#include "action_info.h"
#include <errno.h>
#include <string.h>
#include <swf.h>
#include "util.h"

int action_info(int fcount, char **files)
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
				
				printf("SWF %d, %s compression\n", swf->version,
					(swf->compression == SWF_UNCOMPRESSED ? "no" :
						(swf->compression == SWF_ZLIB ? "ZLIB" :
						(swf->compression == SWF_LZMA ? "LZMA" : "unknown"))));
				printf("%dx%dpx, %d frame%s, %f fps\n",
					(swf->frame_size.x_max - swf->frame_size.x_min)/20,
					(swf->frame_size.y_max - swf->frame_size.y_min)/20,
					swf->frame_count, (swf->frame_count > 1 ? "s" : ""),
					swf->frame_rate/256.0f);
				
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
