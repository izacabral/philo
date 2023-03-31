/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izsoares <izsoares@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 18:37:47 by izsoares          #+#    #+#             */
/*   Updated: 2023/03/31 14:38:22 by izsoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	malloc_init(t_data *data, pthread_mutex_t	**hashis, t_philo **philos)
{
	(*hashis) = malloc(sizeof(pthread_mutex_t) * data->number_philos);
	if (!hashis)
		return (-1);
	(*philos) = malloc(sizeof(t_philo) * data->number_philos);
	if (!(*philos))
		return (-1);
	return (0);
}

int	init_hashis(t_data *data, pthread_mutex_t *hashis)
{
	int i;
	i = 0;
	while (i < data->number_philos)
	{
		if (pthread_mutex_init(&hashis[i], NULL) != 0)
			return (-2);
		i++;
	}
	return (0);
}

int	init_philos(t_data *data, t_philo *philos, pthread_mutex_t *hashis)
{
	int i;
	pthread_mutex_t m_print;
	pthread_mutex_t m_died;

	i = 0;
	if (pthread_mutex_init(&m_print, NULL) != 0)
			return (-2);
	if (pthread_mutex_init(&m_died, NULL) != 0)
			return (-2);
	while (i <= (data->number_philos -1))
	{
		philos[i].id = i + 1;
		//printf("philo [%d]\n", philos[i].id);
		philos[i].left_hashi = &hashis[i];
		//printf("philo [%d] left_hashi:%p\n", philos[i].id, philos[i].left_hashi);
		if (i <= (data->number_philos - 2))
			philos[i].right_hashi = &hashis[i + 1];
		else
			philos[i].right_hashi = &hashis[0];
		//printf("philo [%d] right_hashi:%p\n", philos[i].id, philos[i].right_hashi);
		philos[i].data = data;
		//printf("philo [%d] data adress:%p\n", philos[i].id, philos[i].data);
		philos[i].time_last_meal = get_time_now();
		philos[i].m_print = &m_print;
		philos[i].m_died = &m_died;
		philos[i].times_eated = 0;
		if (pthread_mutex_init(&philos[i].m_times_eated, NULL) != 0)
			return (-2);
		//printf("philo [%d] time_created: %lums \n", philos[i].id, philos[i].time_created);
		i++;

	}
	i = 0;
	while (i < (data->number_philos))
	{
		if (pthread_create(&philos[i].philo, NULL, &routine, &philos[i]) != 0)
			return (-3);
		i++;
	}
	if (pthread_create(&data->monitor, NULL, &monitor, philos) != 0)
		return (-2);
	if (pthread_join(data->monitor, NULL) != 0)
		return (-2);

	return (0);
}

int philos_join(t_data *data, t_philo *philos)
{
	int i;

	i = 0;
	while (i < data->number_philos)
	{
		if(pthread_join(philos[i].philo, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}
