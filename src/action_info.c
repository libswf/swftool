#include "action_info.h"
#include <swf.h>
#include "util.h"

void action_info_callback(SWF *swf)
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

int action_info(args_t *args)
{
	return batch_process_files(args, action_info_callback);
}
