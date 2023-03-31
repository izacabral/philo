/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izsoares <izsoares@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:24:03 by izsoares          #+#    #+#             */
/*   Updated: 2023/03/31 19:43:32 by izsoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *arg)
{
	t_philo *philo;

	philo = arg;
	int i;


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




int	main(int argc, char **argv)
{
	//verificação da minha atoi
	/* char *str;
	char *str1;
	char *str2;
	char *str3;
	char *str4;

	str = "-5";
	str1 = "-3458";
	str2 = "2147483647";
	str3 = "34.58";
	str4 = "21474836489";

	printf("%d\n", ph_atoi(str));
	printf("%d\n", ph_atoi(str1));
	printf("%d\n", ph_atoi(str2));
	printf("%d\n", ph_atoi(str3));
	printf("%d\n", ph_atoi(str4)); */

	t_philo			*philos;
	pthread_mutex_t	*hashis;
	t_data			data;


	philos = NULL;
	hashis = NULL;


	if (set_data(argc, argv, &data) != 0)
		return (print_error("input"));
	if (malloc_init(&data, &hashis, &philos) != 0)
		return (print_error("malloc"));

	//
/* 	printf("data adress: %p\n\n", &data);

	printf("number_philos: %d\n", data.number_philos);
	printf("time_to_die: %d\n", data.time_die);
	printf("time_to_eat: %d\n", data.time_eat);
	printf("time_to_sleep: %d\n", data.time_sleep);
	printf("times_to_eat: %d\n", data.times_must_eat); */
	//

	if (init_hashis(&data, hashis) != 0)
		return (print_error("init"));
	if (init_philos(&data, philos, hashis) != 0)
		return (print_error("init"));




	if (philos_join(&data, philos) != 0)
		return (print_error("joint"));

}

