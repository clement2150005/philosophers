/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 08:14:57 by ccolin            #+#    #+#             */
/*   Updated: 2024/12/10 17:12:01 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long long	time_us(unsigned long long start)
{
	struct timeval		tv;
	unsigned long long	current_us;

	gettimeofday(&tv, NULL);
	current_us = (tv.tv_sec * 1000000) + tv.tv_usec;
	if (start)
		return (current_us - start);
	return (current_us);
}

void	end_philosophers(pthread_t **philosophers, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (i < n)
	{
		pthread_join((*philosophers)[i++], NULL);
	}
}

pthread_mutex_t	*set_the_table(t_param *param)
{
	pthread_mutex_t	*forks_locks;
	unsigned int	i;

	i = 0;
	forks_locks = malloc(sizeof(pthread_mutex_t)
			* param->number_of_philosophers);
	if (!forks_locks)
		return (NULL);
	while (i < param->number_of_philosophers)
	{
		if (pthread_mutex_init(&forks_locks[i], NULL) != 0)
		{
			while (--i != 0)
				pthread_mutex_destroy(&forks_locks[i]);
			free(forks_locks);
			return (NULL);
		}
		i++;
	}
	return (forks_locks);
}

int	main(int argc, char **argv)
{
	t_param			param;
	pthread_t		*philosophers;
	pthread_t		*grim_reaper;
	pthread_mutex_t	*forks_locks;

	philosophers = NULL;
	if (!intitialize_param(argc, argv, &param))
		return (0);
	forks_locks = set_the_table(&param);
	grim_reaper = malloc(sizeof(pthread_t));
	if (!grim_reaper)
		return (0);
	if (start_philosophers(&philosophers, &param, &forks_locks))
		return (0);
	if (pthread_create(grim_reaper, NULL, gr_routine, gr_args(&param,
				philosophers)))
	{
		err("Thread creation failed");
		return (0);
	}
	pthread_join(*grim_reaper, NULL);
	end_philosophers(&philosophers, param.number_of_philosophers);
	return (0);
}
