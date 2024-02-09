/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:28:28 by rseelaen          #+#    #+#             */
/*   Updated: 2024/02/09 19:25:03 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_num(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{	
		while (*str[i])
		{
			if (*str[i] < '0' || *str[i] > '9')
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

int	main(int argc, char **argv)
{
	if (num_of_args(argc))
		return (1);
	if (!is_num(argv))
		return (1);
	return (0);
}
