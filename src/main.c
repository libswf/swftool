#include <stdio.h>

int main(int argc, char **argv)
{
	if(argc < 3)
	{
		printf("Usage: swftool [action] [file(s)]\n");
		printf("    \n");
		printf("Actions:\n");
		printf("    info - Print information about the given file(s)\n");
		
		return 1;
	}
	
	for(int i = 1; i < argc; ++i)
	{
		printf("%s\n", argv[i]);
	}
	
	return 0;
}
