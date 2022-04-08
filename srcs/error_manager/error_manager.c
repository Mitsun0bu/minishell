/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llethuil <llethuil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 13:22:25 by llethuil          #+#    #+#             */
/*   Updated: 2022/04/08 17:19:30 by llethuil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	stderror_return(int error, char *who, char *problem, char *err_message)
{
	if (!who)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(problem, 2);
		ft_putstr_fd(": ", 2);
	}
	if (who)
	{
		ft_putstr_fd(who, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(problem, 2);
		ft_putstr_fd(": ", 2);
	}
	if (err_message)
	{
		ft_putstr_fd(err_message, 2);
		ft_putstr_fd("\n", 2);
	}
	return (error);
}

int	stderror_exit(t_input *input, int error, char *problem, char *err_message)
{
	if (problem)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(problem, 2);
		ft_putstr_fd(": ", 2);
	}
	if (err_message)
	{
		ft_putstr_fd(err_message, 2);
		ft_putstr_fd("\n", 2);
	}
	clear_all_garbage(&input->garbage);
	tcsetattr(STDIN_FILENO, TCSANOW, &input->old_term);
	exit(error);
}