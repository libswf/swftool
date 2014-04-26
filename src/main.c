#include "action_help.h"
#include "action_info.h"

// Typedef for function pointers to action implementations
typedef void(*action_func_ptr)(int fcount, const char **files);

int main(int argc, char **argv)
{
	// Pointer to the implementation of the chosen action; func ptrs are nice
	// Default to printing a help message if there's no match
	action_func_ptr action_func = &action_help;
	
	if(argc >= 3)
	{
		const char *action_str = argv[1];
		
		if(strcmp(action_str, "info") == 0)
			action_func = &action_info;
	}
	
	action_func((argc >= 3 ? argc - 2 : 0), argv[2]);
	
	return 0;
}
