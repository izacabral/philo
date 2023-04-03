/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izsoares <izsoares@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:24:03 by izsoares          #+#    #+#             */
/*   Updated: 2023/04/03 11:46:49 by izsoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo *philo;

	philo = arg;
	if (philo->id % 2 == 0)
		usleep(10000);
	while (check_is_died(philo))
	{
		//printf("id philo: %d\n", philo->id);
		take_hashis(philo);
		is_sleeping(philo);
		is_thinking(philo);
	}
	return (NULL);
}

void	take_hashis(t_philo *philo)
{
	pthread_mutex_lock(philo->left_hashi);
	print_msg(philo, "has taken a fork");
	if (philo->data->number_philos > 1)
	{
		pthread_mutex_lock(philo->right_hashi);
		print_msg(philo, "has taken a fork");
		print_msg(philo, "is eating");
		//pthread_mutex_lock(&philo->m_time_last_meal);
		philo->time_last_meal = get_time_now();
		//pthread_mutex_unlock(&philo->m_time_last_meal);
		pthread_mutex_lock(&philo->m_times_eated);
		philo->times_eated++;
		pthread_mutex_unlock(&philo->m_times_eated);
	}
	if (philo->data->number_philos > 1)
		smart_sleep(philo->data->time_eat);
	else
		smart_sleep(philo->data->time_die + 10);
	if (philo->data->number_philos > 1)
		pthread_mutex_unlock(philo->right_hashi);
	pthread_mutex_unlock(philo->left_hashi);
}

void	is_sleeping(t_philo *philo)
{
	if (philo->data->number_philos > 1)
	{
		print_msg(philo, "is sleeping");
		smart_sleep(philo->data->time_sleep);
	}
}

void	is_thinking(t_philo *philo)
{
	if (philo->data->number_philos > 1)
		print_msg(philo, "is thinking");
}




