#include "util.h"
#include <stdlib.h>
#include "constants.h"

SWF* swf_create_from_file(FILE *fp, SWFError *out_err)
{
    if(out_err != NULL) *out_err = SWF_OK;
    
    SWFParser *parser = swf_parser_init();
    SWF *swf = swf_parser_get_swf(parser);
    
    // This code can correctly duplicate a 34kb text file (`diff` says no difference)
    // libswf errors out with SWF_INVALID instead, if fed the file in chunks
    /*char buffer[kFileReadBufferSize];
    size_t size_read = 0;
    while((size_read = fread(buffer, 1, sizeof(buffer), fp)) > 0)
    {
        SWFError err = swf_parser_append(parser, buffer, size_read);
        if(err < 0)
        {
            if(out_err != NULL) *out_err = err;
            break;
        }
    }*/
    
    // This is far less efficient, but it's a workaround for a libswf bug
    fseek(fp, 0, SEEK_END);
    size_t size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    
    void *buffer = malloc(size);
    fread(buffer, 1, size, fp);
    SWFError err = swf_parser_append(parser, buffer, size);
    if(out_err != NULL && err < 0) *out_err = err;
    free(buffer);
    
    swf_parser_free(parser);
    
    return swf;
}
