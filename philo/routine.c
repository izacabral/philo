/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izsoares <izsoares@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:24:03 by izsoares          #+#    #+#             */
/*   Updated: 2023/03/31 19:55:53 by izsoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_hashis(t_philo *philo)
{
	//if (philo->data->number_philos > 1)
	pthread_mutex_lock(philo->left_hashi);
	print_msg(philo, "has taken a fork");
	if (philo->data->number_philos > 1)
	{
		pthread_mutex_lock(philo->right_hashi);
		print_msg(philo, "has taken a fork");
		print_msg(philo, "is eating");
		philo->time_last_meal = get_time_now();
		pthread_mutex_lock(&philo->m_times_eated);
		philo->times_eated++;
		//printf("times_eated: %d\n", philo->times_eated);
		pthread_mutex_unlock(&philo->m_times_eated);
	}
	if (philo->data->number_philos > 1)
		smart_sleep(philo->data->time_eat);
	else
		smart_sleep(philo->data->time_die + 10);
	if (philo->data->number_philos > 1)
		pthread_mutex_unlock(philo->right_hashi);
	//if (philo->data->number_philos > 1)
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
		//printf("i: %d\n", times);
		//pthread_mutex_unlock(&philo->m_times_eated);
		i++;

	}
	if (times == philo->data->number_philos)
		return (0);
	else
		return (1);

}

void	*routine(void *arg)
{
	t_philo *philo;

	philo = arg;
	if (philo->id % 2 == 0)
		usleep(100);

	while (check_is_died(philo))
	{
		//if (check_is_died(philo))
			take_hashis(philo);
		//if (check_is_died(philo))
			is_sleeping(philo);
		//if (check_is_died(philo))
			is_thinking(philo);
	}


	return (NULL);
}

