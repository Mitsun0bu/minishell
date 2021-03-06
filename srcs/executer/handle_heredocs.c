/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredocs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llethuil <llethuil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:38:12 by llethuil          #+#    #+#             */
/*   Updated: 2022/05/19 09:54:42 by llethuil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	get_heredoc_str(t_input *input, t_cmd_lst *cmd);
static int	get_str_from_child(t_input *input, t_cmd_lst *cmd, char *str);

int	handle_heredocs(t_input *input, t_cmd_lst *cmd)
{
	t_cmd_lst	*start;

	start = cmd;
	while (cmd)
	{
		if (cmd->n_heredoc)
			if (get_heredoc_str(input, cmd) != 0)
				return (FAILED);
		cmd = cmd->next;
	}
	cmd = start;
	return (0);
}

static int	get_heredoc_str(t_input *input, t_cmd_lst *cmd)
{
	char	*str;

	str = NULL;
	if (open_single_pipe(cmd->heredoc_pipe) == FAILED)
		return (FAILED);
	set_signals(EXEC);
	cmd->heredoc_process = fork();
	check_fork_error(cmd->heredoc_process);
	if (cmd->heredoc_process == CHILD)
		g_status = get_str_from_child(input, cmd, str);
	waitpid(cmd->heredoc_process, &g_status, 0);
	if (WIFEXITED(g_status) && WEXITSTATUS(g_status) == 1)
		g_status = 1;
	else
		g_status = 0;
	set_signals(MAIN);
	return (g_status);
}

static int	get_str_from_child(t_input *input, t_cmd_lst *cmd, char *str)
{
	int	i;

	i = -1;
	set_signals(HEREDOC);
	while (++i < cmd->n_heredoc)
		str = build_heredoc_str(input, cmd->del[i]);
	if (!str)
		exit(FAILED);
	str = convert_env_var_in_str(input, str);
	input->gb->type = GARBAGE;
	ft_putstr_fd(str, cmd->heredoc_pipe[1]);
	exit (0);
}
