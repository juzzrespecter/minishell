#include "minishell.h"
#define WORD 1
#define CTRL_OP 2
#define REDIR_OP 3

static int	is_redir_op(char *input)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	if (input[i] == '>')
	{
		len++;
		if (input[i + len] == '>')
			len++;
	}
	if (input[i] == '<')
		len++;
	return (len);
}

static int	is_fd(char *input)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (input[i] && !is_redir_op(input + i))
	{
		i++;
		if (ft_isdigit(input[i]))
			len++;
	}
	return ((i == len) ? len : 0);
}

static int	redir_syntax_error(char *input)
{
	int	i;
	int	j;
	int	op_len;
	int	redir_tested;

	i = 0;
	j = 0;
	redir_tested = 0;
	while (input[i] && !is_ctrl_op(input + i) && !is_blank(input[i]))
	{
		while (input[i + j] && !is_redir_op(input + i + j))
			j++;
		if ((op_len = is_redir_op(input + i + j)))
		{
			j += op_len;
			if (redir_tested > 0 && is_fd(input + i))
				return (i);
			redir_tested++;
		}
		i += j;
		j = 0;
	}
	return (0);
}

static int	is_syntax_error(char *input, int prev_token, t_data *data)
{
	int		err_pos;

	if (prev_token == REDIR_OP)
	{
		data->err = ft_substr(input, 0, is_ctrl_op(input));
		return (1);
	}
	if (input[0] == '<' || input[0] == '>')
	{
		err_pos = redir_syntax_error(input);
		if (err_pos != 0)
		{
			data->err = ft_substr(input, err_pos, is_fd(input + err_pos));
			return (1);
		}				
	}
	else
	{
		if (prev_token == CTRL_OP)
		{
			data->err = ft_substr(input, 0, is_ctrl_op(input));
			return (1);
		}
	}
	return (0);
}

int			parser_error(char *input, t_data *data)
{
	int		i;
	int		prev_token;
	int		quote_ctrl[2];
	int		op_len;

	i = 0;
	quote_ctrl[0] = 0;
	quote_ctrl[1] = 0;
	prev_token = 0;
	while (input[i])
	{
		if (is_quote(input[i], quote_ctrl))
			i++;
		if (is_word(input + i) || (quote_ctrl[0] || quote_ctrl[1]))
		{
			i++;
			prev_token = WORD;
		}
		if ((op_len = is_ctrl_op(input + i)) && !(quote_ctrl[0] || quote_ctrl[1]))
		{
			if (is_syntax_error(input + i, prev_token, data))
				return (258);
			prev_token = CTRL_OP;
			if (input[i] == '<' || input[i] == '>')
				prev_token = REDIR_OP;
			i += op_len;
		}
		else
			i++;
	}
	return (0);
}
