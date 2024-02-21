/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 00:46:55 by renato            #+#    #+#             */
/*   Updated: 2024/02/21 18:16:58 by rseelaen         ###   ########.fr       */
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
	if (halt(philo))
	{	
		pthread_mutex_unlock(philo->first_fork);
		return (1);
	}
	print_status(philo->id, "has taken a fork", get_interval(), philo->super);
	if (philo->nbr_of_philos == 1)
		return (single_philo(philo, philo->first_fork));
	pthread_mutex_lock(philo->second_fork);
	if (halt(philo))
	{	
		release_forks(philo->first_fork, philo->second_fork);
		return (1);
	}
	pthread_mutex_lock(&philo->meal_m);
	print_status(philo->id, "has taken a fork", get_interval(), philo->super);
	return (0);
}

int	eat(t_philo *philo)
{

	if (take_forks(philo))
		return (1);
	philo->last_meal = get_interval();
	pthread_mutex_unlock(&philo->meal_m);
	if (halt(philo))
	{	
		release_forks(philo->first_fork, philo->second_fork);
		return (1);
	}
	print_status(philo->id, "is eating", get_interval(), philo->super);
	pthread_mutex_lock(&philo->gen_m);
	philo->meals_had++;
	pthread_mutex_unlock(&philo->gen_m);
	pthread_mutex_unlock(&philo->super->dead);
	usleep(philo->time_to_eat * 1000);
	if (check_full(philo))
	{
		release_forks(philo->first_fork, philo->second_fork);
		return (1);
	}
	release_forks(philo->first_fork, philo->second_fork);
	return (0);
}
