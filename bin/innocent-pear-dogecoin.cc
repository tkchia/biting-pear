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
#include <innocent-pear/dawg.h>
#include <innocent-pear/host/lolcat.h>
#include <innocent-pear/host/srsly.h>

#define NEW_SXN_NAME_TPL ".rodata.innocent_pear.dogecoin"

using innocent_pear::impl::uint64_t;
using innocent_pear::impl::mt19937_64;

typedef std::map<asection *, long> sxn_to_reloc_count_map_t;
typedef std::map<asection *, arelent **> sxn_to_relocs_map_t;
typedef std::list<asection *> sxn_list_t;

struct fortune_t
{
	bfd *obfd;
	asymbol **syms;
	unsigned addr_octets, alignment_power;
	reloc_howto_type *from_howto, *to_howto, *extra_howto;
	long total_abs_reloc_count;
	sxn_to_reloc_count_map_t reloc_count;
	sxn_to_relocs_map_t relocs;
	sxn_list_t xsxns;
};

__attribute__((noinline))
static void such()
{
	std::cerr << "( ) failed: " << bfd_errmsg(bfd_get_error());
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

static mt19937_64 generator;

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
	fortune->obfd = obfd;
	fortune->addr_octets = addr_bits / 8;
	fortune->alignment_power = get_align(addr_bits) - 3;
	fortune->from_howto = from;
	fortune->to_howto = to;
	fortune->extra_howto = extra;
	fortune->total_abs_reloc_count = 0;
}

static void prep_sxn(bfd *ibfd, asection *isxn, void *cookie)
{
	fortune_t *fortune = (fortune_t *)cookie;
	bfd *obfd = fortune->obfd;
	const char *name = bfd_section_name(ibfd, isxn);
	flagword flags = bfd_get_section_flags(ibfd, isxn);
	bfd_vma vma = bfd_section_vma(ibfd, isxn),
		lma = bfd_section_lma(ibfd, isxn);
	bfd_size_type size = bfd_section_size(ibfd, isxn);
	wow("  ", name, ": vma 0x", std::hex, vma,
	    ", lma 0x", lma, ", size 0x", size);
	asection *osxn = bfd_make_section_anyway_with_flags(obfd,name,flags);
	if (!osxn)
		much("bfd_make_section_anyway_with_flags");
	if (!bfd_set_section_size(obfd, osxn, size))
		much("bfd_set_section_size");
	if (!bfd_set_section_vma(obfd, osxn, vma))
		much("bfd_set_section_vma");
	osxn->lma = lma;
	if (!bfd_set_section_alignment(obfd, osxn,
	    bfd_section_alignment(ibfd, isxn)))
		much("bfd_set_section_alignment");
	isxn->output_section = osxn;
	isxn->output_offset = 0;
	if (!bfd_copy_private_section_data(ibfd, isxn, obfd, osxn))
		much("bfd_copy_private_section_data");
}

static void do_frob_3(bfd *ibfd, fortune_t *fortune)
{
	wow("preparing existing sections");
	bfd_map_over_sections(ibfd, prep_sxn, fortune);
}

/* per phrack.org/issues/56/9.html */
static void do_frob_4(bfd *ibfd, bfd *obfd, fortune_t *fortune)
{
	wow("reading and copying symbol table");
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
	fortune->syms = syms;
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
	for (long i = 0; i < nrels; ++i) {
		arelent *pr = rels[i];
		if (are_same_reloc_type(pr->howto, fortune->from_howto))
			++fortune->total_abs_reloc_count;
	}
}

static void do_frob_5(bfd *ibfd, fortune_t *fortune)
{
	wow("collecting and counting relocations");
	bfd_map_over_sections(ibfd, count_sxn_relocs, fortune);
	long cnt = fortune->total_abs_reloc_count;
	wow("  ", cnt, " absolute relocation", cnt == 1 ? "" : "s", " found");
}

static void do_frob_6(bfd *ibfd, bfd *obfd, fortune_t *fortune)
{
	wow("creating new sections");
	long nxsxns = fortune->total_abs_reloc_count;
	for (long i = 0; i < nxsxns; ++i) {
		std::size_t nm_sz = sizeof(NEW_SXN_NAME_TPL) + 17;
		char *nm = new char[nm_sz];
		snprintf(nm, nm_sz, NEW_SXN_NAME_TPL ".%016" PRIx64,
		    (uint64_t)generator());
		if (i == 16)
			wow("  ...");
		else if (i < 16)
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
	wow("  ", bfd_section_name(ibfd, isxn));
	flagword fl = bfd_get_section_flags(ibfd, isxn);
	if ((fl & (SEC_HAS_CONTENTS | SEC_RELOC)) == 0)
		return;
	bfd_size_type sz = bfd_section_size(ibfd, isxn);
	if (sz) {
		unsigned char stuff[sz];
		if (!bfd_get_section_contents(ibfd, isxn, stuff, 0, sz))
			much("bfd_get_section_contents");
		if (!bfd_set_section_contents(obfd, osxn, stuff, 0, sz))
			much("bfd_set_section_contents");
	}
	if ((fl & SEC_RELOC) == 0)
		return;
	if (fortune->relocs.count(isxn) == 0)
		return;
	long nrels = fortune->reloc_count[isxn];
	arelent **rels = fortune->relocs[isxn];
	arelent **orels = new arelent *[nrels];
	for (long i = 0; i < nrels; ++i) {
		arelent *pr = rels[i];
		reloc_howto_type *howto = pr->howto;
		if (!are_same_reloc_type(howto, fortune->from_howto)) {
			orels[i] = pr;
			continue;
		}
		wow("    frobbing reloc. at +0x", std::hex, pr->address);
		arelent *pfr = new arelent;
		*pfr = *pr;
		pfr->howto = fortune->to_howto;
		orels[i] = pfr;
		sxn_list_t& xsxns = fortune->xsxns;
		asection *xsxn = xsxns.front();
		xsxns.pop_front();
		sz = fortune->addr_octets;
		unsigned char stuff[sz];
		memset(stuff, 0, sz);
		if (!bfd_set_section_contents(obfd, xsxn, stuff, 0, sz))
			much("bfd_set_section_contents");
		arelent *xrel = new arelent, **xrels = new arelent *[1];
		xrel->sym_ptr_ptr = osxn->symbol_ptr_ptr;
		xrel->address = 0;
		xrel->addend = pr->address;
		xrel->howto = fortune->extra_howto;
		xrels[0] = xrel;
		bfd_set_reloc(obfd, xsxn, xrels, 1u);
	}
	bfd_set_reloc(obfd, osxn, orels, (unsigned)nrels);
}

/* per phrack.org/issues/56/9.html */
static void do_frob_7(bfd *ibfd, fortune_t *fortune)
{
	wow("copying and frobbing sections");
	bfd_map_over_sections(ibfd, copy_sxn, fortune);
	if (!fortune->xsxns.empty())
		many("inconsistent relocation counts!");
}

/* per phrack.org/issues/56/9.html */
static void do_frob_8(bfd *ibfd, bfd *obfd)
{
	wow("copying BFD back-end data");
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
	do_frob_6(ibfd, obfd, &fortune);
	do_frob_7(ibfd, &fortune);
	do_frob_8(ibfd, obfd);
}

int main(int argc, char **argv)
{
	bfd *ibfd = 0, *obfd = 0;
	curious(*argv);
	bfd_init();
	try {
		if (argc != 4)
			many("invalid arguments");
		const char *ifn = argv[1], *ofn = argv[2];
		generator.seed(lolrus(argv[3], "invalid arguments"));
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
