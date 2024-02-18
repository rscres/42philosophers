/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 00:49:20 by renato            #+#    #+#             */
/*   Updated: 2024/02/18 00:54:59 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo, int fork_l, int fork_r)
{
	pthread_mutex_lock(philo->super->dead);
	if (philo->super->dead_flag == TRUE)
	{
		pthread_mutex_unlock(philo->super->dead);
		if (fork_l)
			pthread_mutex_unlock(philo->fork_l);
		if (fork_r)
			pthread_mutex_unlock(philo->fork_r);
		return (1);
	}
	pthread_mutex_unlock(philo->super->dead);
	return (0);
}

int	check_state(t_philo *philo)
{
	pthread_mutex_lock(philo->state_m);
	if (philo->state != DEAD && philo->state != FULL)
	{
		pthread_mutex_unlock(philo->state_m);
		return (0);
	}
	pthread_mutex_unlock(philo->state_m);
	return (1);
}
