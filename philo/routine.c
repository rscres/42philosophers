/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 01:06:56 by renato            #+#    #+#             */
/*   Updated: 2024/02/20 01:46:35 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think(t_philo *philo)
{
	print_status(philo->id, "is thinking", get_interval(), philo->super);
	usleep(100 * philo->id);
}

int	rest(t_philo *philo)
{
	print_status(philo->id, "is sleeping", get_interval(), philo->super);
	usleep(philo->time_to_sleep * 1000);
	return (0);
}

void	*routine(void *p)
{
	t_philo		*philo;
	int			meals;
	pthread_t	timeout_thread;

	philo = (t_philo *)p;
	pthread_mutex_lock(philo->meal_m);
	philo->last_meal = 0;
	pthread_mutex_unlock(philo->meal_m);
	meals = 0;
	usleep(100 * philo->id);
	pthread_create(&timeout_thread, NULL, supervisor, philo);
	pthread_detach(timeout_thread);
	while (!check_state(philo) && !any_dead_philo(philo))
	{

		if (eat(philo))
			break ;
		if (++meals == philo->nbr_of_meals || check_state(philo))
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
