#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "common.h"
#include "version.h"
#include "action_info.h"
#include "action_list.h"



/// Typedef for function pointers to action implementations
/// @arg fcount The number of files given
/// @arg files All files passed in
typedef int(*action_func_ptr)(args_t *args);



/// Typedef for implementation map entries
typedef struct {
	const char *key;		///< The key for the action
	action_func_ptr func;	///< Function to call if this action is requested
	
	const char *helptext;	///< Descriptive text for --help
} action_entry;

/// Typedef for argument map entries
typedef struct {
	const char skey;		///< Shorthand key for the arg
	const char *lkey;		///< Long key for the arg
	bool *out_flag;			///< Flag to set if the arg is passed
	
	const char *helptext;	///< Descriptive text for --help
} argument_entry;



// Args to pass to functions
args_t arg_data = {0};

// Map of registered actions
action_entry actions[] = {
	{
		"info", &action_info,
		"Print general information about an SWF."
	},
	{
		"list", &action_list,
		"List tags in an SWF."
	},
};

// Map of registered arguments
argument_entry arguments[] = {
	{
		'?', "help", &arg_data.print_help,
		"Print this help message and exit."
	},
	{
		0, "version", &arg_data.print_version,
		"Print the program version and exit."
	},
	{
		'v', "verbose", &arg_data.verbose,
		"Verbose output (does nothing atm)."
	},
};



void print_version()
{
	printf("swftool %i.%i\n", SWFTOOL_VERSION_MAJOR, SWFTOOL_VERSION_MINOR);
}

void print_help()
{
	printf("Usage: swftool [action] [file] <file2> <file...>\n");
	printf("\n");
	
	printf("Actions:\n");
	for(size_t i = 0; i < sizeof(actions)/sizeof(actions[0]); i++)
	{
		printf("    %s\n", actions[i].key);
		printf("        %s\n", actions[i].helptext);
	}
	
	printf("Options:\n");
	for(size_t i = 0; i < sizeof(arguments)/sizeof(arguments[0]); i++)
	{
		printf("    ");
		if(arguments[i].skey != 0) printf("-%c", arguments[i].skey);
		if(arguments[i].skey != 0 && arguments[i].lkey != NULL) printf(", ");
		if(arguments[i].lkey != NULL) printf("--%s", arguments[i].lkey);
		printf("\n");
		
		printf("        %s\n", arguments[i].helptext);
	}
}



int main(int argc, char **argv)
{
	// Pointer to the implementation of the chosen action; func ptrs are nice
	// Default to printing a help message if there's no match
	action_func_ptr action_func = NULL;
	
	// Loop through the arguments, excluding 0 (the program name)
	for(int i = 1; i < argc; i++)
	{
		char *arg = argv[i];
		
		// If it starts with '-', it's a flag
		if(strlen(arg) > 1 && arg[0] == '-')
		{
			// If it starts with "--", it's a single, long flag
			if(arg[1] == '-')
			{
				for(size_t j = 0; j < sizeof(arguments)/sizeof(arguments[0]); j++)
				{
					argument_entry *argument = &(arguments[j]);
					if(argument->lkey != NULL && strcmp(arg + 2, argument->lkey) == 0 && argument->out_flag != NULL)
						*(argument->out_flag) = true;
				}
			}
			// Otherwise it's one or more short flags
			else
			{
				// For short flags, each letter in the string can be a flag
				for(size_t k = 1; k < strlen(arg); k++)
				{
					for(size_t j = 0; j < sizeof(arguments)/sizeof(arguments[0]); j++)
					{
						argument_entry *argument = &(arguments[j]);
						if(arg[k] == argument->skey && argument->out_flag != NULL)
							*(argument->out_flag) = true;
					}
				}
			}
		}
		// If it's not a flag...
		else
		{
			// The first non-flag argument should be the action
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
				
				// Error if we still haven't got an action_func
				if(action_func == NULL)
				{
					printf("ERROR: Unknown action %s\n", arg);
					break;
				}
			}
			// Everything else is a file
			else
			{
				++arg_data.fcount;
				
				// Why doesn't POSIX have OpenBSD's reallocarray yet?
				if(arg_data.files == NULL) arg_data.files = malloc(arg_data.fcount * sizeof(char*));
				else arg_data.files = realloc(arg_data.files, arg_data.fcount * sizeof(char*));
				
				arg_data.files[arg_data.fcount - 1] = arg;
			}
		}
	}
	
	
	
	if(arg_data.print_version)
	{
		print_version();
		return 0;
	}
	
	if(action_func == NULL || arg_data.print_help)
	{
		print_help();
		return (arg_data.print_help ? 0 : 1);
	}
	
	return action_func(&arg_data);
}
