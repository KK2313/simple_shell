#include "ourshell.h"

int main(int ac, char **argv)
{
	char *prompt = "ourshell$ ";
	char *lineptr, *lineptr_copy = NULL;
	size_t n = 0;
	ssize_t nchars_read;
	const char *delim = " \n";
	int no_tokens = 0;
	char *token;
	int j;

	(void)ac;
	(void)argv;

	while(1)
	{
	printf("%s", prompt);
	nchars_read = getline(&lineptr, &n, stdin);

	if (nchars_read == -1){
		printf("Exit ourshell\n");
		return (-1);
	}

	lineptr_copy = malloc(sizeof(char) * nchars_read);
	if (lineptr_copy== NULL){
			perror("tsh: memory allocation error");
			return (-1);
		}


	strcpy(lineptr_copy, lineptr);

	token = strtok(lineptr, delim);

	while (token != NULL){
		no_tokens++;
		token = strtok(NULL, delim);
	}
	no_tokens++;


	argv = malloc(sizeof(char *) * no_tokens);
	
	token = strtok(lineptr_copy, delim);

	for (j = 0; token != NULL; j++){
			argv[j] = malloc(sizeof(char) * strlen(token));
			strcpy(argv[j], token);

			token = strtok(NULL, delim);
			}
	argv[j] = NULL;


	printf("%s\n", lineptr);
	
	free(lineptr);
	n = 0;
	lineptr = NULL;
	}

	return (0);
}
