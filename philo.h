/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:43:12 by renato            #+#    #+#             */
/*   Updated: 2024/02/14 01:58:50 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

# define TRUE 1
# define FALSE 0

enum	e_states
{
	EATING,
	THINKING,
	SLEEPING,
	DEAD
};

typedef struct s_philo
{
	pthread_t		thread;
	int				state;
	size_t			last_meal;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_of_meals;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	*fork_r;
}	t_philo;

typedef struct s_main
{
	t_philo			*philos;
	pthread_mutex_t	*forks;
	int				*dead_flag;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_of_meals;
	int				nbr_of_philos;
}	t_main;

//set_time.c

__uint32_t	get_cur_time(void);
int			get_interval(void);

//input_validation.c

int			check_input(int argc, char **argv);

#endif //PHILO_H