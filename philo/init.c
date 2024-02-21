/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:10:15 by rseelaen          #+#    #+#             */
/*   Updated: 2024/02/21 18:55:13 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	assign_forks(t_philo *philo, t_main main, int i)
{
	if (philo->id == main.nbr_of_philos)
	{
		philo->first_fork = &main.forks[(i + 1) % main.nbr_of_philos];
		philo->second_fork = &main.forks[i];
	}
	else
	{
		philo->first_fork = &main.forks[i];
		philo->second_fork = &main.forks[(i + 1) % main.nbr_of_philos];
	}
}

int	init_philos(t_philo **philos, int nbr_of_philos, t_main main, int i)
{
	*philos = malloc(sizeof(t_philo) * nbr_of_philos);
	if (!*philos)
		return (1);
	while (++i < nbr_of_philos)
	{
		(*philos)[i].super = main.super;
		(*philos)[i].id = i + 1;
		(*philos)[i].last_meal = 0;
		(*philos)[i].nbr_of_philos = main.nbr_of_philos;
		(*philos)[i].time_to_die = main.time_to_die;
		(*philos)[i].time_to_eat = main.time_to_eat;
		(*philos)[i].time_to_sleep = main.time_to_sleep;
		(*philos)[i].nbr_of_meals = main.nbr_of_meals;
		(*philos)[i].meals_had = 0;
		(*philos)[i].finish_flag = FALSE;
		assign_forks(&(*philos)[i], main, i);
		pthread_mutex_init(&(*philos)[i].meal_m, NULL);
		pthread_mutex_init(&(*philos)[i].gen_m, NULL);
		pthread_mutex_init(&(*philos)[i].super_finish, NULL);
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
	pthread_mutex_init(&(*main).super->dead, NULL);
	pthread_mutex_init(&(*main).super->print, NULL);
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
	init_philos(&main->philos, main->nbr_of_philos, *main, -1);
}
