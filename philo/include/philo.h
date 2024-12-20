/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 17:24:14 by ccolin            #+#    #+#             */
/*   Updated: 2024/12/15 17:35:58 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

//==========================================================================//
//									LIBRARIES								//
//==========================================================================//
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

//==========================================================================//
//									STRUCTURES								//
//==========================================================================//
typedef struct s_param
{
	unsigned long long	strt;
	unsigned int		nb_philo;
	unsigned long long	time_to_die;
	unsigned long long	time_to_eat;
	unsigned long long	time_to_sleep;
	unsigned long long	num_eats_per_philosopher;
	unsigned long long	*dth_time;
	int					is_alive;
	pthread_mutex_t		*eating_lock;
	pthread_mutex_t		*finished_lock;
	unsigned int		finished;
	int					*status;
	int					*forks;
}						t_param;

typedef struct s_philo_arg
{
	unsigned int		id;
	unsigned int		meal;
	pthread_mutex_t		*frk_lock;
	t_param				*param;
}						t_philo_arg;

typedef struct s_reaper_arg
{
	unsigned int		id;
	t_param				*param;
}						t_reaper_arg;

//==========================================================================//
//									MACROS									//
//==========================================================================//
# define EATING 100
# define ALIVE 101
# define DEAD 0
# define ON_THE_TABLE 102
# define USED 0

//==========================================================================//
//									  FUNCTIONS								//
//==========================================================================//

//==============================>> CLEANUP.C <<=============================//
void				cleanup_1(t_param *param);
void				cleanup_2(t_param *param, pthread_mutex_t *frk_lock);
void				cleanup_3(t_param *param, pthread_mutex_t *frk_lock);
void				cleanup_4(t_param *param, pthread_mutex_t *frk_lock);
void				cleanup_5(t_param *param, pthread_mutex_t *frk_lock);

//===============================>> MAIN.C <<===============================//
int					init_simulation(int argc, char **argv, t_param *param,
						pthread_mutex_t **frk_lock);
int					main(int argc, char **argv);
void				end_philo(pthread_t **philo, unsigned int n);
void				clean_the_table(int nb_philo, pthread_mutex_t *mutex);

//===========================>> MAKE_MUTEXES.C <<===========================//
pthread_mutex_t		*make_fork_mutexes(t_param *param);
pthread_mutex_t		*make_eating_mutexes(t_param *param,
						pthread_mutex_t *frk_lock);
pthread_mutex_t		*make_finish_mutexes(t_param *param,
						pthread_mutex_t *frk_lock);

//====================>> PARAMETERS_INITIALIZATION.C <<=====================//
int					str_is_not_digits_only(char *str);
int					check_param(t_param *param, int argc);
unsigned long long	get_parameter(char *str);
int					allocate_param_memory(t_param *param);
int					intitialize_param(int argc, char **argv, t_param *param);

//=========================>> PHILO_ROUTINE.C <<============================//
void				sleeping(t_philo_arg *args);
void				swap_forks(unsigned int *left, unsigned int *right);
void				take_forks(t_philo_arg *args, unsigned int *left,
						unsigned int *right);
void				eating(t_philo_arg *args);
void				*routine(void *arg);

//===================>> PHILOSOPHERS_INITIALIZATION.C <<====================//
void				*new_philo_arg(t_param *param, int i,
						pthread_mutex_t **frk_lock);
int					strt_philo(pthread_t **philo, t_param *param,
						pthread_mutex_t **frk_lock);

//=======================>> REAPER_INITIALIZATION.C <<======================//
void				*reaper_args(t_param *param, int id);

//=========================>> REAPER_ROUTINE.C <<===========================//
int					is_alive(t_param *param);
void				kill(t_reaper_arg *args, int i, int silent);
void				*reaper_routine(void *arg);

//=============================>> UTILS.C <<================================//
char				*ft_strchr(const char *s, int c);
unsigned long long	time_us(unsigned long long strt);
void				swap_forks(unsigned int *left, unsigned int *right);
void				set_time_of_death(t_philo_arg *args);
void				swap_forks(unsigned int *left, unsigned int *right);

#endif
