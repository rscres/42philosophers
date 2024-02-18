/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 00:48:33 by renato            #+#    #+#             */
/*   Updated: 2024/02/18 00:48:41 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(int id, char *status, size_t time, t_super *super)
{
	pthread_mutex_lock(super->print);
	printf("%zu %d %s\n", time, id, status);
	pthread_mutex_unlock(super->print);
}
