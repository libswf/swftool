#ifndef COMMON_H
#define COMMON_H

#include <stdbool.h>

typedef struct {
	int fcount;
	char **files;
	
	bool verbose;
} args_t;

#endif
