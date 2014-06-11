#ifndef COMMON_H
#define COMMON_H

#include <stdbool.h>

typedef struct {
	int fcount;
	char **files;
	
	bool print_help;
	bool verbose;
} args_t;

// Based on code from http://stackoverflow.com/a/3437484
#ifdef __GNUC__
	// This requires the non-standard GNU Statement Expression extension
	#define MAX(a,b) \
		({\
			__typeof__(a) _a = (a); \
			__typeof__(b) _b = (b); \
			_a > _b ? _a : _b;\
		})
#else
	// This compiles on anything
	#define MAX(a,b) (a > b ? a : b)
#endif

#endif
