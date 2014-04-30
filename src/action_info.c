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
			
			// -- This code triggers a flood of Error -127 (Invalid)
			/*char buffer[kFileReadBufferSize];
			size_t size_read = 0;
			while((size_read = fread(buffer, 1, sizeof(buffer), fp)) == sizeof(buffer))
			{
				SWFError err = swf_parser_append(parser, buffer, size_read);
				if(err < 0)
				{
					fprintf(stderr, "libswf error (%d): %s\n", err, swf->err.text);
					//break;
				}
			}
			*/
			
			fseek(fp, 0, SEEK_END);
			size_t size = ftell(fp);
			fseek(fp, 0, SEEK_SET);
			
			void *buffer = malloc(size);
			fread(buffer, 1, size, fp);
			SWFError err = swf_parser_append(parser, buffer, size);
			if(err < 0)
				fprintf(stderr, "libswf error (%d): %s\n", err, swf->err.text);
			
			swf_parser_free(parser);
		}
		else
		{
			fprintf(stderr, "Couldn't open %s: %s", path, strerror(errno));
		}
	}
	
	return 0;
}
