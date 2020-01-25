/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_common_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 12:30:27 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/25 12:56:25 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int			*count_max_average(int *array, size_t size)
{
	int			*ptr;
	int			*start_ptr;
	int			average;
	long long	sum;
	size_t		group;

	group = size / 2;
	ptr = array;
	sum = 0;
	while (ptr < (array + group))
	{
		sum += *ptr;
	}
	average = sum / group;
	start_ptr = ptr;
	while (ptr < (array + size))
	{
		sum -= *(ptr - group);
		sum += *ptr;
		if (average < (int)(sum / group))
		{
			average = sum / group;
			start_ptr = ptr - group;
		}
	}
	ptr = array;
	while (ptr < (array + group - 1))
	{
		sum -= *(ptr + size - group);
		sum += *ptr;
		if (average < (int)(sum / group))
		{	
			average = sum / group;
			start_ptr = ptr - group;
		}
	}
	return (start_ptr);
}

