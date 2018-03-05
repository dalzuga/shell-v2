#include "header.h"

int main_loop(shell_t *shs)
{
	shs->read = getline(&(shs->line), &(shs->len), shs->fp);
	if (shs->fp == NULL)
	{
		/* if fp is a file which failed to open */
		perror((shs->argv)[0]);
		return (EXIT_FAILURE);
	}

	if (shs->read == EOF) /* handle Ctrl+D */
	{
		_free(shs->line);
		free_env(*(shs->env));
		if (errno == 0)
			return (EXIT_SUCCESS);
		perror((shs->argv)[0]);
		return (EXIT_FAILURE);
	}

	shs->cmd = strtok(shs->line, " \n");
	/* handles newline (empty command) + checks for built in */
	if (shs->cmd != NULL && handle_builtins(shs->cmd, shs->line, shs->env))
	{
		canary("exec begins");

		/**
		 * PROGRAM EXEC
		 * fork() begins here
		 */

		if (handle_exec(shs->cmd, shs->line, shs->env))
		{
			canary("hello");
			free_env(*(shs->env));
			perror((shs->argv)[0]);
			return (EXIT_FAILURE);
		}
	}

	return (972);
}
