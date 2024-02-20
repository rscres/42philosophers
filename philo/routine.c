/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 01:06:56 by renato            #+#    #+#             */
/*   Updated: 2024/02/19 22:50:24 by rseelaen         ###   ########.fr       */
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

int	check_flag(t_philo *philo)
{
	pthread_mutex_lock(philo->super->dead);
	if (philo->super->dead_flag == TRUE)
	{
		pthread_mutex_unlock(philo->super->dead);
		return (1);
	}
	pthread_mutex_unlock(philo->super->dead);
	return (0);
}

void	*check_timeout(void *p)
{
	t_philo	*philo = (t_philo *)p;
	int		time_to_die = philo->time_to_die;

	while (1)
	{
		if (check_flag(philo))
			break ;
		pthread_mutex_lock(philo->meal_m);
		if (get_interval() - philo->last_meal > (size_t)time_to_die)
		{
			pthread_mutex_unlock(philo->meal_m);
			pthread_mutex_lock(philo->super->dead);
			philo->super->dead_flag = TRUE;
			pthread_mutex_unlock(philo->super->dead);
			print_status(philo->id, "died", get_interval(), philo->super);
			break ;
		}
		pthread_mutex_unlock(philo->meal_m);
		usleep(1000);
	}
	return (NULL);
}

void	*routine(void *p)
{
	t_philo	*philo;
	int		meals;
	pthread_t timeout_thread;

	philo = (t_philo *)p;
	pthread_mutex_lock(philo->meal_m);
	philo->last_meal = 0;
	pthread_mutex_unlock(philo->meal_m);
	meals = 0;
	usleep(100 * philo->id);
	pthread_create(&timeout_thread, NULL, check_timeout, philo);
	while (philo->state != FULL && !check_flag(philo))
	{
		if (eat(philo))
			break ;
		meals++;
		if (philo->nbr_of_meals != -1 && meals == philo->nbr_of_meals)
		{
			pthread_mutex_lock(philo->state_m);
			philo->state = FULL;
			pthread_mutex_unlock(philo->state_m);
			break ;
		}
		think(philo);
		rest(philo);
	}
	pthread_join(timeout_thread, NULL);
	return (NULL);
}
