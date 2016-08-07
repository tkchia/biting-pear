#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <set>
#include <sstream>
#include <utility>
#include <unistd.h>
#include <bfd.h>
#define innocent_pear_HOST_SIDE
#include <innocent-pear/dawg.h>
#include <innocent-pear/host/lolcat.h>
#include <innocent-pear/host/srsly.h>

struct afortune
{
	bfd *obfd;
	asymbol **syms;
};

typedef std::set<bfd_size_type> adreld;

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

static void prep_sxn(bfd *ibfd, asection *isxn, void *cookie)
{
	bfd *obfd = (bfd *)cookie;
	const char *name = bfd_section_name(ibfd, isxn);
	flagword flags = bfd_get_section_flags(ibfd, isxn);
	bfd_vma vma = bfd_section_vma(ibfd, isxn),
		lma = bfd_section_lma(ibfd, isxn);
	bfd_size_type size = bfd_section_size(ibfd, isxn);
	std::ostringstream oss;
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

static void do_frob_2(bfd *ibfd, bfd *obfd)
{
	wow("preparing sections");
	bfd_map_over_sections(ibfd, prep_sxn, obfd);
}

static void check_symbol(bfd *ibfd, asymbol *sym, const char *nm)
{
	if (!sym)
		many("symbol ", nm, " is not defined");
	asection *sxn = sym->section;
	const char *name = bfd_section_name(ibfd, sxn);
	if (bfd_is_const_section(sxn))
		many("symbol ", nm, " is in special section ", name);
	flagword fl = bfd_get_section_flags(ibfd, sxn);
	if ((fl & SEC_HAS_CONTENTS) == 0)
		many("symbol ", nm, " is in non-content (possibly BSS) "
		      "section ", name);
	if ((fl & SEC_RELOC) != 0)
		many("symbol ", nm, " is in a section that has static "
		      "relocations");
	symvalue val = sym->value;
	wow("symbol ", nm, " = ", name, ' ', val < 0 ? '-' : '+',
	    " 0x", std::hex, val < 0 ? -val : val);
	if (val < 0 || val > bfd_section_size(ibfd, sxn))
		many("symbol ", nm, " lies outside section content");
}

/* per phrack.org/issues/56/9.html */
static void do_frob_3(bfd *ibfd, bfd *obfd, long *p_n_syms, asymbol ***p_syms)
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
	*p_n_syms = n_syms;
	*p_syms = syms;
}

static void do_frob_4(bfd *ibfd, adreld *dreld)
{
	wow("reading and scanning dynamic relocation tables");
	long dssz = bfd_get_dynamic_symtab_upper_bound(ibfd);
	if (dssz > SSIZE_MAX)
		much("dynamic relocation table is impossibly big!");
	if (dssz < 0) {
		if (bfd_get_error() == bfd_error_invalid_operation) {
			wow("  no dynamic relocations");
			return;
		}
		much("bfd_get_dynamic_symtab_upper_bound");
	}
	asymbol **dyn_syms = new asymbol *[(dssz + sizeof(asymbol *) - 1)
	    / sizeof(asymbol *)];
	if (bfd_canonicalize_dynamic_symtab(ibfd, dyn_syms) < 0)
		much("bfd_canonicalize_dynamic_symtab");
	long drsz = bfd_get_dynamic_reloc_upper_bound(ibfd);
	if (drsz < 0 || drsz > SSIZE_MAX)
		much("bfd_get_dynamic_reloc_upper_bound");
	arelent **dyn_rels = new arelent *[(drsz + sizeof(arelent *) - 1)
	    / sizeof(arelent *)];
	long n_dyn_rels = bfd_canonicalize_dynamic_reloc(ibfd, dyn_rels,
	    dyn_syms);
	if (n_dyn_rels < 0)
		much("bfd_canonicalize_dynamic_reloc");
	for (long i = 0; i < n_dyn_rels; ++i) {
		arelent *rel = dyn_rels[i];
		bfd_size_type rel_off = rel->address;
		bfd_size_type rel_sz = bfd_get_reloc_size(rel->howto);
		while (rel_sz--)
			dreld->insert(rel_off++);
	}
}

/* per phrack.org/issues/56/9.html */
static void do_frob_5(bfd *ibfd, bfd *obfd, const char *bnm, const char *enm,
    long n_syms, asymbol **syms, adreld *dreld, asymbol **p_bsym,
    asymbol **p_esym)
{
	*p_bsym = *p_esym = 0;
	wow("scanning symbol table");
	for (long i = 0; i < n_syms; ++i) {
		asymbol *sym = syms[i];
		if (bfd_is_local_label(ibfd, sym) ||
		    bfd_is_target_special_symbol(ibfd, sym))
			continue;
		if (std::strcmp(sym->name, bnm) == 0)
			*p_bsym = sym;
		if (std::strcmp(sym->name, enm) == 0)
			*p_esym = sym;
	}
	check_symbol(ibfd, *p_bsym, bnm);
	check_symbol(ibfd, *p_esym, enm);
	asection *sxn = (*p_bsym)->section;
	if (sxn != (*p_esym)->section)
		many("symbols ", bnm, " and ", enm,
		     "are in different sections");
	if ((*p_bsym)->value > (*p_esym)->value)
		many("symbol ", enm, " is before ", bnm);
	bfd_size_type
	    bsym_off = (*p_bsym)->value + bfd_section_lma(ibfd, sxn),
	    esym_off = (*p_esym)->value + bfd_section_lma(ibfd, sxn);
	adreld::const_iterator it = dreld->lower_bound(bsym_off);
	if (it != dreld->end() && *it < esym_off)
		many('[', bnm, " ... ", enm, "] has dynamic relocations");
}

static void copy_sxn(bfd *ibfd, asection *isxn, void *cookie)
{
	afortune *fortune = (afortune *)cookie;
	bfd *obfd = fortune->obfd;
	asymbol **syms = fortune->syms;
	asection *osxn = isxn->output_section;
	wow("  ", bfd_section_name(ibfd, osxn));
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
	long rels_sz = bfd_get_reloc_upper_bound(ibfd, isxn);
	if (rels_sz < 0 || rels_sz > SSIZE_MAX)
		much("bfd_get_reloc_upper_bound");
	arelent **rels = new arelent *[(rels_sz + sizeof(arelent *) - 1)
	    / sizeof(arelent *)];
	long nrels = bfd_canonicalize_reloc(ibfd, isxn, rels, syms);
	if (nrels < 0 || nrels != (unsigned)nrels)
		much("bfd_canonicalize_reloc");
	bfd_set_reloc(obfd, osxn, rels, (unsigned)nrels);
}

/* per phrack.org/issues/56/9.html */
static void do_frob_6(bfd *ibfd, bfd *obfd, asymbol *bsym, asymbol *esym,
    asymbol **syms, innocent_pear::impl::rand_state_t seed)
{
	afortune fortune = { obfd, syms };
	wow("copying sections");
	bfd_map_over_sections(ibfd, copy_sxn, &fortune);
	asection *osxn = bsym->section->output_section;
	wow("frobbing section ", bfd_section_name(obfd, osxn));
	file_ptr off = bsym->value;
	bfd_size_type sz = esym->value - bsym->value;
	unsigned char stuff[sz];
	if (!bfd_get_section_contents(obfd, osxn, stuff, off, sz))
		much("bfd_get_section_contents");
	innocent_pear::srsly<unsigned char>(seed).wut(stuff, stuff + sz);
	if (!bfd_set_section_contents(obfd, osxn, stuff, off, sz))
		much("bfd_set_section_contents");
}

/* per phrack.org/issues/56/9.html */
static void do_frob_7(bfd *ibfd, bfd *obfd)
{
	wow("copying BFD back-end data");
	if (!bfd_copy_private_bfd_data(ibfd, obfd))
		much("bfd_copy_private_bfd_data");
}

static void copy_and_frob_object(bfd *ibfd, bfd *obfd, const char *bnm,
    const char *enm, innocent_pear::impl::rand_state_t seed)
{
	asymbol *bsym, *esym, **syms;
	long n_syms;
	adreld dreld;
	do_frob_1(ibfd, obfd);
	do_frob_2(ibfd, obfd);
	do_frob_3(ibfd, obfd, &n_syms, &syms);
	do_frob_4(ibfd, &dreld);
	do_frob_5(ibfd, obfd, bnm, enm, n_syms, syms, &dreld, &bsym, &esym);
	do_frob_6(ibfd, obfd, bsym, esym, syms, seed);
	do_frob_7(ibfd, obfd);
}

int main(int argc, char **argv)
{
	bfd *ibfd = 0, *obfd = 0;
	innocent_pear::impl::rand_state_t seed = 0;
	curious(*argv);
	bfd_init();
	try {
		if (argc != 6 || *argv[5] == 0)
			many("invalid arguments");
		const char *ifn = argv[1], *ofn = argv[2],
		    *bnm = argv[3], *enm = argv[4];
		seed = (innocent_pear::impl::rand_state_t)lolrus(argv[5],
		    "invalid arguments");
		ibfd = bfd_openr(ifn, 0);
		if (!ibfd)
			much("bfd_openr");
		check_object(ibfd);
		sleepier_t tfn(ofn);
		obfd = bfd_openw(tfn(), bfd_get_target(ibfd));
		if (!obfd)
			much("bfd_openw");
		copy_and_frob_object(ibfd, obfd, bnm, enm, seed);
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
