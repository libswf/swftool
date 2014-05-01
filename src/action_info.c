#include "action_info.h"
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
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
			
			// This code can correctly duplicate a 34kb text file (`diff` says no difference)
			// libswf errors out with SWF_INVALID instead, if fed the file in chunks
			/*char buffer[kFileReadBufferSize];
			size_t size_read = 0;
			while((size_read = fread(buffer, 1, sizeof(buffer), fp)) > 0)
			{
				printf("Read %d bytes\n", size_read);
				SWFError err = swf_parser_append(parser, buffer, size_read);
				if(err < 0)
				{
					fprintf(stderr, "libswf error (%d): %s\n", err, swf_parser_get_swf(parser)->err.text);
					break;
				}
			}*/
			
			// This is far less efficient, but it's a workaround for a libswf bug
			fseek(fp, 0, SEEK_END);
			size_t size = ftell(fp);
			fseek(fp, 0, SEEK_SET);
			
			void *buffer = malloc(size);
			fread(buffer, 1, size, fp);
			swf_parser_append(parser, buffer, size);
			free(buffer);
			
			fclose(fp);
			swf_parser_free(parser);
			
			printf("%s\n", path);
			printf("SWF %d, %s compression\n", swf->version,
				(swf->compression == SWF_UNCOMPRESSED ? "no" :
					(swf->compression == SWF_ZLIB ? "ZLIB" :
					(swf->compression == SWF_LZMA ? "LZMA" : "unknown"))));
			
			swf_free(swf);
		}
		else
		{
			fprintf(stderr, "Couldn't open %s: %s", path, strerror(errno));
		}
	}
	
	return 0;
}
