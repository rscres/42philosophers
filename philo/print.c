/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 00:48:33 by renato            #+#    #+#             */
/*   Updated: 2024/02/22 14:21:06 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(int id, char *status, size_t time, t_super *super)
{
	pthread_mutex_lock(&super->print_m);
	printf("%zu %d %s\n", time, id, status);
	pthread_mutex_unlock(&super->print_m);
}
