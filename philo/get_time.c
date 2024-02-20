/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 16:25:46 by renato            #+#    #+#             */
/*   Updated: 2024/02/19 21:23:45 by rseelaen         ###   ########.fr       */
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

int	ft_usleep(size_t time)
{
	u_int64_t	start;

	start = get_cur_time();
	while ((get_cur_time() - start) < time)
		usleep(time / 10);
	return (0);
}
