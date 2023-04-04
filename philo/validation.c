/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izsoares <izsoares@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:15:27 by izsoares          #+#    #+#             */
/*   Updated: 2023/04/04 12:01:02 by izsoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_atoi(char *str)
{
	int	nb;
	int	i;

	nb = 0;
	i = 0;
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			return (-1);
		i++;
	}
	while (str[i])
	{
		if ((str[i] >= '0' && str[i] <= '9') && nb >= 0 && nb < INT_MAX)
		{
			nb = nb * 10 + (str[i] - '0');
		}
		else
			return (-1);
		i++;
	}
	return (nb);
}

int	verify_args(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc >= 5 && argc <= 6)
	{
		while (argv[i])
		{
			if (ph_atoi(argv[i]) >= 1)
				i++;
			else
				return (1);
		}
	}
	else
		return (1);
	return (0);
}

int	set_data(int argc, char **argv, t_data *data)
{
	if (verify_args(argc, argv) == 0)
	{
		data->number_philos = ph_atoi(argv[1]);
		data->time_die = ph_atoi(argv[2]);
		data->time_eat = ph_atoi(argv[3]);
		data->time_sleep = ph_atoi(argv[4]);
		if (argc == 6)
			data->times_must_eat = ph_atoi(argv[5]);
		else
			data->times_must_eat = 0;
		data->died = 1;
		data->time_created = get_time_now();
		return (0);
	}
	else
		return (1);
}

int	print_error(char *str)
{
	if (strncmp(str, "input", 6) == 0)
	{
		printf("\e[31m---Invalid parameters! Try something like:\n\e[0m");
		printf("\e[32m./philo <number_of_philosophers> <time_to_die> <time_to_eat>\
	<time_to_sleep> [number_of_times_each_philosopher_must_eat]\n\e[0m");
	}
	else if (strncmp(str, "malloc", 7) == 0)
		printf("\e[31mMalloc Error!\n\e[0m");
	else if (strncmp(str, "mutexes", 8) == 0)
		printf("\e[31mSomething wrong on Mutexes initialization!\n\e[0m");
	else if (strncmp(str, "philos", 7) == 0)
		printf("\e[31mSomething wrong on Philos initialization\n\e[0m");
	else if (strncmp(str, "threads", 8) == 0)
		printf("\e[31mSomething wrong on Threads creation\n\e[0m");
	else if (strncmp(str, "join", 5) == 0)
		printf("\e[31mSomething wrong on joining\n\e[0m");
	else if (strncmp(str, "end", 4) == 0)
		printf("\e[31mSomething wrong in the end\n\e[0m");
	return (0);
}
