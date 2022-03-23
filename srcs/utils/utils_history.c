/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llethuil <llethuil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 10:22:49 by llethuil          #+#    #+#             */
/*   Updated: 2022/03/23 14:39:13 by llethuil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*get_history_path(t_input *input)
{
	char	*path;

	path = ft_strjoin(input, get_value("HOME", input), "/.minishelled_history");
	input->garbage->type = GARBAGE;
	return(path);
}
