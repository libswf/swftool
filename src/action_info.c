#include "action_info.h"
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <swf.h>
#include "constants.h"

int action_info(int fcount, char **files)
{
	for(int i = 0; i < fcount; i++)
	{
		const char *path = files[i];
		
		FILE *fp = fopen(path, "rb");
		if(fp)
		{
			SWFParser *parser = swf_parser_init();
			SWF *swf = swf_parser_get_swf(parser);
			
			char buffer[kFileReadBufferSize];
			size_t size_read = 0;
			while((size_read = fread(buffer, 1, sizeof(buffer), fp)) == 0)
			{
				SWFError err = swf_parser_append(parser, buffer, size_read);
				if(err < 0)
				{
					fprintf(stderr, "libswf error (%d): %s\n", err, swf->err.text);
					break;
				}
			}
			
			swf_parser_free(parser);
		}
		else
		{
			fprintf(stderr, "Couldn't open %s: %s", path, strerror(errno));
		}
	}
	
	return 0;
}
