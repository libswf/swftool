#include "util.h"
#include <stdlib.h>
#include "constants.h"

SWFError parse_swf_file(SWFParser *parser, FILE *fp)
{
	if(parser == NULL || fp == NULL) return SWF_UNKNOWN;
	
	char buffer[kFileReadBufferSize];
	size_t size_read = 0;
	while((size_read = fread(buffer, 1, sizeof(buffer), fp)) > 0)
	{
		SWFError err = swf_parser_append(parser, buffer, size_read);
		if(err < 0) return err;
	}
	
	return SWF_OK;
}
