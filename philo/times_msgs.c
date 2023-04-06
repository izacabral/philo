/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   times_msgs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izsoares <izsoares@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 18:31:25 by izsoares          #+#    #+#             */
/*   Updated: 2023/04/06 15:22:58 by izsoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_time_now(void)
{
	struct timeval	n_time;

	gettimeofday(&n_time, NULL);
	return ((n_time.tv_sec * 1000) + n_time.tv_usec / 1000);
}

void	print_msg(t_philo *philo, char *str)
{
	long long	milesec;

	pthread_mutex_lock(&philo->data->m_print);
	milesec = get_time_now() - philo->data->time_created;
	pthread_mutex_unlock(&philo->data->m_print);
	pthread_mutex_lock(&philo->data->m_died);
	if (philo->data->died)
	{
		pthread_mutex_unlock(&philo->data->m_died);
		pthread_mutex_lock(&philo->data->m_print);
		printf("%lld %d %s\n", milesec, philo->id, str);
		pthread_mutex_unlock(&philo->data->m_print);
	}
	else
		pthread_mutex_unlock(&philo->data->m_died);
}

void	print_msg_died(t_philo *philo, char *str)
{
	long long	milesec;

	pthread_mutex_lock(&philo->data->m_print);
	milesec = get_time_now() - philo->data->time_created;
	pthread_mutex_unlock(&philo->data->m_print);
	pthread_mutex_lock(&philo->data->m_print);
	printf("%lld %d %s\n", milesec, philo->id, str);
	pthread_mutex_unlock(&philo->data->m_print);
}

void	smart_sleep(unsigned long time)
{
	unsigned long	s_time;

	s_time = get_time_now();
	while (s_time + time > get_time_now())
		usleep(100);
}
