/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izsoares <izsoares@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 18:37:47 by izsoares          #+#    #+#             */
/*   Updated: 2023/04/06 16:39:15 by izsoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	malloc_init(t_data *data, pthread_mutex_t **hashis, t_philo **philos)
{
	(*hashis) = malloc(sizeof(pthread_mutex_t) * data->number_philos);
	if (!hashis)
		return (-1);
	(*philos) = malloc(sizeof(t_philo) * data->number_philos);
	if (!(*philos))
		return (-1);
	return (0);
}

int	init_mutexes(t_data *data, pthread_mutex_t *hashis, t_philo *philos)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&data->m_print, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&data->m_died, NULL) != 0)
		return (-2);
	while (i < data->number_philos)
	{
		if (pthread_mutex_init(&hashis[i], NULL) != 0)
			return (-3);
		if (pthread_mutex_init(&philos[i].m_time_last_meal, NULL) != 0)
			return (-4);
		if (pthread_mutex_init(&philos[i].m_times_eated, NULL) != 0)
			return (-5);
		i++;
	}
	return (0);
}

int	init_philos(t_data *data, t_philo *philos, pthread_mutex_t *hashis)
{
	int	i;

	i = 0;
	while (i <= (data->number_philos -1))
	{
		philos[i].id = i + 1;
		philos[i].left_hashi = &hashis[i];
		if (i <= (data->number_philos - 2))
			philos[i].right_hashi = &hashis[i + 1];
		else
			philos[i].right_hashi = &hashis[0];
		philos[i].data = data;
		philos[i].time_last_meal = get_time_now();
		philos[i].times_eated = 0;
		i++;
	}
	return (0);
}

int	init_threads(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < (data->number_philos))
	{
		if (pthread_create(&philos[i].philo, NULL, &routine, &philos[i]) != 0)
			return (-2);
		i++;
	}
	return (0);
}

int	threads_join(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->number_philos)
	{
		if (pthread_join(philos[i].philo, NULL) != 0)
			return (-1);
		i++;
	}
	return (0);
}
