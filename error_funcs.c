#include "minishell.h"

int		janitor(char **argv, t_data *data, int err_code)
{
	int	i;
	int	exit_status;

	i = 0;

	/* cuatro casos:
	 * 127 - cmd not found
	 * errno == 2 - no such file or directory (stderror)
	 * errno == 13 - cannot be executed (perm denied)
	 * otro errno
	 *
	 * caso 1 & 2 devuelve 127
	 * caso 3 devuelve 126
	 * caso 4 devuelve 128 + n
	 */

	exit_status = 0;
	if (err_code == 127)
		exit_status = print_error(argv[0], NULL, "command not found", err_code);
	if (err_code == 2)
		exit_status = print_error(argv[0], NULL, strerror(errno), 127);
	if (err_code == 13)
		exit_status = print_error(argv[0], NULL, strerror(errno), 126);
	if (err_code != 2 && err_code != 13 && err_code != 127)
		exit_status = print_error(argv[0], NULL, strerror(errno), errno + 128);
	if (argv != NULL)
		free_inputs(argv);
	free_env(data->env);
	return (exit_status);
}

void	free_inputs(char **inputs)
{
	int	i;

	i = 0;
	while (inputs[i])
	{
		free(inputs[i]);
		i++;
	}
	free(inputs);
}

int		print_error(char *cmd, char *arg, char *err_msg, int exit_code)
{
	write(2, "bash: ", 6);
	if (cmd != NULL)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": ", 2);
	}
	if (arg != NULL)
	{
		write(2, arg, ft_strlen(arg));
		write(2, ": ", 2);
	}
	write(2, err_msg, ft_strlen((err_msg)));
	write(2, "\n", 1);
	g_status = exit_code;
	return (exit_code);
}


// func montar error para identificadores no validos
// (strjoin)
