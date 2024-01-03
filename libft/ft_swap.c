/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:52:02 by rseelaen          #+#    #+#             */
/*   Updated: 2023/10/27 13:02:31 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//ft_swap() swaps the values of two integers.
void	ft_swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
