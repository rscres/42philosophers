/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 00:49:20 by renato            #+#    #+#             */
/*   Updated: 2024/02/20 01:24:41 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	any_dead_philo(t_philo *philo)
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
