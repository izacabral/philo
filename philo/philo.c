/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izsoares <izsoares@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:24:03 by izsoares          #+#    #+#             */
/*   Updated: 2023/04/03 11:45:48 by izsoares         ###   ########.fr       */
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
	if (init_hashis(&data, hashis) != 0)
		return (print_error("init"));
	if (init_philos(&data, philos, hashis) != 0)
		return (print_error("init"));
	if (philos_join(&data, philos) != 0)
		return (print_error("join"));
	if (free_end(&data, &hashis, &philos) != 0)
		return (print_error("end"));
	return (0);
}

