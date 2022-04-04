/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_collector_utils_counter.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llethuil <llethuil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 14:16:10 by llethuil          #+#    #+#             */
/*   Updated: 2022/04/04 10:20:51 by llethuil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	count_n_file(char *cmd, int type)
{
	int	n_red;
	int	i;

	n_red = 0;
	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == '\'' || cmd[i] == '"')
			skip_quotes(cmd, &i);
		if (type == 0)
			if (cmd[i] == '<' && cmd[i + 1] != '<' && cmd[i - 1] != '<')
				n_red ++;
		if (type == 1)
			if (cmd[i] == '>' && cmd[i + 1] != '>' && cmd[i - 1] != '>')
				n_red ++;
		if (type == 2)
			if (cmd[i] == '<' && cmd[i + 1] == '<')
					n_red ++;
		if (type == 3)
			if (cmd[i] == '>' && cmd[i + 1] == '>')
					n_red ++;
	}
	return (n_red);
}

int	count_infile_name_len(char *cmd, int i_file)
{
	static int	cursor = -1;
	int			len;

	if (i_file == 0)
		cursor = -1;
	len = 0;
	while (cmd[++cursor])
	{
		if (cmd[cursor] == '\'' || cmd[cursor] == '"')
			skip_quotes(cmd, &cursor);
		if (cmd[cursor] == '<'
			&& cmd[cursor + 1] != '<' && cmd[cursor - 1] != '<')
		{
			skip_space(cmd, &cursor);
			while (cmd[cursor] && !ft_strchr(" \"\'<>", cmd[cursor]))
			{
				count_out_quotes(&cursor, &len);
				if (cmd[cursor] == '\'' || cmd[cursor] == '"')
					count_in_quotes(cmd, &cursor, &len, cmd[cursor]);
			}
			return (len);
		}
	}
	return (0);
}

int	count_output_name_len(char *cmd, int i_file)
{
	static int	cursor = -1;
	int			len;

	if (i_file == 0)
		cursor = -1;
	len = 0;
	while (cmd[++cursor])
	{
		if (cmd[cursor] == '\'' || cmd[cursor] == '"')
			skip_quotes(cmd, &cursor);
		if (cmd[cursor] == '>'
			&& cmd[cursor + 1] != '>' && cmd[cursor - 1] != '>')
		{
			skip_space(cmd, &cursor);
			while (cmd[cursor] && !ft_strchr(" \"\'<>", cmd[cursor]))
			{
				count_out_quotes(&cursor, &len);
				if (cmd[cursor] == '\'' || cmd[cursor] == '"')
					count_in_quotes(cmd, &cursor, &len, cmd[cursor]);
			}
			return (len);
		}
	}
	return (0);
}

int	count_delimiter_len(char *cmd, int i_file)
{
	static int	cursor = -1;
	int			len;

	if (i_file == 0)
		cursor = -1;
	len = 0;
	while (cmd[++cursor])
	{
		if (cmd[cursor] == '\'' || cmd[cursor] == '"')
			skip_quotes(cmd, &cursor);
		if (cmd[cursor] == '<' && cmd[cursor + 1] == '<')
		{
			skip_space(cmd, &cursor);
			while (cmd[cursor] && !ft_strchr(" \"\'<>", cmd[cursor]))
			{
				count_out_quotes(&cursor, &len);
				if (cmd[cursor] == '\'' || cmd[cursor] == '"')
					count_in_quotes(cmd, &cursor, &len, cmd[cursor]);
			}
			return (len);
		}
	}
	return (0);
}

int	count_app_output_name_len(char *cmd, int i_file)
{
	static int	cursor = -1;
	int			len;

	if (i_file == 0)
		cursor = -1;
	len = 0;
	while (cmd[++cursor])
	{
		if (cmd[cursor] == '\'' || cmd[cursor] == '"')
			skip_quotes(cmd, &cursor);
		if (cmd[cursor] == '>' && cmd[cursor + 1] == '>')
		{
			skip_space(cmd, &cursor);
			while (cmd[cursor] && !ft_strchr(" \"\'<>", cmd[cursor]))
			{
				count_out_quotes(&cursor, &len);
				if (cmd[cursor] == '\'' || cmd[cursor] == '"')
					count_in_quotes(cmd, &cursor, &len, cmd[cursor]);
			}
			return (len);
		}
	}
	return (0);
}
