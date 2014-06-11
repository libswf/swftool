#include "util.h"
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "constants.h"

const char* printable_tag_type(SWFTagType type)
{
	switch(type)
	{
		case SWF_END:
			return "End";
			
		case SWF_SHOW_FRAME:
			return "Show Frame";
			
		case SWF_DEFINE_SHAPE:
			return "Define Shape";
			
		case SWF_PLACE_OBJECT:
			return "Place Object";
			
		case SWF_REMOVE_OBJECT:
			return "Remove Object";
			
		case SWF_DEFINE_BITS:
			return "Define Bits";
			
		case SWF_DEFINE_BUTTON:
			return "Define Button";
			
		case SWF_JPEG_TABLES:
			return "JPEG Tables";
			
		case SWF_SET_BACKGROUND_COLOR:
			return "Set Background Color";
			
		case SWF_DEFINE_FONT:
			return "Define Font";
			
		case SWF_DEFINE_TEXT:
			return "Define Text";
			
		case SWF_DO_ACTION:
			return "Do Action";
			
		case SWF_DEFINE_FONT_INFO:
			return "Define Font Info";
			
		case SWF_DEFINE_SOUND:
			return "Define Sound";
			
		case SWF_START_SOUND:
			return "Start Sound";
			
		case SWF_DEFINE_BUTTON_SOUND:
			return "Define Button Sound";
			
		case SWF_SOUND_STREAM_HEAD:
			return "Sound Stream Head";
			
		case SWF_SOUND_STREAM_BLOCK:
			return "Sound Stream Block";
			
		case SWF_DEFINE_BITS_LOSSLESS:
			return "Define Bits Lossless";
			
		case SWF_DEFINE_BITS_JPEG_2:
			return "Define Bits JPEG (2)";
			
		case SWF_DEFINE_SHAPE_2:
			return "Define Shape (2)";
			
		case SWF_DEFINE_BUTTON_CXFORM:
			return "Define Button CXFORM";
			
		case SWF_PROTECT:
			return "Protect";
			
		case SWF_PLACE_OBJECT_2:
			return "Place Object (2)";
			
		case SWF_REMOVE_OBJECT_2:
			return "Remove Object (2)";
			
		case SWF_DEFINE_SHAPE_3:
			return "Define Shape (3)";
			
		case SWF_DEFINE_TEXT_2:
			return "Define Text (2)";
			
		case SWF_DEFINE_BUTTON_2:
			return "Define Button (2)";
			
		case SWF_DEFINE_BITS_JPEG_3:
			return "Define Bits JPEG (3)";
			
		case SWF_DEFINE_BITS_LOSSLESS_2:
			return "Define Bits Lossless (2)";
			
		case SWF_DEFINE_EDIT_TEXT:
			return "Define Edit Text";
			
		case SWF_DEFINE_SPRITE:
			return "Define Sprite";
			
		case SWF_FRAME_LABEL:
			return "Frame Label";
			
		case SWF_SOUND_STREAM_HEAD_2:
			return "Sound Stream Head (2)";
			
		case SWF_DEFINE_MORPH_SHAPE:
			return "Define Morph Shape";
			
		case SWF_DEFINE_FONT_2:
			return "Define Font (2)";
			
		case SWF_EXPORT_ASSETS:
			return "Export Assets";
			
		case SWF_IMPORT_ASSETS:
			return "Import Assets";
			
		case SWF_ENABLE_DEBUGGER:
			return "Enable Debugger";
			
		case SWF_DO_INIT_ACTION:
			return "Do Init Action";
			
		case SWF_DEFINE_VIDEO_STREAM:
			return "Define Video Stream";
			
		case SWF_VIDEO_FRAME:
			return "Video Frame";
			
		case SWF_DEFINE_FONT_INFO_2:
			return "Define Font Info (2)";
			
		case SWF_ENABLE_DEBUGGER_2:
			return "Enable Debugger (2)";
			
		case SWF_SCRIPT_LIMITS:
			return "Script Limits";
			
		case SWF_SET_TAB_INDEX:
			return "Set Tab Index";
			
		case SWF_FILE_ATTRIBUTES:
			return "File Attributes";
			
		case SWF_PLACE_OBJECT_3:
			return "Place Object (3)";
			
		case SWF_IMPORT_ASSETS_2:
			return "Import Assets (2)";
			
		case SWF_DEFINE_FONT_ALIGN_ZONES:
			return "Define Font Align Zones";
			
		case SWF_CSM_TEXT_SETTINGS:
			return "CSM Text Settings";
			
		case SWF_DEFINE_FONT_3:
			return "Define Font (3)";
			
		case SWF_SYMBOL_CLASS:
			return "Symbol Class";
			
		case SWF_METADATA:
			return "Metadata";
			
		case SWF_DEFINE_SCALING_GRID:
			return "Define Scaling Grid";
			
		case SWF_DO_ABC:
			return "Do ABC";
			
		case SWF_DEFINE_SHAPE_4:
			return "Define Shape (4)";
			
		case SWF_DEFINE_MORPH_SHAPE_2:
			return "Define Morph Shape (2)";
			
		case SWF_DEFINE_SCENE_AND_FRAME_LABEL_DATA:
			return "Define Scene and Frame Label Data";
			
		case SWF_DEFINE_BINARY_DATA:
			return "Define Binary Data";
			
		case SWF_DEFINE_FONT_NAME:
			return "Define Font Name";
			
		case SWF_START_SOUND_2:
			return "Start Sound (2)";
			
		case SWF_DEFINE_BITS_JPEG_4:
			return "Define Bits JPEG (4)";
			
		case SWF_DEFINE_FONT_4:
			return "Define Font (4)";
			
		case SWF_ENABLE_TELEMETRY:
			return "Enable Telemetry";
	}
	
	return NULL;
}

SWFError parse_swf_file(SWFParser *parser, FILE *fp)
{
	if(parser == NULL || fp == NULL) return SWF_UNKNOWN;
	
	char buffer[kFileReadBufferSize];
	size_t size_read = 0;
	while((size_read = fread(buffer, 1, sizeof(buffer), fp)) > 0)
	{
		SWFError err = swf_parser_append(parser, buffer, size_read);
		if(err < 0) return err;
	}
	
	return SWF_OK;
}

int batch_process_files(args_t *args, void(*callback)(SWF *swf))
{
	int retval = 0;
	
	for(int i = 0; i < args->fcount; i++)
	{
		const char *path = args->files[i];
		
		if(args->fcount > 1)
			printf("== %s ==\n", path);
		
		FILE *fp = fopen(path, "rb");
		if(fp)
		{
			SWFParser *parser = swf_parser_init();
			
			if(parse_swf_file(parser, fp) == SWF_OK)
			{
				SWF *swf = swf_parser_get_swf(parser);
				callback(swf);
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
