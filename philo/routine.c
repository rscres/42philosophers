/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 01:06:56 by renato            #+#    #+#             */
/*   Updated: 2024/02/21 03:06:57 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	think(t_philo *philo)
{
	if (halt(philo))
		return (1);
	print_status(philo->id, "is thinking", get_interval(), philo->super);
	usleep(100 * philo->id); //maybe remove
	return (0);
}

int	rest(t_philo *philo)
{
	if (halt(philo))
		return (1);
	print_status(philo->id, "is sleeping", get_interval(), philo->super);
	usleep(philo->time_to_sleep * 1000);
	return (0);
}

void	*routine(void *p)
{
	t_philo		*philo;
	pthread_t	timeout_thread;

	philo = (t_philo *)p;
	pthread_mutex_lock(&philo->meal_m);
	philo->last_meal = get_interval();
	pthread_mutex_unlock(&philo->meal_m);
	pthread_create(&timeout_thread, NULL, supervisor, philo);
	pthread_detach(timeout_thread);
	usleep(100 * philo->id);
	while (!halt(philo))
	{
		if (eat(philo))
			break ;
		if (think(philo))
			break ;
		if (rest(philo))
			break ;
	}
	return (NULL);
}
