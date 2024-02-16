/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:43:12 by renato            #+#    #+#             */
/*   Updated: 2024/02/16 00:49:18 by renato           ###   ########.fr       */
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
	EATING,
	THINKING,
	SLEEPING,
	DEAD,
	STOP
};

typedef struct s_supervisor
{
	int				dead_flag;
	pthread_mutex_t	*dead;
	pthread_mutex_t	*print;
}	t_super;


typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				state;
	size_t			last_meal;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_of_meals;
	t_super			*super;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	*fork_r;
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

int			ft_atoi(const char *str);

#endif //PHILO_H