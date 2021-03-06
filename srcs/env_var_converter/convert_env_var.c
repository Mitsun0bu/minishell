/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llethuil <llethuil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 18:58:03 by llethuil          #+#    #+#             */
/*   Updated: 2022/05/05 15:22:38 by llethuil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static char	*get_exit_status(t_input *input, char *str, int i, int redir);
static char	*get_key_to_process(t_input *input, char *str, int *i);
static int	is_first_command(char *str, int limit);
static char	*get_env_var_value(t_input *input, char *str, int *i, int red);

char	*convert_env_var(t_input *input, char *str, int *i, int red)
{
	char	*value;

	value = ft_strdup(input, "");
	input->gb->type = GARBAGE;
	if (str[*i + 1] == '?')
	{
		value = get_exit_status(input, str, *i, red);
		input->gb->type = GARBAGE;
		*i += 2;
	}
	else
		value = get_env_var_value(input, str, i, red);
	if (value)
		return (value);
	return ("");
}

static char	*get_exit_status(t_input *input, char *str, int i, int redir)
{
	char	*value;

	if (redir == HEREDOC)
		value = ft_strdup(input, "$?");
	else if (is_first_command(str, i))
		value = ft_itoa(input, g_status);
	else
		value = ft_strdup(input, "0");
	return (value);
}

static int	is_first_command(char *str, int limit)
{
	int	i;

	i = -1;
	while (++i < limit)
	{
		if (ft_strchr("\"\'", str[i]))
			skip_quotes(str, &i);
		if (str[i] == '|')
			return (0);
	}
	return (1);
}

static char	*get_env_var_value(t_input *input, char *str, int *i, int red)
{
	char	*key;
	char	*value;

	key = get_key_to_process(input, str, i);
	value = ft_strdup(input, "");
	input->gb->type = GARBAGE;
	if (red == HEREDOC)
	{
		value = ft_strjoin(input, "$", key);
		input->gb->type = GARBAGE;
		return (value);
	}
	if (ft_strcmp("$", key) == SUCCESS)
		return ("$");
	return (get_value_from_key(input, key));
}

static char	*get_key_to_process(t_input *input, char *str, int *i)
{
	char	*key;
	int		start;

	start = (*i) + 1;
	while (str[++(*i)])
		if (!ft_isalnum(str[*i]) && str[*i] != '_')
			break ;
	if (start == *i)
		key = ft_strdup(input, "$");
	else
		key = ft_substr(input, str, start, *i - start);
	input->gb->type = GARBAGE;
	return (key);
}
