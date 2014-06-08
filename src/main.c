#include <string.h>
#include "action_help.h"
#include "action_info.h"
#include "action_list.h"

// Typedef for function pointers to action implementations
typedef int(*action_func_ptr)(int fcount, char **files);

// Typedef for implementation map entries
typedef struct {
	const char *key;
	action_func_ptr func;
} action_entry;

int main(int argc, char **argv)
{
	// Map of registered actions
	action_entry actions[] = {
		{ "info", &action_info },
		{ "list", &action_list }
	};
	
	// Pointer to the implementation of the chosen action; func ptrs are nice
	// Default to printing a help message if there's no match
	action_func_ptr action_func = &action_help;
	
	if(argc >= 3)
	{
		const char *action_str = argv[1];
		
		for(unsigned i = 0; i < sizeof(actions)/sizeof(actions[0]); i++)
			if(strcmp(action_str, actions[i].key) == 0)
				{ action_func = actions[i].func; break; }
	}
	
	return action_func((argc >= 3 ? argc - 2 : 0), argv + 2);
}
