/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 00:46:55 by renato            #+#    #+#             */
/*   Updated: 2024/02/20 01:52:05 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	single_philo(t_philo *philo, pthread_mutex_t *first_fork)
{
	pthread_mutex_unlock(first_fork);
	usleep(philo->time_to_die * 1000);
	print_status(philo->id, "died", get_interval(), philo->super);
	return (1);
}

void	release_forks(pthread_mutex_t *first_fork, pthread_mutex_t *second_fork)
{
	if (first_fork)
		pthread_mutex_unlock(first_fork);
	if (second_fork)
		pthread_mutex_unlock(second_fork);
}

int	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->first_fork);
	if (any_dead_philo(philo))
	{
		pthread_mutex_unlock(philo->first_fork);
		return (1);
	}
	print_status(philo->id, "has taken a fork", get_interval(), philo->super);
	if (philo->nbr_of_philos == 1)
		return (single_philo(philo, philo->first_fork));
	pthread_mutex_lock(philo->second_fork);
	if (any_dead_philo(philo))
	{
		release_forks(philo->first_fork, philo->second_fork);
		return (1);
	}
	print_status(philo->id, "has taken a fork", get_interval(), philo->super);
	return (0);
}

int	eat(t_philo *philo)
{

	if (take_forks(philo))
		return (1);
	pthread_mutex_lock(philo->meal_m);
	philo->last_meal = get_interval();
	pthread_mutex_unlock(philo->meal_m);
	print_status(philo->id, "is eating", get_interval(), philo->super);
	usleep(philo->time_to_eat * 1000);
	if (any_dead_philo(philo))
	{
		release_forks(philo->first_fork, philo->second_fork);
		return (1);
	}
	release_forks(philo->first_fork, philo->second_fork);
	return (0);
}
