/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:28:28 by rseelaen          #+#    #+#             */
/*   Updated: 2024/02/18 00:49:36 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think(t_philo *philo)
{
	pthread_mutex_lock(philo->state_m);
	philo->state = THINKING;
	print_status(philo->id, "is thinking", get_interval(), philo->super);
	pthread_mutex_unlock(philo->state_m);
	usleep(100);
}

int	rest(t_philo *philo)
{
	pthread_mutex_lock(philo->state_m);
	philo->state = SLEEPING;
	print_status(philo->id, "is sleeping", get_interval(), philo->super);
	pthread_mutex_unlock(philo->state_m);
	usleep(philo->time_to_sleep * 1000);
	return (0);
}

void	*routine(void *p)
{
	t_philo	*philo;
	int		meals;

	philo = (t_philo *)p;
	pthread_mutex_lock(philo->state_m);
	philo->last_meal = 0;
	pthread_mutex_unlock(philo->state_m);
	meals = 0;
	while (!check_state(philo) && !is_dead(philo))
	{
		if (eat(philo))
			break ;
		meals++;
		if (philo->nbr_of_meals != -1 && meals >= philo->nbr_of_meals)
		{
			pthread_mutex_lock(philo->state_m);
			philo->state = FULL;
			pthread_mutex_unlock(philo->state_m);
			break ;
		}
		think(philo);
		rest(philo);
	}
	return (NULL);
}

void	free_data(t_main *main)
{
	int	i;

	i = -1;
	while (++i < main->nbr_of_philos)
	{
		pthread_mutex_destroy(main->philos[i].state_m);
		pthread_mutex_destroy(main->philos[i].fork_l);
		pthread_mutex_destroy(main->philos[i].fork_r);
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
	while (++i < main.nbr_of_philos)
		pthread_create(&main.philos[i].thread, NULL, &routine,
			(void *)&main.philos[i]);
	pthread_create(&main.supervisor, NULL, &supervisor, &main);
	i = -1;
	while (++i < main.nbr_of_philos)
		pthread_join(main.philos[i].thread, NULL);
	pthread_join(main.supervisor, NULL);
	free_data(&main);
	return (0);
}
