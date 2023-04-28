#include "main.h"
/**
 * main - initialize variables
 * @argc: no. of values from command line
 * @argv: values from the command line
 * @env: no. of values received from command line
 * Return:0 when successful
 */
int main(int argc, char *argv[], char *env[])
{
	data_of_program data_struct = {NULL}, *dataVal = &data_struct;
	char *promptStr = "";

	init_data(dataVal, argc, argv, env);

	signal(SIGINT, ctrl_c_handler);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{
		errno = 2;
		promptStr = PROMPT_MSG;
	}
	errno = 0;
	infi_prompt(promptStr, dataVal);
	return (0);
}

/**
 * ctrl_c_handler - print new line prompt SIGINT (ctrl + c) is pressed
 * @UNUSED: option of the prototype
 */
void ctrl_c_handler(int opr UNUSED)
{
	_print("\n");
	_print(PROMPT_MSG);
}

/**
 * init_data - init the struct with the program info
 * @data: pointer
 * @argv: array of arg passed to program
 * @env: environ passed to the program
 * @argc: no of values received from the command line
 */
void init_data(data_of_program *data, int argc, char *argv[], char **env)
{
	int i = 0;

	data->program_name = argv[0];
	data->input_line = NULL;
	data->command_name = NULL;
	data->exec_counter = 0;

	if (argc == 1)
		data->file_descriptor = STDIN_FILENO;
	else
	{
		data->file_descriptor = open(argv[1], O_RDONLY);
		if (data->file_descriptor == -1)
		{
			_printe(data->program_name);
			_printe(": 0: Can't open ");
			_printe(argv[1]);
			_printe("\n");
			exit(127);
		}
	}
	data->tokens = NULL;
	data->env = malloc(sizeof(char *) * 50);
	if (env)
	{
		for (; env[i]; i++)
		{
			data->env[i] = str_duplicate(env[i]);
		}
	}
	data->env[i] = NULL;
	env = data->env;

	data->alias_list = malloc(sizeof(char *) * 20);
	for (i = 0; i < 20; i++)
	{
		data->alias_list[i] = NULL;
	}
}
/**
 * infi_prompt - its a infinite loop that shows the prompt
 * @prompt: prompt to be printed
 * @data: infinite loop to display prompt
 */
void infi_prompt(char *prompt, data_of_program *data)
{
	int err_code = 0, str_len = 0;

	while (++(data->exec_counter))
	{
		_print(prompt);
		err_code = str_len = _getline(data);

		if (err_code == EOF)
		{
			free_every_data(data);
			exit(errno);
		}
		if (str_len >= 1)
		{
			expand_alias(data);
			expand_variables(data);
			tokenize(data);
			if (data->tokens[0])
			{
				err_code = execute(data);
				if (err_code != 0)
					_print_error(err_code, data);
			}
			free_recurr_data(data);
		}
	}
}
