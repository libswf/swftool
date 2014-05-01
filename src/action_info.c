#include "action_info.h"
#include <errno.h>
#include <string.h>
#include <swf.h>
#include "util.h"

int action_info(int fcount, char **files)
{
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
				printf("%s\n", path);
				printf("SWF %d, %s compression\n", swf->version,
					(swf->compression == SWF_UNCOMPRESSED ? "no" :
						(swf->compression == SWF_ZLIB ? "ZLIB" :
						(swf->compression == SWF_LZMA ? "LZMA" : "unknown"))));
			}
			else
			{
				printf("Error %d: %s", err, swf->err.text);
			}
			
			swf_free(swf);
		}
		else
		{
			fprintf(stderr, "Couldn't open %s: %s", path, strerror(errno));
		}
	}
	
	return 0;
}
