/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 00:46:55 by renato            #+#    #+#             */
/*   Updated: 2024/02/18 00:47:41 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	release_forks(pthread_mutex_t *first_fork, pthread_mutex_t *second_fork)
{
	if (first_fork)
		pthread_mutex_unlock(first_fork);
	if (second_fork)
		pthread_mutex_unlock(second_fork);
}

void	take_forks(t_philo *philo, pthread_mutex_t *first_fork, pthread_mutex_t *second_fork)
{
	pthread_mutex_lock(first_fork);
	if (is_dead(philo))
	{
		pthread_mutex_unlock(first_fork);
		return ;
	}
	print_status(philo->id, "has taken a fork", get_interval(), philo->super);
	pthread_mutex_lock(second_fork);
	if (is_dead(philo))
	{
		release_forks(first_fork, second_fork);
		return ;
	}
}

void	start_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->state_m);
	philo->state = EATING;
	philo->last_meal = get_interval();
	pthread_mutex_unlock(philo->state_m);
	print_status(philo->id, "is eating", get_interval(), philo->super);
}


int	eat(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (philo->id % 2 == 0)
	{
		usleep(100);
		first_fork = philo->fork_r;
		second_fork = philo->fork_l;
	}
	else
	{
		first_fork = philo->fork_l;
		second_fork = philo->fork_r;
	}
	take_forks(philo, first_fork, second_fork);
	if (is_dead(philo))
	{
		release_forks(first_fork, second_fork);
		return (1);
	}
	start_eating(philo);
	if (is_dead(philo))
	{
		release_forks(first_fork, second_fork);
		return (1);
	}
	usleep(philo->time_to_eat * 1000);
	if (is_dead(philo))
	{
		release_forks(first_fork, second_fork);
		return (1);
	}
	release_forks(first_fork, second_fork);
	return (0);
}
