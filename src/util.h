#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <swf.h>
#include "common.h"

const char* printable_tag_type(SWFTagType type);
SWFError parse_swf_file(SWFParser *parser, FILE *fp);

int batch_process_files(args_t *args, void(*callback)(SWF *swf));

#endif
