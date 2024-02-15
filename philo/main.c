/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:28:28 by rseelaen          #+#    #+#             */
/*   Updated: 2024/02/15 00:48:53 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putendl(char *s)
{
	while (*s)
		write(1, s++, 1);
	write(1, "\n", 1);
}

void	print_status(int id, char *status, size_t time, t_super *super)
{
	pthread_mutex_lock(super->print);
	printf("%zu %d %s\n", time, id, status);
	pthread_mutex_unlock(super->print);
}

int	init_philos(t_philo **philos, int nbr_of_philos, t_main main)
{
	int	i;

	*philos = malloc(nbr_of_philos * sizeof(t_philo));
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
	if (!forks)
		return (1);
	i = -1;
	while (++i < nbr_of_philos)
		pthread_mutex_init((*forks) + i, NULL);
	return (0);
}

void	init_data(t_main *main, char **argv)
{
	(*main).super = malloc(sizeof(t_super));
	if (!(*main).super)
		return ;
	(*main).super->dead = malloc(sizeof(pthread_mutex_t));
	if (!(*main).super->dead)
		return ;
	(*main).super->print = malloc(sizeof(pthread_mutex_t));
	if (!(*main).super->print)
		return ;
	pthread_mutex_init((*main).super->dead, NULL);
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

int	rest(t_philo *p)
{
	print_status(p->id, "is sleeping", get_interval(), p->super);
	if (p->super->dead_flag == TRUE)
		return (1);
	usleep(p->time_to_sleep * 1000);
	return (0);
}

int	eat(t_philo *p)
{
	pthread_mutex_lock(p->fork_l);
	if (p->super->dead_flag == TRUE)
		return (1);
	print_status(p->id, "has taken a fork", get_interval(), p->super);
	pthread_mutex_lock(p->fork_r);
	if (p->super->dead_flag == TRUE)
		return (1);
	print_status(p->id, "has taken a fork", get_interval(), p->super);
	print_status(p->id, "is eating", get_interval(), p->super);
	p->last_meal = get_cur_time();
	usleep(p->time_to_eat * 1000);
	pthread_mutex_unlock(p->fork_l);
	pthread_mutex_unlock(p->fork_r);
	print_status(p->id, "is thinking", get_interval(), p->super);
	return (0);
}

void	*routine(void *philo)
{
	t_philo	*p;
	// size_t	start;
	// int		i = 0;
	int		meals;

	p = (t_philo *)philo;
	if (p->id % 2 == 0)
		usleep(2000);
	// start = get_cur_time();
	meals = 0;
	while (p->super->dead_flag == FALSE && (p->nbr_of_meals == -1 || meals < p->nbr_of_meals))
	{
		if (eat(p))
			break ;
		meals++;
		if (p->super->dead_flag == TRUE)
			break ;
		if (rest(p))
			break ;
		if (p->super->dead_flag == TRUE)
			break ;
		if (p->last_meal + p->time_to_die < get_cur_time())
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
	i = -1;
	while (++i < main.nbr_of_philos)
		pthread_join(main.philos[i].thread, NULL);
	return (0);
}
