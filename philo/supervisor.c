/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 00:43:54 by renato            #+#    #+#             */
/*   Updated: 2024/02/22 13:46:40 by rseelaen         ###   ########.fr       */
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
	pthread_mutex_unlock(&philo->meal_m);
	pthread_mutex_lock(&philo->super_finish);
	philo->finish_flag = TRUE;
	pthread_mutex_unlock(&philo->super_finish);
}

void	*supervisor(void *p)
{
	t_philo	*philo;
	size_t	time_to_die;
	size_t	sleep;

	philo = (t_philo *)p;
	time_to_die = (size_t)philo->time_to_die;
	usleep((time_to_die + 2) * 1000);
	while (1)
	{
		pthread_mutex_lock(&philo->meal_m);
		if (is_philo_dead(philo, time_to_die))
		{
			change_finish_flag(philo);
			break ;
		}
		else if (check_full(philo))
		{
			change_finish_flag(philo);
			break ;
		}
		sleep = time_to_die - (get_interval() - philo->last_meal) + 5;
		pthread_mutex_unlock(&philo->meal_m);
		usleep(sleep * 1000);
	}
	return (NULL);
}
