/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llethuil <llethuil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 17:07:38 by llethuil          #+#    #+#             */
/*   Updated: 2022/03/07 14:14:48 by llethuil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(int ac, char **av, char **envp)
{
	t_input		input;
	t_cmd_lst	*lst_node;

	(void)av;
	shell_init(ac, envp, &input, &lst_node);
	while (1)
	{
		cmd_line_manager(&input);
		env_parser(&input);
		lexer(&input);
		parser(&input);
		cmd_lst_init(&input, &lst_node);
		executer(envp, &input, &lst_node);
		free_lst(&input, &lst_node);
		free_input_struct(&input);
	}
	free_env_struct(&input);
	return (0);
}
