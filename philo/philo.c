/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izsoares <izsoares@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:24:03 by izsoares          #+#    #+#             */
/*   Updated: 2023/03/22 13:08:30 by izsoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *routine()
{
	printf("Testing thread\n");
	return (NULL);
}

void init(int argc, char **argv, t_philo *philos, pthread_mutex_t *hashis)
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
			philos[i].id = i;
			//printf("%d\n", philos[i].id);
			pthread_create (&philos[i].philo, NULL, &routine, NULL);
			philos[i].left_hashi = &hashis[i];
			//printf("%d\n", philos[i].left_hashi);
			if (i <= n_philo - 2)
				philos[i].right_hashi = &hashis[i+1];
			else
				philos[i].right_hashi = &hashis[0];
			//printf("%d\n", philos[i].right_hashi);
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


int	main(int argc, char **argv)
{
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

	philos = NULL;
	hashis = NULL;
	verify_args(argc, argv);
	init(argc, argv, philos, hashis);

}
