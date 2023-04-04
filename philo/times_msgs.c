/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   times_msgs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izsoares <izsoares@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 18:31:25 by izsoares          #+#    #+#             */
/*   Updated: 2023/04/04 15:15:12 by izsoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_time_now(void)
{
	struct timeval n_time;

	gettimeofday(&n_time, NULL);
	return ((n_time.tv_sec * 1000) + n_time.tv_usec / 1000);
}


void	print_msg(t_philo *philo, char *str)
{
	long long milesec;
	milesec = get_time_now() - philo->data->time_created;
	pthread_mutex_lock(philo->m_print);
	if (philo->data->died)
		printf("%lld %d %s\n", milesec, philo->id, str);
	pthread_mutex_unlock(philo->m_print);
}

void	print_msg_died(t_philo *philo, char *str)
{
	long long milesec;
	milesec = get_time_now() - philo->data->time_created;
	pthread_mutex_lock(philo->m_print);
	printf("%lld %d %s\n", milesec, philo->id, str);
	pthread_mutex_unlock(philo->m_print);
}

void	smart_sleep(unsigned long time)
{
	unsigned long s_time;

	s_time = get_time_now();
	while (s_time + time > get_time_now())
		usleep(100);
}
