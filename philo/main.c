/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:28:28 by rseelaen          #+#    #+#             */
/*   Updated: 2024/02/22 14:21:06 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_data(t_main *main)
{
	int	i;

	i = -1;
	while (++i < main->nbr_of_philos)
	{
		pthread_mutex_destroy(&main->forks[i]);
		pthread_mutex_destroy(&main->philos[i].meal_m);
		pthread_mutex_destroy(&main->philos[i].gen_m);
	}
	pthread_mutex_destroy(&main->super->print_m);
	pthread_mutex_destroy(&main->super->dead_m);
	free(main->philos);
	free(main->super);
	free(main->forks);
}

int	main(int argc, char **argv)
{
	int		i;
	t_main	main;

	if (check_input(argc, argv))
		return (1);
	init_data(&main, argv);
	i = -1;
	get_interval();
	while (++i < main.nbr_of_philos)
		pthread_create(&main.philos[i].thread, NULL, &routine,
			(void *)&main.philos[i]);
	i = -1;
	while (++i < main.nbr_of_philos)
		pthread_join(main.philos[i].thread, NULL);
	free_data(&main);
	return (0);
}
