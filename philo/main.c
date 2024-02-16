/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:28:28 by rseelaen          #+#    #+#             */
/*   Updated: 2024/02/16 01:17:26 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(int id, char *status, size_t time, t_super *super)
{
	pthread_mutex_lock(super->print);
	printf("%zu %d %s\n", time, id, status);
	pthread_mutex_unlock(super->print);
}

void	unlock_forks(pthread_mutex_t *forks, int nbr_of_philos)
{
	int	i;

	i = -1;
	while (++i < nbr_of_philos)
		pthread_mutex_unlock(&forks[i]);
}

int	init_philos(t_philo **philos, int nbr_of_philos, t_main main)
{
	int	i;

	*philos = malloc(sizeof(t_philo) * nbr_of_philos);
	if (!*philos)
		return (1);
	i = -1;
	while (++i < nbr_of_philos)
	{
		(*philos)[i].super = main.super;
		(*philos)[i].id = i + 1;
		(*philos)[i].state = THINKING;
		(*philos)[i].last_meal = 0;
		(*philos)[i].time_to_die = main.time_to_die;
		(*philos)[i].time_to_eat = main.time_to_eat;
		(*philos)[i].time_to_sleep = main.time_to_sleep;
		(*philos)[i].nbr_of_meals = main.nbr_of_meals;
		(*philos)[i].fork_l = &main.forks[i];
		if (i == 0)
			(*philos)[i].fork_r = &main.forks[nbr_of_philos - 1];
		else
			(*philos)[i].fork_r = &main.forks[i - 1];
	}
	return (0);
}

int	init_forks(pthread_mutex_t **forks, int nbr_of_philos)
{
	int	i;

	*forks = malloc(sizeof(pthread_mutex_t) * nbr_of_philos);
	if (!*forks)
		return (1);
	i = -1;
	while (++i < nbr_of_philos)
		pthread_mutex_init(&(*forks)[i], NULL);
	return (0);
}

void	init_data(t_main *main, char **argv)
{
	(*main).super = malloc(sizeof(t_super));
	(*main).super->dead = malloc(sizeof(pthread_mutex_t));
	(*main).super->print = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init((*main).super->dead, NULL);
	pthread_mutex_init((*main).super->print, NULL);
	(*main).super->dead_flag = FALSE;
	(*main).nbr_of_philos = ft_atoi(argv[1]);
	(*main).time_to_die = ft_atoi(argv[2]);
	(*main).time_to_eat = ft_atoi(argv[3]);
	(*main).time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		(*main).nbr_of_meals = ft_atoi(argv[5]);
	else
		(*main).nbr_of_meals = -1;
	init_forks(&main->forks, main->nbr_of_philos);
	init_philos(&main->philos, main->nbr_of_philos, *main);
}

void	*supervisor(void *main)
{
	t_main	*m;
	int		i;

	m = (t_main *)main;
	while (m->super->dead_flag == FALSE)
	{
		i = 0;
		while (i < m->nbr_of_philos)
		{
			if (get_cur_time() - m->philos[i].last_meal > (size_t)m->time_to_die
				&& m->philos[i].state != FULL && m->philos[i].state != EATING)
			{
				m->super->dead_flag = TRUE;
				print_status(m->philos[i].id, "died", get_interval(),
					m->super);
				unlock_forks(m->forks, m->nbr_of_philos);
				break ;
			}
			i++;
		}
		usleep(100);
	}
	return (0);
}

int	rest(t_philo *p)
{
	p->state = SLEEPING;
	print_status(p->id, "is sleeping", get_interval(), p->super);
	if (p->super->dead_flag == TRUE)
		return (1);
	usleep(p->time_to_sleep * 1000);
	return (0);
}

int	eat_odd(t_philo *p)
{
	pthread_mutex_lock(p->fork_l);
	if (p->super->dead_flag == TRUE)
		return (1);
	print_status(p->id, "has taken a fork", get_interval(), p->super);
	pthread_mutex_lock(p->fork_r);
	if (p->super->dead_flag == TRUE)
		return (1);
	print_status(p->id, "has taken a fork", get_interval(), p->super);
	return (0);
}

int	eat_even(t_philo *p)
{
	pthread_mutex_lock(p->fork_r);
	if (p->super->dead_flag == TRUE)
		return (1);
	print_status(p->id, "has taken a fork", get_interval(), p->super);
	pthread_mutex_lock(p->fork_l);
	if (p->super->dead_flag == TRUE)
		return (1);
	print_status(p->id, "has taken a fork", get_interval(), p->super);
	return (0);
}

int	eat(t_philo *p)
{
	if (p->id % 2 == 0)
	{
		if (eat_even(p))
			return (1);
	}
	else
	{
		if (eat_odd(p))
			return (1);
	}
	p->state = EATING;
	p->last_meal = get_cur_time();
	print_status(p->id, "is eating", get_interval(), p->super);
	usleep(p->time_to_eat * 1000);
	pthread_mutex_unlock(p->fork_l);
	pthread_mutex_unlock(p->fork_r);
	p->state = THINKING;
	print_status(p->id, "is thinking", get_interval(), p->super);
	return (0);
}

void	*routine(void *philo)
{
	t_philo	*p;
	int		meals;

	p = (t_philo *)philo;
	p->last_meal = get_cur_time();
	if (p->id % 2 == 0)
		usleep(2000);
	meals = 0;
	while (p->super->dead_flag == FALSE && (p->nbr_of_meals == -1
			|| meals < p->nbr_of_meals))
	{
		if (eat(p))
			break ;
		meals++;
		if (p->super->dead_flag == TRUE || (p->nbr_of_meals != -1
				&& meals >= p->nbr_of_meals))
		{
			p->state = FULL;
			break ;
		}
		if (rest(p))
			break ;
		if (p->super->dead_flag == TRUE)
			break ;
		if (get_cur_time() - p->last_meal > (size_t)p->time_to_die)
		{
			p->super->dead_flag = TRUE;
			print_status(p->id, "died", get_interval(), p->super);
			break ;
		}
	}
	return (0);
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
