/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bubble_sort_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 12:39:52 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/14 13:02:38 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void			bubble_sort_v2(int *stack, int size, t_sort_result *sort_result)
{
	int		is_sorted;
	int		*top_ptr;

	sort_result->average = cal_average(stack, size);
	is_sorted = 1;
	top_ptr = stack + size - 1;
	sort_result->action_list_size = 0;
	while (is_sorted)
	{
		is_sorted = 0;
		while (top_ptr > stack)
		{
			if (*top_ptr > *(top_ptr - 1))
			{
				swap_int(top_ptr, top_ptr - 1);
				add_action(sort_result, "sa");
				is_sorted = 1;
			}
			add_action(sort_result, "ra");
			top_ptr--;
		}
		add_action(sort_result, "ra");
		top_ptr = stack + size - 1;
	}
	return ;
}