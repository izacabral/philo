/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izsoares <izsoares@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:15:27 by izsoares          #+#    #+#             */
/*   Updated: 2023/03/21 16:03:25 by izsoares         ###   ########.fr       */
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
