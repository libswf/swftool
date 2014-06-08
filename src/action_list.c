#include "action_list.h"
#include <errno.h>
#include <string.h>
#include <swf.h>
#include "util.h"

int action_list(int fcount, char **files)
{
	int retval = 0;
	
	for(int i = 0; i < fcount; i++)
	{
		const char *path = files[i];
		SWFError err;
		SWF *swf = swf_create_from_path(path, &err);
		
		if(swf)
		{
			if(err == SWF_OK)
			{
				if(fcount > 1)
					printf("== %s ==\n", path);
				
				for(unsigned i = 0; i < swf->nb_tags; i++)
				{
					SWFTag *tag = &swf->tags[i];
					char *type = NULL;
					
					// TODO: More descriptive tag names
					switch(tag->type)
					{
						case SWF_END:
							type = "End"; break;
						case SWF_SHOW_FRAME:
							type = "Show Frame"; break;
						case SWF_DEFINE_SHAPE:
							type = "Define Shape"; break;
						case SWF_PLACE_OBJECT:
							type = "Place Object"; break;
						case SWF_REMOVE_OBJECT:
							type = "Remove Object"; break;
						case SWF_DEFINE_BITS:
							type = "Define Bits"; break;
						case SWF_DEFINE_BUTTON:
							type = "Define Button"; break;
						case SWF_JPEG_TABLES:
							type = "JPEG Tables"; break;
						case SWF_SET_BACKGROUND_COLOR:
							type = "Set Background Color"; break;
						case SWF_DEFINE_FONT:
							type = "Define Font"; break;
						case SWF_DEFINE_TEXT:
							type = "Define Text"; break;
						case SWF_DO_ACTION:
							type = "Do Action"; break;
						case SWF_DEFINE_FONT_INFO:
							type = "Define Font Info"; break;
						case SWF_DEFINE_SOUND:
							type = "Define Sound"; break;
						case SWF_START_SOUND:
							type = "Start Sound"; break;
						case SWF_DEFINE_BUTTON_SOUND:
							type = "Define Button Sound"; break;
						case SWF_SOUND_STREAM_HEAD:
							type = "Sound Stream Head"; break;
						case SWF_SOUND_STREAM_BLOCK:
							type = "Sound Stream Block"; break;
						case SWF_DEFINE_BITS_LOSSLESS:
							type = "Define Bits Lossless"; break;
						case SWF_DEFINE_BITS_JPEG_2:
							type = "Define Bits JPEG (2)"; break;
						case SWF_DEFINE_SHAPE_2:
							type = "Define Shape (2)"; break;
						case SWF_DEFINE_BUTTON_CXFORM:
							type = "Define Button CXFORM"; break;
						case SWF_PROTECT:
							type = "Protect"; break;
						case SWF_PLACE_OBJECT_2:
							type = "Place Object (2)"; break;
						case SWF_REMOVE_OBJECT_2:
							type = "Remove Object (2)"; break;
						case SWF_DEFINE_SHAPE_3:
							type = "Define Shape (3)"; break;
						case SWF_DEFINE_TEXT_2:
							type = "Define Text (2)"; break;
						case SWF_DEFINE_BUTTON_2:
							type = "Define Button (2)"; break;
						case SWF_DEFINE_BITS_JPEG_3:
							type = "Define Bits JPEG (3)"; break;
						case SWF_DEFINE_BITS_LOSSLESS_2:
							type = "Define Bits Lossless (2)"; break;
						case SWF_DEFINE_EDIT_TEXT:
							type = "Define Edit Text"; break;
						case SWF_DEFINE_SPRITE:
							type = "Define Sprite"; break;
						case SWF_FRAME_LABEL:
							type = "Frame Label"; break;
						case SWF_SOUND_STREAM_HEAD_2:
							type = "Sound Stream Head (2)"; break;
						case SWF_DEFINE_MORPH_SHAPE:
							type = "Define Morph Shape"; break;
						case SWF_DEFINE_FONT_2:
							type = "Define Font (2)"; break;
						case SWF_EXPORT_ASSETS:
							type = "Export Assets"; break;
						case SWF_IMPORT_ASSETS:
							type = "Import Assets"; break;
						case SWF_ENABLE_DEBUGGER:
							type = "Enable Debugger"; break;
						case SWF_DO_INIT_ACTION:
							type = "Do Init Action"; break;
						case SWF_DEFINE_VIDEO_STREAM:
							type = "Define Video Stream"; break;
						case SWF_VIDEO_FRAME:
							type = "Video Frame"; break;
						case SWF_DEFINE_FONT_INFO_2:
							type = "Define Font Info (2)"; break;
						case SWF_ENABLE_DEBUGGER_2:
							type = "Enable Debugger (2)"; break;
						case SWF_SCRIPT_LIMITS:
							type = "Script Limits"; break;
						case SWF_SET_TAB_INDEX:
							type = "Set Tab Index"; break;
						case SWF_FILE_ATTRIBUTES:
							type = "File Attributes"; break;
						case SWF_PLACE_OBJECT_3:
							type = "Place Object (3)"; break;
						case SWF_IMPORT_ASSETS_2:
							type = "Import Assets (2)"; break;
						case SWF_DEFINE_FONT_ALIGN_ZONES:
							type = "Define Font Align Zones"; break;
						case SWF_CSM_TEXT_SETTINGS:
							type = "CSM Text Settings"; break;
						case SWF_DEFINE_FONT_3:
							type = "Define Font (3)"; break;
						case SWF_SYMBOL_CLASS:
							type = "Symbol Class"; break;
						case SWF_METADATA:
							type = "Metadata"; break;
						case SWF_DEFINE_SCALING_GRID:
							type = "Define Scaling Grid"; break;
						case SWF_DO_ABC:
							type = "Do ABC"; break;
						case SWF_DEFINE_SHAPE_4:
							type = "Define Shape (4)"; break;
						case SWF_DEFINE_MORPH_SHAPE_2:
							type = "Define Morph Shape (2)"; break;
						case SWF_DEFINE_SCENE_AND_FRAME_LABEL_DATA:
							type = "Define Scene and Frame Label Data"; break;
						case SWF_DEFINE_BINARY_DATA:
							type = "Define Binary Data"; break;
						case SWF_DEFINE_FONT_NAME:
							type = "Define Font Name"; break;
						case SWF_START_SOUND_2:
							type = "Start Sound (2)"; break;
						case SWF_DEFINE_BITS_JPEG_4:
							type = "Define Bits JPEG (4)"; break;
						case SWF_DEFINE_FONT_4:
							type = "Define Font (4)"; break;
						case SWF_ENABLE_TELEMETRY:
							type = "Enable Telemetry"; break;
					}
					
					if(type != NULL) printf("%s\n", type);
					else printf("UNKNOWN (%i)\n", tag->type);
				}
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
