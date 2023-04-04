/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izsoares <izsoares@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:24:03 by izsoares          #+#    #+#             */
/*   Updated: 2023/04/04 12:04:47 by izsoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo			*philos;
	pthread_mutex_t	*hashis;
	t_data			data;

	philos = NULL;
	hashis = NULL;
	if (set_data(argc, argv, &data) != 0)
		return (print_error("input"));
	if (malloc_init(&data, &hashis, &philos) != 0)
		return (print_error("malloc"));
	if (init_mutexes(&data, hashis, philos) != 0)
		return (print_error("mutexes"));
	if (init_philos(&data, philos, hashis) != 0)
		return (print_error("philos"));
	if (init_threads(&data, philos) != 0)
		return (print_error("threads"));
	if (threads_join(&data, philos) != 0)
		return (print_error("join"));
	if (free_end(&data, &hashis, &philos) != 0)
		return (print_error("end"));
	return (0);
}

