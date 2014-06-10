#ifndef COMMON_H
#define COMMON_H

typedef struct {
	int fcount;
	const char **files;
	
	bool verbose, test;
} args_t;

#endif
