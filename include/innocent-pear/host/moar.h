#ifndef innocent_pear_H_MOAR
#define innocent_pear_H_MOAR

#define KeccakP200_excluded
#define KeccakP400_excluded
#define KeccakP800_excluded
#include <cstdlib>
#include <innocent-pear/bbq.h>
#include "KeccakPRG.h"

class moar_t
{
	KeccakWidth1600_SpongePRG_Instance g_;
    public:
	moar_t()
		{ KeccakWidth1600_SpongePRG_Initialize(&g_, 254u); }
	~moar_t()
		{ KeccakWidth1600_SpongePRG_Forget(&g_); }
	void feed(const unsigned char *, std::size_t);
	innocent_pear::impl::uint_least64_t fetch();
};

#endif
