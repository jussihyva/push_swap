/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 11:27:19 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/22 11:36:47 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		*ft_intsort(int const *array, size_t size)
{
	int			is_sorted;
	size_t		c;
	int			*sorted_array;

	sorted_array = ft_intcpy(array, size);
	is_sorted = 0;
	while (!is_sorted)
	{
		is_sorted = 1;
		c = -1;
		while (++c < size - 1)
		{
			if (sorted_array[c] > sorted_array[c + 1])
			{
				ft_intswap(sorted_array + c, sorted_array + c + 1);
				is_sorted = 0;
			}
		}
	}
	return (sorted_array);
}
