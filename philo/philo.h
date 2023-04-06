/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izsoares <izsoares@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:08:16 by izsoares          #+#    #+#             */
/*   Updated: 2023/04/06 14:41:57 by izsoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define INT_MAX 2147483647

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_data
{
	int				number_philos;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				times_must_eat;
	int				died;
	unsigned long	time_created;
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_died;
	//pthread_t		monitor;
}				t_data;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*left_hashi;
	pthread_mutex_t	*right_hashi;
	t_data			*data;
	unsigned long	time_last_meal;
	pthread_mutex_t	m_time_last_meal;
	int				times_eated;
	pthread_mutex_t	m_times_eated;
	pthread_t		philo;
}				t_philo;

// validation
int				ph_atoi(char *str);
int				verify_args(int argc, char **argv);
int				set_data(int argc, char **argv, t_data *data);
int				print_error(char *str);

// init
int				malloc_init(t_data *data, pthread_mutex_t **hashis,
					t_philo **philos);
int				init_mutexes(t_data *data, pthread_mutex_t *hashis,
					t_philo *philos);
int				init_philos(t_data *data, t_philo *philos,
					pthread_mutex_t *hashis);
int				init_threads(t_data *data, t_philo *philos);
int				threads_join(t_data *data, t_philo *philos);

// routine
void			*routine(void *arg);
void			take_hashis(t_philo *philo);
void			is_sleeping(t_philo *philo);
void			is_thinking(t_philo *philo);

// monitor
void			*monitor(void *arg);
int				check_is_died(t_philo *philo);
int				check_is_satisfied(t_philo *philo);
int				check_must_eat(t_philo *philo);
void			set_monitor(t_philo *philo, int i);

// times and msgs
unsigned long	get_time_now(void);
void			print_msg(t_philo *philo, char *str);
void			print_msg_died(t_philo *philo, char *str);
void			smart_sleep(unsigned long time);

// destroy_free
int				free_end(t_data *data, pthread_mutex_t	**hashis,
					t_philo **philos);
int				destroy_mutexes(t_data *data, pthread_mutex_t *hashis,
					t_philo *philos);
#endif
