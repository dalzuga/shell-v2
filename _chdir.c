#include "header.h"

/**
 * _chdir - change current directory, and update PWD and OLDPWD environment
 * variables.
 *
 * @dest: directory to change to
 * @env: the current environment
 *
 * Return: On success, return 0. On error, return -1.
 */
int _chdir(char *dest, char ***env)
{
	char *OLDPWD_value = NULL, *PWD_value = NULL, *buf = NULL;

	buf = _getcwd();
	_setenv_func(env, "OLDPWD", buf);
	free(buf);
	chdir(dest);

	buf = _getcwd();
	_setenv_func(env, "PWD", buf);
	free(buf);

	if (DEBUG == 1)
	{
		printf("env is: %p\n", (void *) env);
		canary(PWD_value);
		canary(OLDPWD_value);
	}

	return (0);
}

/**
 * _getcwd - returns current working directory string using standard library
 * call. The user of this function must free the returned allocated memory.
 *
 * Return: On success, return the cwd. On error, exit with EXIT_FAILURE.
 */
char *_getcwd(void)
{
	char *buf = NULL;
	size_t buf_size = 0;

	while (1)
	{
		buf = getcwd(buf, buf_size);
		if (buf != NULL)
		{
			errno = 0;	/* avoid undefined behavior */
			break;
		}

		buf_size += BUF_SIZE; /* increase buffer size (linearly) */
		if (buf_size > 0)
			free(buf);
		buf = malloc(sizeof(char) * buf_size);
		if (buf == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
	}

	return (buf);
}
