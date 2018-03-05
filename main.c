#include "header.h"

int main(int __attribute__ ((unused)) argc, char *argv[], char **env)
{
	shell_t *shs;
	int interactive = 0;

	shs = malloc(sizeof(shell_t));
	if (shs == NULL)
	{
		perror("malloc");
	}
	shs->fp = stdin;
	shs->line = NULL;
	shs->len = 0;
	shs->read = 0;
	shs->cmd = NULL;
	shs->env = NULL;
	shs->argv = NULL;

	shs->argv = argv;

	interactive = _isinteractive();

	env = replicate_env(env); /* take control of environment */
	shs->env = &env;

	if (signal(SIGINT, interrupt_handler) == SIG_IGN)
	{
		signal(SIGINT, SIG_IGN);
	}

	while (1)
	{
		if (interactive)
			print_prompt();

		if (main_loop(shs) != EXIT_SUCCESS)
			return (EXIT_SUCCESS);
		else
			break;
	}

	free(shs);
	return (EXIT_SUCCESS);
}
