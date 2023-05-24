#include "ourshell.h"

/**
 * recurrent_data_free - function to keep the buffers clean
 * @data: ..
 */
void recurrent_data_free(data_of_program *data)
{
    if (data->tokens)
        free_pointers_array(data->tokens);
    if (data->input_line)
        free(data->input_line);
    if (data->command_name)
        free(data->command_name);

    data->input_line = NULL;
    data->command_name = NULL;
    data->tokens = NULL;
}

/**
 * clean_data - free all data
 * @data: ..
 */
void clean_data(data_of_program *data)
{
    if (data->file_descriptor != 0)
    {
        if (close(data->file_descriptor))
            perror(data->program_name);
    }
    recurrent_data_free(data);
    free_array_pointers(data->env);
    free_array_pointers(data->alias_list);
}

/**
 * free_array_pointers - ..
 * @myarrays: array of pointers
 */
void free_array_pointers(char **myarrays)
{
    int i;

    if (myarrays != NULL)
    {
        for (i = 0; myarrays[i]; i++)
            free(myarrays[i]);

        free(myarrays);
    }
}
