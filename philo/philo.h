/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izsoares <izsoares@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:08:16 by izsoares          #+#    #+#             */
/*   Updated: 2023/03/22 13:00:38 by izsoares         ###   ########.fr       */
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
	int number_philos;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	times_must_eat;
}				t_data;

typedef struct s_philo
{
	int				id;
	pthread_t		philo;
	pthread_mutex_t	*left_hashi;
	pthread_mutex_t	*right_hashi;
	t_data			*data;
	unsigned long	time_created;
}				t_philo;


// validation
int		ph_atoi(char *str);
int		verify_args(int argc, char **argv);
int		set_data(int argc, char **argv, t_data *data);
int		print_error(char *str);

#endif
