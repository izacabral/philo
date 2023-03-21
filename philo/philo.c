/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izsoares <izsoares@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:24:03 by izsoares          #+#    #+#             */
/*   Updated: 2023/03/21 15:50:25 by izsoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(void)
{
	char *str;
	char *str1;
	char *str2;
	char *str3;
	char *str4;

	str = "0";
	str1 = "-3458";
	str2 = "2147483647";
	str3 = "34.58";
	str4 = "21474836489";

	printf("%d\n", ph_atoi(str));
	printf("%d\n", ph_atoi(str1));
	printf("%d\n", ph_atoi(str2));
	printf("%d\n", ph_atoi(str3));
	printf("%d\n", ph_atoi(str4));
}
