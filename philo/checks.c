/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 00:49:20 by renato            #+#    #+#             */
/*   Updated: 2024/02/22 14:20:29 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	stop_check(t_philo *philo)
{
	pthread_mutex_lock(&philo->super->dead_m);
	if (philo->super->dead_flag == TRUE)
	{
		pthread_mutex_unlock(&philo->super->dead_m);
		return (1);
	}
	pthread_mutex_unlock(&philo->super->dead_m);
	return (0);
}

int	check_full(t_philo *philo)
{
	pthread_mutex_lock(&philo->gen_m);
	if (philo->meals_had == philo->nbr_of_meals)
	{
		pthread_mutex_unlock(&philo->gen_m);
		return (1);
	}
	pthread_mutex_unlock(&philo->gen_m);
	return (0);
}

int	halt(t_philo *philos)
{
	if (stop_check(philos))
		return (1);
	if (check_full(philos))
		return (1);
	return (0);
}
