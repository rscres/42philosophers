/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 00:43:54 by renato            #+#    #+#             */
/*   Updated: 2024/02/18 00:46:03 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	has_starved(t_philo *philo, size_t time)
{
	int		last_meal;

	last_meal = philo->last_meal;
	if (time - last_meal > (size_t)philo->time_to_die)
		return (1);
	return (0);
}

static void	update_philo_state_to_dead(t_main *main, int i, size_t time)
{
	main->philos[i].state = DEAD;
	pthread_mutex_unlock(main->philos[i].state_m);
	print_status(main->philos[i].id, "died", time, main->super);
	pthread_mutex_lock(main->super->dead);
	main->super->dead_flag = TRUE;
	pthread_mutex_unlock(main->super->dead);
}

static int	supervisor_loop(t_main *main, int i, int full_philosophers)
{
	size_t	time;

	while (++i < main->nbr_of_philos)
	{
		pthread_mutex_lock(main->philos[i].state_m);
		time = get_interval();
		if (has_starved(&main->philos[i], time)
			&& main->philos[i].state != EATING
			&& main->philos[i].state != FULL)
		{
			update_philo_state_to_dead(main, i, time);
			break ;
		}
		else if (main->philos[i].state == FULL)
			full_philosophers++;
		pthread_mutex_unlock(main->philos[i].state_m);
		if (full_philosophers == main->nbr_of_philos)
			break ;
	}
	return (full_philosophers);
}

void	*supervisor(void *m)
{
	t_main	*main;
	int		full_philosophers;

	main = (t_main *)m;
	usleep((main->time_to_die * 1000) / 2);
	full_philosophers = 0;
	while (main->super->dead_flag == FALSE)
	{
		full_philosophers = supervisor_loop(main, -1, full_philosophers);
		if (full_philosophers == main->nbr_of_philos)
			break ;
		usleep(500);
	}
	return (NULL);
}
