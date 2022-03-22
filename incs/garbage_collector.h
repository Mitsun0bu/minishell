/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llethuil <llethuil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:51:26 by llethuil          #+#    #+#             */
/*   Updated: 2022/03/22 19:33:04 by llethuil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                               ~~~ DEFINES ~~~                              */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRABAGE_COLLECTOR_H
# define GRABAGE_COLLECTOR_H

/* ************************************************************************** */
/*                                                                            */
/*                               ~~~ INCLUDES ~~~                             */
/*                                                                            */
/* ************************************************************************** */

# include "main.h"

/* ************************************************************************** */
/*                                                                            */
/*                              ~~~ PROTOTYPES ~~~                            */
/*                                                                            */
/* ************************************************************************** */

/* garbage_collector/garbage_collector.c */
t_garbage_lst	*create_new_garbage(void *ptr, int type);
void			add_garbage_front(t_garbage_lst **gc, t_garbage_lst *new);
void			clear_all_garbage(t_garbage_lst **garbage);
void			clear_one_garbage_type(t_garbage_lst **garbage, int type);

#endif