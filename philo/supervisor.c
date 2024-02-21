/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 00:43:54 by renato            #+#    #+#             */
/*   Updated: 2024/02/21 18:56:02 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->super->dead);
	philo->super->dead_flag = TRUE;
	pthread_mutex_unlock(&philo->super->dead);
	print_status(philo->id, "died", get_interval(), philo->super);
	return (1);
}

static int	is_philo_dead(t_philo *philo, size_t time_to_die)
{
	if (get_interval() - philo->last_meal > time_to_die)
	{
		pthread_mutex_unlock(&philo->meal_m);
		return (is_dead(philo));
	}
	return (0);
}

void	*supervisor(void *p)
{
	t_philo	*philo;
	size_t	time_to_die;

	philo = (t_philo *)p;
	pthread_mutex_lock(&philo->super_finish);
	time_to_die = (size_t)philo->time_to_die;
	usleep((time_to_die + 1) * 1000);
	while (1)
	{
		pthread_mutex_lock(&philo->meal_m);
		if (is_philo_dead(philo, time_to_die))
			break ;
		else if (check_full(philo))
		{
			pthread_mutex_unlock(&philo->meal_m);
			break ;
		}
		else if (philo->finish_flag == TRUE)
		{
			pthread_mutex_unlock(&philo->meal_m);
			break ;
		}
		pthread_mutex_unlock(&philo->meal_m);
		usleep((time_to_die) * 1000);
	}
	pthread_mutex_unlock(&philo->super_finish);
	// print_status(philo->id, "has finished", get_interval(), philo->super);
	return (NULL);
}
