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

int batch_process_files(int fcount, const char **files, void(*callback)(SWF *swf))
{
	int retval = 0;
	
	for(int i = 0; i < fcount; i++)
	{
		const char *path = files[i];
		
		if(fcount > 1)
			printf("== %s ==\n", path);
		
		FILE *fp = fopen(path, "rb");
		if(fp)
		{
			SWFParser *parser = swf_parser_init();
			
			if(parse_swf_file(parser, fp) == SWF_OK)
			{
				SWF *swf = swf_parser_get_swf(parser);
				callback(swf);
				swf_free(swf);
			}
			else
			{
				SWFErrorDesc *err = swf_parser_get_error(parser);
				printf("ERROR: Couldn't load file: %s (%d)\n", err->text, err->code);
				retval = 1;
			}
			
			swf_parser_free(parser);
		}
		else
		{
			fprintf(stderr, "ERROR: Couldn't open file: %s\n", strerror(errno));
			retval = 1;
		}
	}
	
	return retval;
}
