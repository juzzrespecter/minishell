#include "test.h"

char	*search_env(char **env, char *name)
{
	char	*value;
	int	name_len;
	int	i;

	name_len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(name, env[i], name_len) && env[i][name_len] == '=')
			return (env[i]);
		i++;
	}
	return (NULL);
}

int	is_quote(char input, int quote_ctrl[2])
{
	if (input == '\'')
	{
		if (quote_ctrl[1] == 1)
			return (0);
		if (quote_ctrl[0] == 1)
			quote_ctrl[0] = 0;
		else
			quote_ctrl[0] = 1;
		return (1);
	}
	if (input == '\"')
	{
		if (quote_ctrl[0] == 1)
			return (0);
		if (quote_ctrl[1] == 1)
			quote_ctrl[1] = 0;
		else
			quote_ctrl[1] = 1;
		return (1);
	}
	return (0);
}

int	is_var(char input)
{
	if (ft_isalnum(input) || input == '_')
		return (1);
	return (0);
}

int	is_word(char input)
{
	if (!ft_strrchr(";|\n\t\v\r ", input))
		return (1);
	return (0);
}

int	is_blank(char input)
{
	if (!ft_strrchr(" \t\v\f\r", input))
		return (0);
	return (1);
}

int	is_ctrl_op(char input)
{
	if (!ft_strrchr(";|\n", input))
		return (0);
	return (1);
}
