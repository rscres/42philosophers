/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 01:51:55 by renato            #+#    #+#             */
/*   Updated: 2024/02/22 14:09:39 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_positive(char **str)
{
	int		i;

	i = 1;
	while (str[i])
	{	
		if (ft_atoi(str[i]) <= 0)
		{
			printf("Error: arguments must be larger than 0\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	is_num(char **str)
{
	int		i;
	char	*tmp;

	i = 1;
	while (str[i])
	{	
		tmp = str[i];
		while (*tmp)
		{
			if ((*tmp < '0' || *tmp > '9') && *tmp != '-')
			{
				printf("Error: argument is not a number\n");
				return (0);
			}
			tmp++;
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
	if (!is_positive(argv))
		return (1);
	return (0);
}
