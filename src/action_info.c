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
		
		FILE *fp = fopen(path, "rb");
		if(fp)
		{
			SWFError err;
			SWF *swf = swf_create_from_file(fp, &err);
			
			fclose(fp);
			
			if(err == SWF_OK)
			{
				if(fcount > 1)
					printf("== %s ==\n", path);
				
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
				printf("Error %d: %s", err, swf->err.text);
				retval = 1;
			}
			
			swf_free(swf);
		}
		else
		{
			fprintf(stderr, "Couldn't open %s: %s", path, strerror(errno));
			retval = 1;
		}
	}
	
	return retval;
}
