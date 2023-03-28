/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izsoares <izsoares@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:24:03 by izsoares          #+#    #+#             */
/*   Updated: 2023/03/28 13:37:50 by izsoares         ###   ########.fr       */
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
	milesec = get_time_now() - philo->time_created;
	pthread_mutex_lock(philo->m_print);
	if (philo->data->died)
		printf("%lld %d %s\n", milesec, philo->id, str);
	pthread_mutex_unlock(philo->m_print);

}

void	take_hashis(t_philo *philo)
{
	pthread_mutex_lock(philo->left_hashi);
	print_msg(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_hashi);
	print_msg(philo, "has taken a fork");
	print_msg(philo, "is eating");
	philo->time_last_meal = get_time_now();
	usleep(philo->data->time_eat * 1000);
	pthread_mutex_unlock(philo->right_hashi);
	pthread_mutex_unlock(philo->left_hashi);
}

void	is_sleeping(t_philo *philo)
{
	print_msg(philo, "is sleeping");
	usleep(philo->data->time_sleep * 1000);
}

void	is_thinking(t_philo *philo)
{
	print_msg(philo, "is thinking");
}


int	check_is_died(t_philo **philo)
{
	printf("died:\n");
	printf("died: %d\n", (*philo)->data->died);
	//pthread_mutex_lock(philo->m_died);
	if (philo->data->died)
	{
		//pthread_mutex_unlock(philo->m_died);
		return (1);
	}
	else
	{
		//pthread_mutex_unlock(philo->m_died);
		return (0);
	}
}

void	*routine(void *arg)
{
	t_philo *philo;

	philo = arg;
	if (philo->id % 2 == 0)
		usleep(100);
	while (check_is_died(philo))
	{
		if (check_is_died(philo))
			take_hashis(philo);
		if (check_is_died(philo))
			is_sleeping(philo);
		if (check_is_died(philo))
			is_thinking(philo);
	}
	return (NULL);
}

void	*monitor(void *arg)
{
	t_philo *philo;

	philo = arg;
	int i;


	while (check_is_died(philo))
	{
		i = 0;
		while (check_is_died(&philo[i]))
		{
			if ((get_time_now() - philo[i].time_last_meal) > (unsigned long)philo[i].data->time_die)
			{
				philo[i].data->died = 0;
				print_msg(&philo[i], "died");

			}
			i++;
			usleep(200);

		}
		usleep(200);
	}
	return (NULL);
}


/* void init(int argc, char **argv, t_philo *philos, pthread_mutex_t *hashis)
{
	int	n_philo;
	int	i;

	n_philo = ph_atoi(argv[1]);
	i = 0;
	if (argc == 5 || argc == 6)
	{
		philos = malloc(sizeof(t_philo) * n_philo);
		hashis = malloc(sizeof(pthread_mutex_t) * n_philo);

		while (i <= n_philo - 1)
		{
			pthread_mutex_init(&hashis[i], NULL);
			i++;
		}
		i = 0;
		while (i <= n_philo - 1)
		{
			philos[i].id = i + 1;
			//printf("%d\n", philos[i].id);
			pthread_create (&philos[i].philo, NULL, &routine, NULL);
			philos[i].left_hashi = &hashis[i];
			//printf("philo [%d].left_hashi:%p\n", philos[i].id, philos[i].left_hashi);
			if (i <= n_philo - 2)
				philos[i].right_hashi = &hashis[i+1];
			else
				philos[i].right_hashi = &hashis[0];
			//printf("philo [%d].right_hashi:%p\n", philos[i].id, philos[i].right_hashi);
			i++;
		}
		i = 0;
		while (i <= n_philo - 1)
		{
			pthread_join(philos[i].philo, NULL);
			i++;
		}
	}
}
 */

int	malloc_hashis_philos(t_data *data, pthread_mutex_t	**hashis, t_philo **philos)
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

	i = 0;
	pthread_mutex_t m_print;
	pthread_mutex_t m_died;


	if (pthread_mutex_init(&m_print, NULL) != 0)
			return (-2);
	if (pthread_mutex_init(&m_died, NULL) != 0)
			return (-2);
	while (i <= (data->number_philos -1))
	{
		philos[i].id = i + 1;
		printf("philo [%d]\n", philos[i].id);
		if (pthread_create(&philos[i].philo, NULL, &routine, &philos[i]) != 0)
			return (-3);
		philos[i].left_hashi = &hashis[i];
		printf("philo [%d] left_hashi:%p\n", philos[i].id, philos[i].left_hashi);
		if (i <= (data->number_philos - 2))
			philos[i].right_hashi = &hashis[i + 1];
		else
			philos[i].right_hashi = &hashis[0];
		printf("philo [%d] right_hashi:%p\n", philos[i].id, philos[i].right_hashi);
		philos[i].data = data;
		printf("philo [%d] data adress:%p\n", philos[i].id, philos[i].data);
		philos[i].time_created = get_time_now();
		philos[i].time_last_meal = get_time_now();
		philos[i].m_print = &m_print;
		philos[i].m_died = &m_died;
		printf("philo [%d] time_created: %lums \n", philos[i].id, philos[i].time_created);
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


long long time_diff(struct timeval *start, struct timeval *end)
{
	return ((end->tv_sec - start->tv_sec)) * 1000 + ((end->tv_usec - start->tv_usec) /1000);
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
	if (malloc_hashis_philos(&data, &hashis, &philos) != 0)
		return (print_error("malloc"));

	//
	printf("data adress: %p\n\n", &data);

	printf("number_philos: %d\n", data.number_philos);
	printf("time_to_die: %d\n", data.time_die);
	printf("time_to_eat: %d\n", data.time_eat);
	printf("time_to_sleep: %d\n", data.time_sleep);
	printf("times_to_eat: %d\n", data.times_must_eat);
	//

	if (init_hashis(&data, hashis) != 0)
		return (print_error("init"));
	if (init_philos(&data, philos, hashis) != 0)
		return (print_error("init"));




	if (philos_join(&data, philos) != 0)
		return (print_error("joint"));

}

