/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_manager_app_output.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llethuil <llethuil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 13:25:05 by llethuil          #+#    #+#             */
/*   Updated: 2022/03/07 11:43:39 by llethuil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	malloc_app_output_redir_tab(t_input *input)
{
	int	i_cmd;
	int	n_red;

	i_cmd = -1;
	while (input->cmd_tab[++i_cmd])
	{
		n_red = count_app_output_redir(input->cmd_tab[i_cmd]);
		if (!n_red)
		{
			input->redir_tab[i_cmd][3] = safe_malloc(sizeof(char *), 2);
			input->redir_tab[i_cmd][3][0] = NULL;
		}
		else
		{
			input->redir_tab[i_cmd][3] = safe_malloc(sizeof(char *), (n_red + 1));
			input->redir_tab[i_cmd][3][n_red] = NULL;
		}
	}
	return (0);
}

int	count_app_output_redir(char *cmd)
{
	int	n_red;
	int	i;

	n_red = 0;
	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == '\'' || cmd[i] == '"')
			skip_quotes(cmd, &i);
		if (cmd[i] == '>' && cmd[i + 1] == '>')
			n_red ++;
	}
	return (n_red);
}

int	malloc_app_output_name(t_input *input, int *i_cmd)
{
	int	i_red;
	int	len;

	len = 0;
	i_red = -1;
	while (++i_red < count_app_output_redir(input->cmd_tab[*i_cmd]))
	{
		len = count_app_output_name_len(input->cmd_tab[*i_cmd], &i_red);
		input->redir_tab[*i_cmd][3][i_red] = safe_malloc(sizeof(char), (len + 1));
		input->redir_tab[*i_cmd][3][i_red][len] = '\0';
	}
	return (0);
}

int	count_app_output_name_len(char *cmd, int *i_red)
{
	static int	i = -1;
	int			len;

	if (*i_red == 0)
		i = -1;
	len = 0;
	while (cmd[++i])
	{
		if (cmd[i] == '\'' || cmd[i] == '"')
			skip_quotes(cmd, &i);
		if (cmd[i] == '>' && cmd[i + 1] != '>')
		{
			skip_space(cmd, &i);
			while (cmd[i] && !ft_strchr(" \"\'<>", cmd[i]))
				count_out_quotes(&i, &len);
			if (cmd[i] == '\'' || cmd[i] == '"')
				count_in_quotes(cmd, &i, &len, cmd[i]);
			while (cmd[i] && !ft_strchr(" <>", cmd[i]))
				count_out_quotes(&i, &len);
			i --;
			return (len);
		}
	}
	return (0);
}
