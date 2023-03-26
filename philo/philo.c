/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izsoares <izsoares@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:24:03 by izsoares          #+#    #+#             */
/*   Updated: 2023/03/23 16:00:09 by izsoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *routine()
{
	printf("Testing thread\n");
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


int init_hashis(t_data *data, pthread_mutex_t *hashis)
{
	int i;

	hashis = malloc(sizeof(pthread_mutex_t) * data->number_philos);
	if (!hashis)
		return (-1);
	i = 0;
	while (i < data->number_philos)
	{
		if (pthread_mutex_init(&hashis[i], NULL) != 0)
			return (-2);
		i++;
	}
	return (0);
}

int init_philos(t_data *data, t_philo *philos, pthread_mutex_t *hashis)
{
	int i;

	philos = malloc(sizeof(t_philo) * data->number_philos);
	if (!philos)
		return (-3);
	philos->data = data;
	i = 0;
	while (i <= (data->number_philos -1))
	{
		philos[i].id = i + 1;
		printf("philo [%d]\n", philos[i].id);
		if (pthread_create(&philos[i].philo, NULL, &routine, NULL) != 0)
			return (-4);
		philos[i].left_hashi = &hashis[i];
		printf("philo [%d].left_hashi:%p\n", philos[i].id, philos[i].left_hashi);
		if (i <= (data->number_philos - 2))
			philos[i].right_hashi = &hashis[i+1];
		else
			philos[i].right_hashi = &hashis[0];
		printf("philo [%d].right_hashi:%p\n", philos[i].id, philos[i].right_hashi);
		i++;
	}
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


long time_diff(struct timeval *start, struct timeval *end)
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
	struct	timeval start;
	struct	timeval end;

	philos = NULL;
	hashis = NULL;
	if (set_data(argc, argv, &data) != 0)
		return (print_error("input"));

	printf("number_philos: %d\n", data.number_philos);
	printf("time_to_die: %ld\n", data.time_die);
	printf("time_to_eat: %ld\n", data.time_eat);
	printf("time_to_sleep: %ld\n", data.time_sleep);
	printf("times_to_eat: %ld\n", data.times_eat);


	if (init_hashis(&data, hashis) != 0)
		return (print_error("init"));
	if (init_philos(&data, philos, hashis) != 0)
		return (print_error("init"));


	if (philos_join(&data, philos) != 0)
		return (print_error("joint"));




	gettimeofday(&start, NULL);
	//init(argc, argv, philos, hashis);
	usleep(3000);
	gettimeofday(&end, NULL);
	printf("%ld\n", time_diff(&start, &end));

}
