#include "main.h"

/**
 * free_recurr_data - free the field in each loop
 * @data: struct of the program's data
 * Return: Nothing
 */
void free_recurr_data(data_of_program *data)
{
	if (data->tokens)
		free_array_of_pointers(data->tokens);
	if (data->input_line)
		free(data->input_line);
	if (data->command_name)
		free(data->command_name);

	data->input_line = NULL;
	data->command_name = NULL;
	data->tokens = NULL;
}

/**
 * free_all_data - free all field of the data
 * @data: struct of the program's data
 * Return: Nothing
 */
void free_every_data(data_of_program *data)
{
	if (data->file_descriptor != 0)
	{
		if (close(data->file_descriptor))
			perror(data->program_name);
	}
	free_recurr_data(data);
	free_array_of_pointers(data->env);
	free_array_of_pointers(data->alias_list);
}

/**
 * free_array_of_pointers - frees each pointers of array
 * @array: array of pointers
 * Return: nothing
 */
void free_array_of_pointers(char **arr)
{
	int j;

	if (arr != NULL)
	{
		for (j = 0; arr[j]; j++)
			free(arr[j]);

		free(arr);
		arr = NULL;
	}
}
