#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <swf.h>

SWFError parse_swf_file(SWFParser *parser, FILE *fp);

#endif
