#include "action_help.h"
#include <stdio.h>

int action_help(int fcount, char **files)
{
	printf("Usage: swftool [action] [file(s)]\n");
	printf("    \n");
	printf("Actions:\n");
	printf("    info - Print information about the given file(s)\n");
	
	return 0;
}
