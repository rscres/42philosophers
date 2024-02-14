/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 01:51:55 by renato            #+#    #+#             */
/*   Updated: 2024/02/14 01:53:00 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_num(char **str)
{
	int	i;

	i = 1;
	while (str[i])
	{	
		if (str[i][0] == '-' || (i != 5 && str[i][0] == '0'))
		{
			printf("Error: arguments must be larger than 0\n");
			return (2);
		}
		while (*str[i])
		{
			if (*str[i] < '0' || *str[i] > '9' )
			{
				printf("Error: argument is not a number\n");
				return (0);
			}
			str[i]++;
		}
		i++;
	}
	return (1);
}

int	num_of_args(int argc)
{
	if (argc < 5)
	{
		printf("Error: not enough arguments\n");
		return (1);
	}
	if (argc > 6)
	{
		printf("Error: too many arguments\n");
		return (1);
	}
	return (0);
}

int	check_input(int argc, char **argv)
{
	if (num_of_args(argc))
		return (1);
	if (!is_num(argv))
		return (1);
	return (0);
}