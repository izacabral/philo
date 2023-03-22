/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izsoares <izsoares@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:15:27 by izsoares          #+#    #+#             */
/*   Updated: 2023/03/22 11:11:45 by izsoares         ###   ########.fr       */
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

void	verify_args(int argc, char **argv)
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
			{
				print_error();
				exit(EXIT_FAILURE);
			}
		}
	}
	else
	{
		print_error();
		exit(EXIT_FAILURE);
	}
}

void	print_error(void)
{
	printf("\e[31m---Invalid parameters! Try something like:\n\e[0m");
	printf("\e[32m./philo <number_of_philosophers> <time_to_die> <time_to_eat>\
 <time_to_sleep> [number_of_times_each_philosopher_must_eat]\n\e[0m");
}
