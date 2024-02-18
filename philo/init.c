/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:10:15 by rseelaen          #+#    #+#             */
/*   Updated: 2024/02/18 00:21:08 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philos(t_philo **philos, int nbr_of_philos, t_main main)
{
	int	i;

	*philos = malloc(sizeof(t_philo) * nbr_of_philos);
	if (!*philos)
		return (1);
	i = -1;
	while (++i < nbr_of_philos)
	{
		(*philos)[i].super = main.super;
		(*philos)[i].id = i + 1;
		(*philos)[i].state = THINKING;
		(*philos)[i].last_meal = 0;
		(*philos)[i].time_to_die = main.time_to_die;
		(*philos)[i].time_to_eat = main.time_to_eat;
		(*philos)[i].time_to_sleep = main.time_to_sleep;
		(*philos)[i].nbr_of_meals = main.nbr_of_meals;
		(*philos)[i].fork_l = &main.forks[i];
		if (i == 0)
			(*philos)[i].fork_r = &main.forks[nbr_of_philos - 1];
		else
			(*philos)[i].fork_r = &main.forks[i - 1];
		(*philos)[i].state_m = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init((*philos)[i].state_m, NULL);
	}
	return (0);
}

int	init_forks(pthread_mutex_t **forks, int nbr_of_philos)
{
	int	i;

	*forks = malloc(sizeof(pthread_mutex_t) * nbr_of_philos);
	if (!*forks)
		return (1);
	i = -1;
	while (++i < nbr_of_philos)
		pthread_mutex_init(&(*forks)[i], NULL);
	return (0);
}

void	init_data(t_main *main, char **argv)
{
	(*main).super = malloc(sizeof(t_super));
	(*main).super->dead = malloc(sizeof(pthread_mutex_t));
	(*main).super->print = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init((*main).super->dead, NULL);
	pthread_mutex_init((*main).super->print, NULL);
	(*main).super->dead_flag = FALSE;
	(*main).nbr_of_philos = ft_atoi(argv[1]);
	(*main).time_to_die = ft_atoi(argv[2]);
	(*main).time_to_eat = ft_atoi(argv[3]);
	(*main).time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		(*main).nbr_of_meals = ft_atoi(argv[5]);
	else
		(*main).nbr_of_meals = -1;
	init_forks(&main->forks, main->nbr_of_philos);
	init_philos(&main->philos, main->nbr_of_philos, *main);
}
