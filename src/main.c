#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "common.h"
#include "action_help.h"
#include "action_info.h"
#include "action_list.h"



/// Typedef for function pointers to action implementations
/// @arg fcount The number of files given
/// @arg files All files passed in
typedef int(*action_func_ptr)(int fcount, char **files);



/// Typedef for implementation map entries
typedef struct {
	const char *key;		///< The key for the action
	action_func_ptr func;	///< Function to call if this action is requested
} action_entry;

/// Typedef for argument map entries
typedef struct {
	const char skey;		///< Shorthand key for the arg
	const char *lkey;		///< Long key for the arg
	bool *out_flag;			///< Flag to set if the arg is passed
} argument_entry;



int main(int argc, char **argv)
{
	// Args to pass to functions
	args_t arg_data = {0};

	// Map of registered actions
	action_entry actions[] = {
		{ "info", &action_info },
		{ "list", &action_list }
	};

	// Map of registered arguments
	argument_entry arguments[] = {
		{ 'v', "verbose", &arg_data.verbose }
	};
	
	// Pointer to the implementation of the chosen action; func ptrs are nice
	// Default to printing a help message if there's no match
	action_func_ptr action_func = NULL;
	
	for(int i = 1; i < argc; i++)
	{
		char *arg = argv[i];
		
		if(strlen(arg) > 1 && arg[0] == '-')
		{
			if(arg[1] == '-')
			{
				for(size_t j = 0; j < sizeof(arguments)/sizeof(arguments[0]); j++)
				{
					if(strcmp(arg + 2, arguments[j].lkey) == 0 && arguments[j].out_flag != NULL)
						*(arguments[j].out_flag) = true;
				}
			}
			else
			{
				for(size_t k = 1; k < strlen(arg); k++)
				{
					for(size_t j = 0; j < sizeof(arguments)/sizeof(arguments[0]); j++)
					{
						if(arg[k] == arguments[j].skey && arguments[j].out_flag != NULL)
							*(arguments[j].out_flag) = true;
					}
				}
			}
		}
		else
		{
			if(action_func == NULL)
			{
				for(size_t i = 0; i < sizeof(actions)/sizeof(actions[0]); i++)
				{
					if(strcmp(actions[i].key, arg) == 0)
					{
						action_func = actions[i].func;
						break;
					}
				}
			}
			else
			{
				++arg_data.fcount;
				if(arg_data.files == NULL) arg_data.files = malloc(arg_data.fcount * sizeof(char*));
				else arg_data.files = realloc(arg_data.files, arg_data.fcount * sizeof(char*));
				arg_data.files[arg_data.fcount - 1] = arg;
			}
		}
	}
	
	return action_func(arg_data.fcount, arg_data.files);
}
