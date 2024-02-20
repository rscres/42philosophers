/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 00:43:54 by renato            #+#    #+#             */
/*   Updated: 2024/02/20 01:45:07 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*supervisor(void *p)
{
	t_philo	*philo;
	int		time_to_die;

	philo = (t_philo *)p;
	time_to_die = philo->time_to_die;
	while (!check_state(philo) && !any_dead_philo(philo))
	{
		usleep(5000);
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
	}
	return (NULL);
}
