/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:28:28 by rseelaen          #+#    #+#             */
/*   Updated: 2024/02/17 02:58:58 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(int id, char *status, size_t time, t_super *super)
{
	pthread_mutex_lock(super->print);
	printf("%zu %d %s\n", time, id, status);
	pthread_mutex_unlock(super->print);
}

int	is_dead(t_philo *philo)
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

int	has_starved(t_philo *philo, size_t time)
{
	int		last_meal;

	pthread_mutex_lock(philo->meal_m);
	last_meal = philo->last_meal;
	if (time - philo->last_meal > (size_t)philo->time_to_die)
	{
		pthread_mutex_unlock(philo->meal_m);
		return (1);
	}
	pthread_mutex_unlock(philo->meal_m);
	return (0);
}

void	*supervisor(void *m)
{
	t_main	*main;
	int		i;
	size_t	time;
	int		full_philosophers;

	main = (t_main *)m;
	usleep((main->time_to_die * 1000) / 2);
	full_philosophers = 0;
	while (main->super->dead_flag == FALSE)
	{
		i = -1;
		while (++i < main->nbr_of_philos)
		{
			pthread_mutex_lock(main->philos[i].state_m);
			time = get_interval();
			if (has_starved(&main->philos[i], time) && main->philos[i].state != EATING && main->philos[i].state != FULL)
			{
				main->philos[i].state = DEAD;
				pthread_mutex_unlock(main->philos[i].state_m);
				print_status(main->philos[i].id, "died", get_interval(), main->super);
				pthread_mutex_lock(main->super->dead);
				main->super->dead_flag = TRUE;
				pthread_mutex_unlock(main->super->dead);
				break ;
			}
			else if (main->philos[i].state == FULL)
				full_philosophers++;
			pthread_mutex_unlock(main->philos[i].state_m);
		}
		if (full_philosophers == main->nbr_of_philos)
			break ;
		usleep(500);
	}
	return (NULL);
}

int	eat(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (philo->id % 2 == 0)
	{
		usleep(100);
		first_fork = philo->fork_r;
		second_fork = philo->fork_l;
	}
	else
	{
		first_fork = philo->fork_l;
		second_fork = philo->fork_r;
	}
	pthread_mutex_lock(first_fork);
	if (is_dead(philo))
	{
		pthread_mutex_unlock(first_fork);
		return (1);
	}
	print_status(philo->id, "has taken a fork", get_interval(), philo->super);
	pthread_mutex_lock(second_fork);
	if (is_dead(philo))
	{
		pthread_mutex_unlock(first_fork);
		pthread_mutex_unlock(second_fork);
		return (1);
	}
	pthread_mutex_lock(philo->state_m);
	philo->state = EATING;
	pthread_mutex_unlock(philo->state_m);
	print_status(philo->id, "has taken a fork", get_interval(), philo->super);
	print_status(philo->id, "is eating", get_interval(), philo->super);
	if (is_dead(philo))
	{
		pthread_mutex_unlock(first_fork);
		pthread_mutex_unlock(second_fork);
		return (1);
	}
	pthread_mutex_lock(philo->meal_m);
	philo->last_meal = get_interval();
	pthread_mutex_unlock(philo->meal_m);
	usleep(philo->time_to_eat * 1000);
	if (is_dead(philo))
	{
		pthread_mutex_unlock(first_fork);
		pthread_mutex_unlock(second_fork);
		return (1);
	}
	pthread_mutex_unlock(first_fork);
	pthread_mutex_unlock(second_fork);
	pthread_mutex_lock(philo->state_m);
	philo->state = THINKING;
	print_status(philo->id, "is thinking", get_interval(), philo->super);
	pthread_mutex_unlock(philo->state_m);
	return (0);
}

int	rest(t_philo *philo)
{
	pthread_mutex_lock(philo->state_m);
	philo->state = SLEEPING;
	print_status(philo->id, "is sleeping", get_interval(), philo->super);
	pthread_mutex_unlock(philo->state_m);
	usleep(philo->time_to_sleep * 1000);
	return (0);
}

void	*routine(void *p)
{
	t_philo	*philo;
	int		meals;

	philo = (t_philo *)p;
	pthread_mutex_lock(philo->meal_m);
	philo->last_meal = 0;
	pthread_mutex_unlock(philo->meal_m);
	meals = 0;
	while (!check_state(philo) && !is_dead(philo))
	{
		if (eat(philo))
			break ;
		meals++;
		if (philo->nbr_of_meals != -1 && meals >= philo->nbr_of_meals)
		{
			pthread_mutex_lock(philo->state_m);
			philo->state = FULL;
			pthread_mutex_unlock(philo->state_m);
			break ;
		}
		rest(philo);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	int		i;
	t_main	main;

	if (check_input(argc, argv))
		return (1);
	init_data(&main, argv);
	i = -1;
	while (++i < main.nbr_of_philos)
		pthread_create(&main.philos[i].thread, NULL, &routine,
			(void *)&main.philos[i]);
	pthread_create(&main.supervisor, NULL, &supervisor, &main);
	i = -1;
	while (++i < main.nbr_of_philos)
		pthread_join(main.philos[i].thread, NULL);
	pthread_join(main.supervisor, NULL);
	return (0);
}
