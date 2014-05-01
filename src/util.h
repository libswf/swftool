#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <swf.h>

SWF* swf_create_from_path(const char *path, SWFError *out_err);
SWF* swf_create_from_file(FILE *fp, SWFError *out_err);

#endif
