/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 08:14:57 by ccolin            #+#    #+#             */
/*   Updated: 2024/09/07 11:19:25 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher()

int	main(int argc, char **argv)
{
	t_parameters	parameters;
	pthread_t		*philosophers;

	if (!intitialize_parameters(argc, argv, &parameters))
		return (0);
	if (!start_philosophers(philosophers, &parameters))
		return (0);
}