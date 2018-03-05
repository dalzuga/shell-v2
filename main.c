#include "header.h"

int main(int __attribute__ ((unused)) argc, char *argv[], char **env)
{
	FILE *fp = 0;
	char *line = NULL;
	size_t len = 0;
	ssize_t read = 0;
	char *cmd = NULL;
	int interactive;
	fp = stdin;
	interactive = _isinteractive();
	env = replicate_env(env); /* take control of environment */
	if (signal(SIGINT, interrupt_handler) == SIG_IGN)
		signal(SIGINT, SIG_IGN);
	while (1)
	{
		if (interactive)
			print_prompt();
		read = getline(&line, &len, fp);
		if (fp == NULL)
		{
			perror(argv[0]); /* if fp file failed to open */
			return (EXIT_FAILURE);
		}
		if (read == EOF) /* handle Ctrl+D */
		{
			_free(line);
			free_env(env);
			if (errno == 0)
				return (EXIT_SUCCESS);
			perror(argv[0]);
			return (EXIT_FAILURE);
		}
		handle_comments(line);
		cmd = strtok(line, " \n");
		main_2(cmd, line, env, argv);
	}
	return (EXIT_SUCCESS);
}

void main_2(char *cmd, char *line, char **env, char **argv)
{
		if (cmd != NULL && handle_builtins(cmd, line, &env))
		{
			if (handle_exec(cmd, line, &env))
			{
				free_env(env);
				perror(argv[0]);
				exit(EXIT_FAILURE);
			}
		}
}
