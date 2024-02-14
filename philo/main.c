/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:28:28 by rseelaen          #+#    #+#             */
/*   Updated: 2024/02/14 18:51:31 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philos(t_philo **philos, int nbr_of_philos, t_main main)
{
	int	i;

	*philos = malloc(nbr_of_philos * sizeof(t_philo));
	i = -1;
	while (++i < nbr_of_philos)
	{
		*philos = malloc(sizeof(t_philo));
		(*philos)->super = main.super;
		(*philos)->id = i + 1;
		(*philos)->state = THINKING;
		(*philos)->last_meal = 0;
		(*philos)->time_to_die = main.time_to_die;
		(*philos)->time_to_eat = main.time_to_eat;
		(*philos)->time_to_sleep = main.time_to_sleep;
		(*philos)->nbr_of_meals = main.nbr_of_meals;
		(*philos)->fork_l = &main.forks[i];
		if (i == 0)
			(*philos)->fork_r = &main.forks[nbr_of_philos - 1];
		else
			(*philos)->fork_r = &main.forks[i - 1];
	}
}

void	init_forks(pthread_mutex_t **forks, int nbr_of_philos)
{
	int	i;

	*forks = malloc(sizeof(pthread_mutex_t) * nbr_of_philos);
	i = -1;
	while (++i < nbr_of_philos)
		pthread_mutex_init(forks[i], NULL);
}

void	init_data(t_main *main, char **argv)
{
	(*main).super = malloc(sizeof(t_super));
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

void	routine(void *philo)
{
	t_philo	p;

	p = *(t_philo *)philo;
	if (p.id % 2 == 0)
		usleep(1000);
	while ()
}

int	main(int argc, char **argv)
{
	t_main	main;
	int		i;

	if (check_input(argc, argv))
		return (1);
	init_data(&main, argv);
	i = -1;
	while (++i < main.nbr_of_philos)
		pthread_create(&main.philos[i].thread, NULL, &routine, &main);
	i = -1;
	while (++i < main.nbr_of_philos)
		pthread_join(main.philos[i].thread, NULL);
	return (0);
}
