/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izsoares <izsoares@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:45:05 by izsoares          #+#    #+#             */
/*   Updated: 2023/04/03 11:46:58 by izsoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *arg)
{
	t_philo *philo;
	int i;

	philo = arg;
	while (check_is_died(philo))
	{
		i = 0;
		if (check_is_satisfied(philo) == 0)
		{
			pthread_mutex_lock(philo->m_died);
			philo[i].data->died = 0;
			pthread_mutex_unlock(philo->m_died);
			return (NULL);
		}
		while (i < philo->data->number_philos && check_is_died(&philo[i]))
		{
			if ((get_time_now() - philo[i].time_last_meal) >= (unsigned long)philo[i].data->time_die)
			{
				pthread_mutex_lock(philo->m_died);
				philo[i].data->died = 0;
				pthread_mutex_unlock(philo->m_died);
				print_msg_died(&philo[i], "died");
			}
			i++;
			usleep(200);
		}
		usleep(200);
	}
	return (NULL);
}

int	check_is_died(t_philo *philo)
{
	pthread_mutex_lock(philo->m_died);
	if (philo->data->died)
	{
		pthread_mutex_unlock(philo->m_died);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(philo->m_died);
		return (0);
	}
}

int	check_is_satisfied(t_philo *philo)
{
	int i;
	int times;

	times = 0;
	i = 0;
	while (i < philo->data->number_philos)
	{
		//pthread_mutex_lock(&philo[i].m_times_eated);
		if (philo[i].times_eated >= philo->data->times_must_eat)
			times++;
		//pthread_mutex_unlock(&philo->m_times_eated);
		i++;

	}
	if (times == philo->data->number_philos)
		return (0);
	else
		return (-1);
}
