#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <swf.h>

const char* printable_tag_type(SWFTagType type);
SWFError parse_swf_file(SWFParser *parser, FILE *fp);

int batch_process_files(int fcount, const char **files, void(*callback)(SWF *swf));

#endif
