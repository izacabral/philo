/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izsoares <izsoares@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 10:43:20 by izsoares          #+#    #+#             */
/*   Updated: 2023/04/03 11:32:40 by izsoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_end(t_data *data, pthread_mutex_t	**hashis, t_philo **philos)
{
	if (destroy_philos(data, *philos) != 0)
		return (-1);
	if (destroy_hashis(data, *hashis) != 0)
		return (-1);
	free((*hashis));
	free((*philos));
	return (0);
}

int	destroy_hashis(t_data *data, pthread_mutex_t *hashis)
{
	int	i;

	i = 0;
	while (i < data->number_philos)
	{
		if (pthread_mutex_destroy(&hashis[i]) != 0)
			return (-1);
		i++;
	}
	return (0);
}

int	destroy_philos(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	if (pthread_mutex_destroy(&data->m_print) != 0)
		return (-1);
	if (pthread_mutex_destroy(&data->m_died) != 0)
		return (-1);
	while (i < (data->number_philos))
	{
		/* if (pthread_mutex_destroy(&philos[i].m_time_last_meal) != 0)
			return (-1); */
		if (pthread_mutex_destroy(&philos[i].m_times_eated) != 0)
			return (-1);
		i++;
	}
	return (0);
}
