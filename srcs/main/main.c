/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llethuil <llethuil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 17:07:38 by llethuil          #+#    #+#             */
/*   Updated: 2022/05/16 16:27:15 by llethuil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	g_status = 0;

int	main(int ac, char **av, char **envp)
{
	t_input		input;
	t_cmd_lst	*cmd;

	cmd = NULL;
	shell_initializer(ac, av, envp, &input);
	while (1)
	{
		if (cmd_line_manager(&input) == SUCCESS)
		{
			if (cmd_separator(&input) == SUCCESS)
			{
				redir_collector(&input);
				arg_separator(&input);
				cmd_lst_init(&input, &cmd);
				executer(&input, cmd);
				clear_one_gb_type(&input.gb, CMD_LST);
				clear_one_gb_type(&input.gb, CMD_LINE);
				clear_one_gb_type(&input.gb, CMD_TAB);
			}
		}
		clear_one_gb_type(&input.gb, INPUT_STRUCT);
		clear_one_gb_type(&input.gb, GARBAGE);
	}
}
