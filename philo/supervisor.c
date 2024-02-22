/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 00:43:54 by renato            #+#    #+#             */
/*   Updated: 2024/02/22 00:50:26 by renato           ###   ########.fr       */
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
	pthread_mutex_lock(&philo->super->dead);
	if (philo->super->dead_flag == TRUE)
	{	
		pthread_mutex_unlock(&philo->super->dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->super->dead);
	if (get_interval() - philo->last_meal > time_to_die)
		return (is_dead(philo));
	return (0);
}

static void	change_finish_flag(t_philo *philo)
{
	pthread_mutex_lock(&philo->super_finish);
	philo->finish_flag = TRUE;
	pthread_mutex_unlock(&philo->super_finish);
}

void	*supervisor(void *p)
{
	t_philo	*philo;
	size_t	time_to_die;

	philo = (t_philo *)p;
	time_to_die = (size_t)philo->time_to_die;
	usleep((time_to_die + 1) * 1000);
	while (1)
	{
		pthread_mutex_lock(&philo->meal_m);
		if (is_philo_dead(philo, time_to_die))
		{
			pthread_mutex_unlock(&philo->meal_m);
			change_finish_flag(philo);
			break ;
		}
		else if (check_full(philo))
		{
			pthread_mutex_unlock(&philo->meal_m);
			change_finish_flag(philo);
			break ;
		}
		pthread_mutex_unlock(&philo->meal_m);
		usleep((time_to_die) * 1000);
	}
	return (NULL);
}
