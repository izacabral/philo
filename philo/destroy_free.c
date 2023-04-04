/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izsoares <izsoares@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 10:43:20 by izsoares          #+#    #+#             */
/*   Updated: 2023/04/04 17:46:23 by izsoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_end(t_data *data, pthread_mutex_t	**hashis, t_philo **philos)
{
	if (destroy_mutexes(data, *hashis, *philos) != 0)
		return (-1);
	free((*hashis));
	free((*philos));
	return (0);
}

int	destroy_mutexes(t_data *data, pthread_mutex_t *hashis, t_philo *philos)
{
	int	i;

	i = 0;
	if (pthread_mutex_destroy(&data->m_print) != 0)
		return (-1);
	if (pthread_mutex_destroy(&data->m_died) != 0)
		return (-2);
	while (i < data->number_philos)
	{
		if (pthread_mutex_destroy(&hashis[i]) != 0)
			return (-3);
		if (pthread_mutex_destroy(&philos[i].m_time_last_meal) != 0)
			return (-4);
		if (pthread_mutex_destroy(&philos[i].m_times_eated) != 0)
			return (-5);
		i++;
	}
	return (0);
}
