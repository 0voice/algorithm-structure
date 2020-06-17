#include <limits.h>
#include <stdarg.h>

#include "bloom.h"

#define SETBIT(a,n) (a[n/CHAR_BIT] |= (1<<(n%CHAR_BIT)))
#define GETBIT(a,n) (a[n/CHAR_BIT] & (1<<(n%CHAR_BIT)))

BLOOM* bloom_create(size_t size,size_t nfuncs,...)
{
	BLOOM* bloom;
	va_list l;
	int n;

	if (!(bloom = malloc(sizeof(BLOOM)))) return NULL;
	if (!(bloom->a = calloc((size+CHAR_BIT-1)/CHAR_BIT,sizeof(char))))
	{
		free(bloom);
		return NULL;
	}

	if (!(bloom->funcs = (hashfunc_t*)malloc(nfuncs*sizeof(hashfunc_t)))) 
	{
		free(bloom->a);	
		free(bloom);
		return NULL;
	}

	va_start(l,nfuncs);
	for (n = 0; n < nfuncs; ++n)
	{
		bloom->funcs[n] = va_arg(l,hashfunc_t);
	}
	va_end(l);
	
	bloom->nfuncs = nfuncs;
	bloom->asize = size;

	return bloom;
}

int bloom_destroy(BLOOM* bloom)
{
	free(bloom->a);
	free(bloom->funcs);
	free(bloom);

	return 0;
}

int bloom_add(BLOOM* bloom,const char* s)
{
	size_t n;

	for (n = 0; n < bloom->nfuncs; ++n)
	{
		SETBIT(bloom->a,bloom->funcs[n](s)%bloom->asize);
	}

	return 0;
}

int bloom_check(BLOOM* bloom,const char* s)
{
	size_t n;

	for (n = 0; n < bloom->nfuncs; ++n)
	{
		if (!(GETBIT(bloom->a,bloom->funcs[n](s)%bloom->asize))) return 0;
	}

	return 1;
}
