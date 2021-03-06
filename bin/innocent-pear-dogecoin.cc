#include <cinttypes>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <utility>
#include <unistd.h>
#include <bfd.h>
#define innocent_pear_HOST_SIDE
#include <innocent-pear/bbq.h>
#include <innocent-pear/dawg.h>
#include <innocent-pear/host/lolcat.h>
#include <innocent-pear/host/srsly.h>

#define NEW_SXN_NAME_TPL ".innocent_pear.dogecoin"

typedef std::map<asection *, long> sxn_to_reloc_count_map_t;
typedef std::map<asection *, arelent **> sxn_to_relocs_map_t;
typedef std::list<asection *> sxn_list_t;

struct fortune_t
{
	bfd *obfd;
	unsigned long sxn_ctr, n_syms;
	asymbol **syms;
	unsigned addr_octets, alignment_power, pcrel_adj;
	reloc_howto_type *from_howto, *to_howto, *extra_howto;
	long total_abs_reloc_count;
	sxn_to_reloc_count_map_t reloc_count;
	sxn_to_relocs_map_t relocs;
	sxn_list_t xsxns;
};

enum our_mode_t
{
	mode_relativize,
	mode_unmerge
};

__attribute__((noinline))
static void such()
{
	std::cerr << "( ) failed: " << bfd_errmsg(bfd_get_error());
	amaze();
}

__attribute__((noinline))
static void such_very()
{
	std::cerr << ") failed: " << bfd_errmsg(bfd_get_error());
	amaze();
}

template<class... Ts>
__attribute__((always_inline))
inline void much(Ts... msg)
{
	std::cerr << "ERROR: ";
	very(msg...);
	such();
}

template<class... Ts>
__attribute__((always_inline))
inline void much_very(Ts... msg)
{
	std::cerr << "ERROR: ";
	very(msg...);
	such_very();
}

static our_mode_t our_mode;
static innocent_pear::impl::rand_state_t prg;

static unsigned get_align(unsigned x)
{
	if (x % 2 != 0 || x == 0)
		return 0;
	else
		return get_align(x / 2) + 1;
}

static void check_object(bfd *ibfd)
{
	if (!bfd_check_format(ibfd, bfd_object))
		much("bfd_check_format");
	const char *tgt = bfd_get_target(ibfd);
	wow("input file is for target ", tgt);
	if (bfd_get_flavour(ibfd) == bfd_target_coff_flavour &&
	    std::strncmp(tgt, "pei-", (size_t)4) == 0)
		many("unsupported: Windows PE object");
}

/* per phrack.org/issues/56/9.html */
static void do_frob_1(bfd *ibfd, bfd *obfd)
{
	wow("copying basic object attributes");
	if (!bfd_set_format(obfd, bfd_get_format(ibfd)))
		much("bfd_set_format");
	flagword fl = bfd_get_file_flags(ibfd);
	if (!bfd_set_file_flags(obfd, fl & bfd_applicable_file_flags(obfd)))
		much("bfd_set_file_flags");
	if (!bfd_set_start_address(obfd, bfd_get_start_address(ibfd)))
		much("bfd_set_start_address");
	if (!bfd_set_arch_mach(obfd, bfd_get_arch(ibfd), bfd_get_mach(ibfd)))
		much("bfd_set_arch_mach");
}

static void do_frob_2(bfd *ibfd, bfd *obfd, fortune_t *fortune)
{
	fortune->obfd = obfd;
	fortune->total_abs_reloc_count = 0;
	if (our_mode != mode_relativize)
		return;
	wow("figuring out how to frob relocations");
	unsigned addr_bits = bfd_arch_bits_per_address(ibfd);
	wow("  addresses are ", addr_bits, " bits each");
	reloc_howto_type *from, *to, *extra;
	switch (addr_bits) {
	    case 64:	from = bfd_reloc_type_lookup(ibfd, BFD_RELOC_64);
			to = bfd_reloc_type_lookup(obfd, BFD_RELOC_64_PCREL);
			break;
	    case 32:	from = bfd_reloc_type_lookup(ibfd, BFD_RELOC_32);
			to = bfd_reloc_type_lookup(obfd, BFD_RELOC_32_PCREL);
			break;
	    case 24:	from = bfd_reloc_type_lookup(ibfd, BFD_RELOC_24);
			to = bfd_reloc_type_lookup(obfd, BFD_RELOC_24_PCREL);
			break;
	    case 16:	from = bfd_reloc_type_lookup(ibfd, BFD_RELOC_16);
			to = bfd_reloc_type_lookup(obfd, BFD_RELOC_16_PCREL);
			break;
	    default:	from = to = 0;
	}
	if (!from || !to)
		many("no idea how to frob ", addr_bits, "-bit "
		     "absolute relocations!");
	extra = to;
	wow("  rewriting relocation type ", from->name);
	wow("    to ", to->name, " plus ", extra->name);
	fortune->addr_octets = addr_bits / 8;
	fortune->alignment_power = get_align(addr_bits) - 3;
	if (bfd_get_arch(obfd) == bfd_arch_i386 && addr_bits == 32)
		fortune->pcrel_adj = 4;
	else
		fortune->pcrel_adj = 0;
	fortune->from_howto = from;
	fortune->to_howto = to;
	fortune->extra_howto = extra;
}

static void prep_sxn_i(bfd *ibfd, asection *isxn, void *cookie)
{
	fortune_t *fortune = (fortune_t *)cookie;
	bfd *obfd = fortune->obfd;
	const char *name = bfd_section_name(ibfd, isxn);
	flagword flags = bfd_get_section_flags(ibfd, isxn);
	bfd_vma vma = bfd_section_vma(ibfd, isxn),
		lma = bfd_section_lma(ibfd, isxn);
	bfd_size_type size = bfd_section_size(ibfd, isxn);
	if (fortune->sxn_ctr++ == 64)
		wow("  ...");
	else if (fortune->sxn_ctr < 64)
		wow("  ", name, ": vma 0x", std::hex, vma,
		    ", lma 0x", lma, ", size 0x", size);
	if (our_mode == mode_unmerge) {
		if ((flags & SEC_ALLOC) != 0 && (flags & SEC_MERGE) != 0) {
			wow("  ", name, ": allocated, mergeable -- "
			    "making non-mergeable");
			flags &= ~(SEC_MERGE | SEC_STRINGS);
		}
	}
	asection *osxn = bfd_make_section_anyway_with_flags(obfd,name,flags);
	if (!osxn)
		much_very("bfd_make_section_anyway_with_flags(, ", name, ", ");
	if (!bfd_set_section_size(obfd, osxn, size))
		much_very("bfd_set_section_size(, ", name, ", ");
	if (!bfd_set_section_vma(obfd, osxn, vma))
		much_very("bfd_set_section_vma(, ", name, ", ");
	osxn->lma = lma;
	if (!bfd_set_section_alignment(obfd, osxn,
	    bfd_section_alignment(ibfd, isxn)))
		much_very("bfd_set_section_alignment(, ", name, ", ");
	isxn->output_section = osxn;
	isxn->output_offset = 0;
	osxn->entsize = isxn->entsize;
	osxn->compress_status = isxn->compress_status;
}

static void do_frob_3(bfd *ibfd, fortune_t *fortune)
{
	wow("preparing existing sections");
	fortune->sxn_ctr = 0;
	bfd_map_over_sections(ibfd, prep_sxn_i, fortune);
}

/* per phrack.org/issues/56/9.html */
static void do_frob_4(bfd *ibfd, bfd *obfd, fortune_t *fortune)
{
	wow("reading and copying symbol table");
	fortune->n_syms = 0;
	fortune->syms = 0;
	long symtab_sz = bfd_get_symtab_upper_bound(ibfd), n_syms;
	if (symtab_sz < 0 || symtab_sz > SSIZE_MAX)
		much("bfd_get_symtab_upper_bound");
	asymbol **syms = new asymbol *[(symtab_sz + sizeof(asymbol *) - 1)
	    / sizeof(asymbol *)];
	n_syms = bfd_canonicalize_symtab(ibfd, syms);
	if (n_syms < 0)
		much("bfd_canonicalize_symtab");
	if (!bfd_set_symtab(obfd, syms, n_syms))
		much("bfd_set_symtab");
	fortune->n_syms = n_syms;
	fortune->syms = syms;
}

static void prep_sxn_ii(bfd *ibfd, asection *isxn, void *cookie)
{
	/* OK, this is a really, really bad idea... */
	typedef struct
	{
		unsigned sh_name, sh_type;
		bfd_vma sh_flags, sh_addr;
		file_ptr sh_offset;
		bfd_size_type sh_size;
		unsigned sh_link, sh_info;
		bfd_vma sh_addralign;
		bfd_size_type sh_entsize;
		asection *bfd_section;
		unsigned char *contents;
	} Elf_Internal_Shdr;
	struct bfd_elf_section_reloc_data
	{
		Elf_Internal_Shdr *hdr;
		unsigned count;
		int idx;
		struct elf_link_hash_entry **hashes;
	};
	struct bfd_elf_section_data
	{
		Elf_Internal_Shdr this_hdr;
		struct flag_info *section_flag_info;
		struct bfd_elf_section_reloc_data rel, rela;
		int this_idx, dynindx;
		asection *linked_to;
		struct elf_internal_rela *relocs;
		void *local_dynrel;
		asection *sreloc;
		union {
			const char *name;
			asymbol *id;
		} group;
		asection *sec_group;
		/* ... */
	};
	const unsigned SHT_GROUP = 0x11;
	fortune_t *fortune = (fortune_t *)cookie;
	flagword flags = bfd_get_section_flags(ibfd, isxn);
	if ((flags & SEC_GROUP) == 0)
		return;
	const char *name = bfd_section_name(ibfd, isxn);
	bfd_elf_section_data *psd = (bfd_elf_section_data *)isxn->used_by_bfd;
	if (!psd) {
		wow("  ", name, ": !psd");
		return;
	}
	Elf_Internal_Shdr *psh = &psd->this_hdr;
	if (psh->sh_type != SHT_GROUP) {
		wow("  ", name, ": psh->sh_type != SHT_GROUP");
		return;
	}
	if (psh->sh_flags != 0) {
		wow("  ", name, ": psh->sh_flags != 0");
		return;
	}
	if (psh->sh_addr != bfd_section_vma(ibfd, isxn)) {
		wow("  ", name, ": psh->sh_addr bogus");
		return;
	}
	if (psh->sh_info == 0) {
		wow("  ", name, ": psh->sh_info == 0");
		return;
	}
	if (psh->sh_info > fortune->n_syms) {
		wow("  ", name, ": psh->sh_info > n_syms");
		return;
	}
	if (psh->bfd_section != isxn) {
		wow("  ", name, ": psh->bfd_section != isxn");
		return;
	}
	if (psd->group.id != 0) {
		wow("  ", name, ": psd->group.id != 0");
		return;
	}
	asymbol *id = fortune->syms[psh->sh_info - 1];
	psd->group.id = id;
	if (fortune->sxn_ctr++ == 64)
		wow("  ...");
	else if (fortune->sxn_ctr < 64)
		wow("  ", name, '[', id->name, ']');
}

static void prep_sxn_iii(bfd *ibfd, asection *isxn, void *cookie)
{
	fortune_t *fortune = (fortune_t *)cookie;
	bfd *obfd = fortune->obfd;
	const char *name = bfd_section_name(ibfd, isxn);
	if (fortune->sxn_ctr++ == 64)
		wow("  ...");
	else if (fortune->sxn_ctr < 64)
		wow("  ", name);
	asection *osxn = isxn->output_section;
	if (!bfd_copy_private_section_data(ibfd, isxn, obfd, osxn))
		much("bfd_copy_private_section_data");
}

static void do_frob_5(bfd *ibfd, fortune_t *fortune)
{
	if (fortune->syms != 0 &&
	    bfd_get_flavour(ibfd) == bfd_target_elf_flavour) {
		wow("fishing out section group signatures");
		fortune->sxn_ctr = 0;
		bfd_map_over_sections(ibfd, prep_sxn_ii, fortune);
	}
	wow("copying BFD back-end data for sections");
	fortune->sxn_ctr = 0;
	bfd_map_over_sections(ibfd, prep_sxn_iii, fortune);
}

static void do_frob_6(bfd *ibfd, bfd *obfd)
{
	wow("copying BFD back-end header data");
	if (!bfd_copy_private_header_data(ibfd, obfd))
		much("bfd_copy_private_header_data");
}

static bool are_same_reloc_type(reloc_howto_type *h1, reloc_howto_type *h2)
{
	/* Is there a better way to compare these things? */
	return h1 == h2 || memcmp(h1, h2, sizeof(*h1)) == 0;
}

static void count_sxn_relocs(bfd *ibfd, asection *isxn, void *cookie)
{
	fortune_t *fortune = (fortune_t *)cookie;
	flagword fl = bfd_get_section_flags(ibfd, isxn);
	if ((fl & SEC_RELOC) == 0)
		return;
	long rels_sz = bfd_get_reloc_upper_bound(ibfd, isxn);
	if (rels_sz <= 0)
		return;
	arelent **rels = new arelent *[(rels_sz + sizeof(arelent *) - 1)
	    / sizeof(arelent *)];
	long nrels = bfd_canonicalize_reloc(ibfd, isxn, rels, fortune->syms);
	if (nrels < 0 || nrels != (unsigned)nrels)
		much("bfd_canonicalize_reloc");
	if (fortune->relocs.count(isxn) != 0)
		many("libbfd scanned the same section twice for some reason");
	fortune->reloc_count[isxn] = nrels;
	fortune->relocs[isxn] = rels;
	if (our_mode != mode_relativize)
		return;
	/*
	 * Do not frob relocations belonging to sections containing group
	 * information.
	 *
	 * In addition, at this point we do not frob relocations belonging
	 * to link-once sections, mergeable sections, sorted sections, or
	 * sections which _belong_ to groups (which may mark the sections as
	 * being link-once).  It may make sense in the future to frob
	 * relocations on _some_ link-once, mergeable, or sorted sections,
	 * but this needs to be done right.
	 */
	if ((fl & (SEC_LINK_ONCE | SEC_MERGE | SEC_SORT_ENTRIES)) != 0 ||
	    bfd_is_group_section(ibfd, isxn))
		return;
	for (long i = 0; i < nrels; ++i) {
		arelent *pr = rels[i];
		if (are_same_reloc_type(pr->howto, fortune->from_howto))
			++fortune->total_abs_reloc_count;
	}
}

static void do_frob_7(bfd *ibfd, fortune_t *fortune)
{
	wow("collecting and counting relocations");
	bfd_map_over_sections(ibfd, count_sxn_relocs, fortune);
	if (our_mode != mode_relativize)
		return;
	long cnt = fortune->total_abs_reloc_count;
	wow("  ", cnt, " frobbable absolute relocation",
	    cnt == 1 ? "" : "s", " found");
}

static void do_frob_8(bfd *ibfd, bfd *obfd, fortune_t *fortune)
{
	if (our_mode != mode_relativize)
		return;
	wow("creating new sections");
	long nxsxns = fortune->total_abs_reloc_count;
	for (long i = 0; i < nxsxns; ++i) {
		std::size_t nm_sz = sizeof(NEW_SXN_NAME_TPL) + 17;
		char *nm = new char[nm_sz];
		prg = innocent_pear::impl::update_outer(prg, 5);
		snprintf(nm, nm_sz, NEW_SXN_NAME_TPL ".%016" PRIxLEAST64, prg);
		if (i == 64)
			wow("  ...");
		else if (i < 64)
			wow("  ", nm);
		asection *xsxn = bfd_make_section_anyway_with_flags(obfd, nm,
		    SEC_ALLOC | SEC_LOAD | SEC_READONLY | SEC_DATA |
		    SEC_HAS_CONTENTS | SEC_RELOC | SEC_KEEP);
		if (!xsxn)
			much("bfd_make_section_anyway_with_flags");
		bfd_size_type xsxn_sz = fortune->addr_octets;
		if (!bfd_set_section_size(obfd, xsxn, xsxn_sz))
			much("bfd_set_section_size");
		if (!bfd_set_section_vma(obfd, xsxn, 0))
			much("bfd_set_section_vma");
		if (!bfd_set_section_alignment(obfd, xsxn,
		    fortune->alignment_power))
			much("bfd_set_section_alignment");
		fortune->xsxns.push_back(xsxn);
	}
}

static void copy_sxn(bfd *ibfd, asection *isxn, void *cookie)
{
	fortune_t *fortune = (fortune_t *)cookie;
	bfd *obfd = fortune->obfd;
	asection *osxn = isxn->output_section;
	const char *name = bfd_section_name(ibfd, isxn);
	bool blurt = false;
	if (fortune->sxn_ctr++ == 64)
		wow("  ...");
	else if (fortune->sxn_ctr < 64) {
		wow("  ", name);
		blurt = true;
	}
	flagword fl = bfd_get_section_flags(ibfd, isxn);
	if ((fl & (SEC_HAS_CONTENTS | SEC_RELOC)) == 0)
		return;
	if ((fl & SEC_GROUP) == 0) {
		bfd_size_type sz = bfd_section_size(ibfd, isxn);
		if (sz) {
			unsigned char stuff[sz];
			if (!bfd_get_section_contents(ibfd,isxn,stuff,0,sz))
				much_very("bfd_get_section_contents(, ", name,
				    ", ...");
			if (!bfd_set_section_contents(obfd,osxn,stuff,0,sz))
				much_very("bfd_set_section_contents(, ", name,
				    ", ...");
		}
	}
	if ((fl & SEC_RELOC) == 0 || fortune->relocs.count(isxn) == 0)
		return;
	long nrels = fortune->reloc_count[isxn];
	arelent **rels = fortune->relocs[isxn];
	if (our_mode != mode_relativize) {
		bfd_set_reloc(obfd, osxn, rels, (unsigned)nrels);
		return;
	}
	if ((fl & (SEC_LINK_ONCE | SEC_MERGE | SEC_SORT_ENTRIES)) != 0 ||
	    bfd_is_group_section(ibfd, isxn)) {
		if (blurt)
			wow("    not frobbing");
		bfd_set_reloc(obfd, osxn, rels, (unsigned)nrels);
		return;
	}
	arelent **orels = new arelent *[nrels];
	for (long i = 0; i < nrels; ++i) {
		arelent *pr = rels[i];
		reloc_howto_type *howto = pr->howto;
		if (!are_same_reloc_type(howto, fortune->from_howto)) {
			orels[i] = pr;
			continue;
		}
		/*
		 * (1) We need to decide whether to stash the place offset
		 *     (pr->address) in the section contents, or in the new
		 *     relocation's addend field (xrel->addend).  We also
		 *     need to decide how (and whether) to adjust the addend
		 *     for the original relocation.
		 *
		 *     From the libbfd info file:
		 *
		 *	"All relocations for all ELF USE_RELA targets should
		 *	 set this [.partial_inplace] field to FALSE (values
		 *	 of TRUE should be looked on with suspicion). 
		 *	 However, the converse is not true: not all
		 *	 relocations of all ELF USE_REL targets set this
		 *	 field to TRUE.  Why this is so is peculiar to each
		 *	 particular target."
		 *
		 *     And indeed howto->partial_inplace is unreliable. 
		 *     (E.g. libbfd has .partial_inplace == false for
		 *     R_ARM_REL32 in a 32-bit ARM target, but totally
		 *     ignores xrel->addend when actually applying
		 *     R_ARM_REL32 relocations.)
		 *
		 *     So instead of using .partial_inplace, use .src_mask. 
		 *     If .src_mask says that we can fit the place offset
		 *     into the section contents, then do so.
		 *
		 * (2) To take care of relocations referring to mergeable
		 *     sections (SEC_MERGE), we need to take into account
		 *     how a linker decides which locations are reachable
		 *     when doing a mark-and-sweep.
		 *
		 *     In particular, for an i386 target when a direct `jmp'
		 *     or `call' will have an offset relative to the
		 *     instructions _end_, an R_386_PC32 at place P for
		 *     symbol S with addend A is taken to refer to S + A +
		 *     4, not S + A.
		 *
		 *     This means S + A + 4 will be marked as reachable, and
		 *     S + A not necessarily so!
		 *
		 *     Thus, for i386, we subtract 4 to the addends of the
		 *     R_386_PC32 relocations, and in the target startup
		 *     code (in share/innocent-pear/), we add 4 back in.
		 */
		if (blurt)
			wow("    frobbing reloc. at +0x", std::hex,
			    pr->address);
		bfd_size_type sz = fortune->addr_octets;
		unsigned char stuff[sz];
		bfd_vma adj = fortune->pcrel_adj;
		arelent *pfr = new arelent;
		*pfr = *pr;
		pfr->howto = fortune->to_howto;
		if (adj != 0) {
			if (pfr->howto->src_mask != 0) {
				if (!bfd_get_section_contents(obfd, osxn,
				    stuff, pfr->address, sz))
					much_very("bfd_get_section_contents"
					    "(, ", name, ", ...");
				bfd_put(sz * 8, obfd, bfd_get(sz * 8, obfd,
				    stuff) - adj, stuff);
				if (!bfd_set_section_contents(obfd, osxn,
				    stuff, pfr->address, sz))
					much_very("bfd_set_section_contents"
					    "(, ", name, ", ...");
			} else
				pfr->addend -= adj;
		}
		orels[i] = pfr;
		sxn_list_t& xsxns = fortune->xsxns;
		asection *xsxn = xsxns.front();
		xsxns.pop_front();
		arelent *xrel = new arelent, **xrels = new arelent *[1];
		xrels[0] = xrel;
		xrel->sym_ptr_ptr = osxn->symbol_ptr_ptr;
		xrel->address = 0;
		howto = fortune->extra_howto;
		xrel->howto = howto;
		bfd_size_type off = pr->address;
		off -= adj;
		const char *xname = bfd_section_name(obfd, xsxn);
		if (howto->src_mask != 0) {
			if (blurt)
				wow("    ~> p ", xname);
			bfd_put(sz * 8, obfd, off, stuff);
			xrel->addend = 0;
		} else {
			if (blurt)
				wow("    ~> a ", xname);
			memset(stuff, 0, sz);
			xrel->addend = off;
		}
		if (!bfd_set_section_contents(obfd, xsxn, stuff, 0, sz))
			much_very("bfd_set_section_contents(, ", xname,
			    ", ...");
		bfd_set_reloc(obfd, xsxn, xrels, 1u);
	}
	bfd_set_reloc(obfd, osxn, orels, (unsigned)nrels);
}

/* per phrack.org/issues/56/9.html */
static void do_frob_9(bfd *ibfd, fortune_t *fortune)
{
	if (our_mode == mode_relativize)
		wow("copying and frobbing sections");
	else
		wow("copying sections");
	fortune->sxn_ctr = 0;
	bfd_map_over_sections(ibfd, copy_sxn, fortune);
	if (!fortune->xsxns.empty())
		many("inconsistent relocation counts!");
}

/* per phrack.org/issues/56/9.html */
static void do_frob_10(bfd *ibfd, bfd *obfd)
{
	wow("copying remaining BFD back-end data");
	if (!bfd_copy_private_bfd_data(ibfd, obfd))
		much("bfd_copy_private_bfd_data");
}

static void copy_and_frob_object(bfd *ibfd, bfd *obfd)
{
	fortune_t fortune;
	do_frob_1(ibfd, obfd);
	do_frob_2(ibfd, obfd, &fortune);
	do_frob_3(ibfd, &fortune);
	do_frob_4(ibfd, obfd, &fortune);
	do_frob_5(ibfd, &fortune);
	do_frob_6(ibfd, obfd);
	do_frob_7(ibfd, &fortune);
	do_frob_8(ibfd, obfd, &fortune);
	do_frob_9(ibfd, &fortune);
	do_frob_10(ibfd, obfd);
}

int main(int argc, char **argv)
{
	bfd *ibfd = 0, *obfd = 0;
	curious(*argv);
	bfd_init();
	try {
		if (argc == 5 && strcmp(argv[4], "-v") == 0) {
			ohai(true);
			--argc;
		}
		if (argc != 4)
			many("invalid arguments");
		const char *ifn = argv[1], *ofn = argv[2];
		if (strcmp(argv[3], "u") == 0)
			our_mode = mode_unmerge;
		else {
			our_mode = mode_relativize;
			prg = lolrus(argv[3], "invalid arguments");
		}
		ibfd = bfd_openr(ifn, 0);
		if (!ibfd)
			much("bfd_openr");
		check_object(ibfd);
		sleepier_t tfn(ofn);
		obfd = bfd_openw(tfn(), bfd_get_target(ibfd));
		if (!obfd)
			much("bfd_openw");
		copy_and_frob_object(ibfd, obfd);
		bfd_boolean closed = bfd_close(obfd);
		obfd = 0;
		if (!closed)
			much("bfd_close");
		tfn.sleepiest(ofn);
		bfd_close(ibfd);
		ibfd = 0;
		wow("done");
	} catch (int s) {
		if (obfd)
			bfd_close_all_done(obfd);
		if (ibfd)
			bfd_close(ibfd);
		return s;
	}
	return 0;
}
