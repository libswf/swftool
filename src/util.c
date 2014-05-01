#include "util.h"
#include <stdlib.h>
#include "constants.h"

SWF* swf_create_from_path(const char *path, SWFError *out_err)
{
    FILE *fp = fopen(path, "rb");
    if(fp)
    {
        return swf_create_from_file(fp, out_err);
    }
    else
    {
        if(out_err != NULL) *out_err = SWF_UNKNOWN;
        return NULL;
    }
}

SWF* swf_create_from_file(FILE *fp, SWFError *out_err)
{
    if(out_err != NULL) *out_err = SWF_OK;
    
    SWFParser *parser = swf_parser_init();
    SWF *swf = swf_parser_get_swf(parser);
    
    char buffer[kFileReadBufferSize];
    size_t size_read = 0;
    while((size_read = fread(buffer, 1, sizeof(buffer), fp)) > 0)
    {
        SWFError err = swf_parser_append(parser, buffer, size_read);
        if(err < 0)
        {
            if(out_err != NULL) *out_err = err;
            break;
        }
    }
    
    swf_parser_free(parser);
    
    return swf;
}
