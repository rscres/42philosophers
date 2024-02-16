/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 16:25:46 by renato            #+#    #+#             */
/*   Updated: 2024/02/15 23:57:42 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

__uint32_t	get_cur_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

__uint32_t	get_interval(void)
{
	static __uint32_t	start;
	__uint32_t			current;

	if (start == 0)
	{
		start = get_cur_time();
		return (0);
	}
	current = get_cur_time();
	return ((current - start));
}
