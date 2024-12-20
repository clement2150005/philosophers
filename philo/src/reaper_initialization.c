/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper_initialization.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:17:50 by ccolin            #+#    #+#             */
/*   Updated: 2024/12/15 11:40:55 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*reaper_args(t_param *param, int id)
{
	t_reaper_arg	*reaper_arg;

	reaper_arg = malloc(sizeof(t_reaper_arg));
	if (!reaper_arg)
		return (NULL);
	reaper_arg->param = param;
	reaper_arg->id = id;
	return ((void *)reaper_arg);
}
