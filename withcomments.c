#include "ourshell.h"

int main(int ac, char **argv)
{
    // Set the prompt for the shell
    char *prompt = "ourshell$ ";

    // Variables to store user input and its details
    char *lineptr, *lineptr_copy = NULL;
    size_t n = 0;
    ssize_t nchars_read;

    // Delimiter used to split the input into separate parts
    const char *delim = " \n";

    // Count the number of tokens (separate parts) in the input
    int no_tokens = 0;

    // Variables for tokenizing the input
    char *token;
    int j;

    // Ignore the command-line arguments passed to the program
    (void)ac;
    (void)argv;

    while(1)
    {
        // Print the shell prompt to ask for input
        printf("%s", prompt);

        // Read the input line from the user
        nchars_read = getline(&lineptr, &n, stdin);

        // Check if it's the end of input
        if (nchars_read == -1){
            printf("Exit ourshell\n");
            return (-1);
        }

        // Allocate memory to make a copy of the input line
        lineptr_copy = malloc(sizeof(char) * nchars_read);
        if (lineptr_copy == NULL){
            perror("tsh: memory allocation error");
            return (-1);
        }
        
        // Copy the input line to the copy variable
        strcpy(lineptr_copy, lineptr);

        // Count the number of separate parts (tokens) in the input
        token = strtok(lineptr, delim);
        while (token != NULL){
            no_tokens++;
            token = strtok(NULL, delim);
        }
        no_tokens++;

        // Allocate memory to store the separate parts (tokens)
        argv = malloc(sizeof(char *) * no_tokens);

        // Store each token in the argument vector array
        token = strtok(lineptr_copy, delim);
        for (j = 0; token != NULL; j++){
            // Allocate memory for each token and copy it
            argv[j] = malloc(sizeof(char) * strlen(token));
            strcpy(argv[j], token);

            token = strtok(NULL, delim);
        }
        argv[j] = NULL;

        // Print the user's input line
        printf("%s\n", lineptr);

        // Free allocated memory and reset variables for the next iteration
        free(lineptr);
        n = 0;
        lineptr = NULL;
    }

    return (0);
}
