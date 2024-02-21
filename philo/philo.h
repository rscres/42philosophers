/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:43:12 by renato            #+#    #+#             */
/*   Updated: 2024/02/21 02:49:17 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define TRUE 1
# define FALSE 0

enum	e_states
{
	ALIVE,
	EATING,
	THINKING,
	SLEEPING,
	DEAD,
	FULL
};

typedef struct s_supervisor
{
	int				dead_flag;
	int				philo_full;
	pthread_mutex_t	dead;
	pthread_mutex_t	print;
}	t_super;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				state;
	size_t			last_meal;
	int				nbr_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_of_meals;
	int				meals_had;
	t_super			*super;
	pthread_mutex_t	state_m;
	pthread_mutex_t	meal_m;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
}	t_philo;

typedef struct s_main
{
	t_philo			*philos;
	pthread_t		supervisor;
	t_super			*super;
	pthread_mutex_t	*forks;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_of_meals;
	int				nbr_of_philos;
}	t_main;

//set_time.c

__uint32_t	get_cur_time(void);
__uint32_t	get_interval(void);

//input_validation.c

int			check_input(int argc, char **argv);

//init.c

void		init_data(t_main *main, char **argv);

//supervisor.c

void		*supervisor(void *m);

//eat.c

int			eat(t_philo *philo);

//print.c

void		print_status(int id, char *status, size_t time, t_super *super);

//checks.c

int			stop_check(t_philo *philo);
int			check_full(t_philo *philo);
int			halt(t_philo *philos);

//routine.c

void		*routine(void *p);

//utils_libft.c

int			ft_atoi(const char *str);

int			ft_usleep(size_t time);

#endif //PHILO_H