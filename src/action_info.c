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
		SWFError err;
		SWF *swf = swf_create_from_path(path, &err);
		
		if(fcount > 1)
			printf("== %s ==\n", path);
		
		if(swf)
		{
			if(err == SWF_OK)
			{
				printf("SWF %d, %s compression\n", swf->version,
					(swf->compression == SWF_UNCOMPRESSED ? "no" :
						(swf->compression == SWF_ZLIB ? "ZLIB" :
						(swf->compression == SWF_LZMA ? "LZMA" : "unknown"))));
				printf("%dx%dpx, %d frame%s, %f fps\n",
					(swf->frame_size.x_max - swf->frame_size.x_min)/20,
					(swf->frame_size.y_max - swf->frame_size.y_min)/20,
					swf->frame_count, (swf->frame_count > 1 ? "s" : ""),
					swf->frame_rate/256.0f);
			}
			else
			{
				printf("ERROR: Couldn't load file: %s (%d)\n", swf->err.text, err);
				retval = 1;
			}
			
			swf_free(swf);
		}
		else
		{
			fprintf(stderr, "ERROR: Couldn't open file: %s\n", strerror(errno));
			retval = 1;
		}
	}
	
	return retval;
}
