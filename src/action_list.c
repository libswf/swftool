#include "action_list.h"
#include <errno.h>
#include <string.h>
#include <math.h>
#include <swf.h>
#include <zlib.h>
#include "util.h"

void action_list_callback(SWF *swf)
{
	// Count the number of digits in the tag count, to get the
	// padding for that column in the output
	unsigned num_max_digits = log10((double)swf->nb_tags) + 1;
	
	for(unsigned i = 0; i < swf->nb_tags; i++)
	{
		SWFTag *tag = &swf->tags[i];
		
		// Tag ID
		printf("%-*d | ", num_max_digits, i+1);
		
		// CRC32
		uint32_t crc = crc32(crc32(0, NULL, 0), tag->payload, tag->size);
		printf("%08X | ", crc);
		
		// Tag name
		const char *type = printable_tag_type(swf->type);
		if(type != NULL) printf("%s", type);
		else printf("UNKNOWN (%i)", tag->type);
		
		printf("\n");
	}
}

int action_list(int fcount, char **files)
{
	return batch_process_files(fcount, files, action_list_callback);
}
