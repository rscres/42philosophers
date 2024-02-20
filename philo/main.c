/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:28:28 by rseelaen          #+#    #+#             */
/*   Updated: 2024/02/19 23:00:07 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_data(t_main *main)
{
	int	i;

	i = -1;
	while (++i < main->nbr_of_philos)
	{
		pthread_mutex_destroy(main->philos[i].state_m);
		pthread_mutex_destroy(&main->forks[i]);
		free(main->philos[i].state_m);
	}
	pthread_mutex_destroy(main->super->print);
	pthread_mutex_destroy(main->super->dead);
	free(main->super->print);
	free(main->super->dead);
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
	pthread_mutex_lock(main.super->dead);
	while (++i < main.nbr_of_philos)
		pthread_create(&main.philos[i].thread, NULL, &routine,
			(void *)&main.philos[i]);
	// pthread_create(&main.supervisor, NULL, &supervisor, &main);
	i = -1;
	while (++i < main.nbr_of_philos)
		pthread_join(main.philos[i].thread, NULL);
	pthread_join(main.supervisor, NULL);
	free_data(&main);
	return (0);
}
