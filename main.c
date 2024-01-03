/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 14:15:56 by renato            #+#    #+#             */
/*   Updated: 2024/01/02 22:49:39 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	invalid_input_count(int argc)
{
	if (argc < 5)
	{
		printf("Error: not enough arguments\n");
		exit(1);
	}
	if (argc > 6)
	{
		printf("Error: too many arguments\n");
		exit(1);
	}
}

int	is_numerical(char *arg)
{
	while (*arg)
	{
		if (*arg >= 48 && *arg <= 57)
			return (1);
		arg++;
	}
	return (0);
}

void	check_input(int argc, char **argv)
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		if (!is_numerical(argv[i]))
		{
			printf("Error: all arguments must be numerical\n");
			exit (2);
		}
		if (argv[i][0] == '-' || (i != 5 && argv[i][0] == '0'))
		{
			printf("Error: arguments must be larger than 0\n");
			exit(2);
		}
	}
}

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		invalid_input_count(argc);
	check_input(argc, argv);
	printf("Correct number  of arguments\n");
	return (0);
}