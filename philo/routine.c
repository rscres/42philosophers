/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 01:06:56 by renato            #+#    #+#             */
/*   Updated: 2024/02/18 01:23:59 by renato           ###   ########.fr       */
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
	while (!check_state(philo) && !is_dead(philo, 0, 0))
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
