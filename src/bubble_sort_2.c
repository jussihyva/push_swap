/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bubble_sort_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 12:39:52 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/16 14:34:30 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void			bubble_sort_v2(t_sort_result *sort_result)
{
	int			is_sorted;
	size_t		top_i;
	size_t		current_i;
	int			*stack_a;

	stack_a = sort_result->stack;
	top_i = sort_result->stack_size - 1;
	sort_result->action_list_size = 0;
	is_sorted = 0;
	while (!is_sorted)
	{
		is_sorted = 1;
		current_i = top_i;
		while (current_i != (top_i - sort_result->stack_size + 1) %
													sort_result->stack_size)
		{
			if (*(stack_a + current_i) > *(stack_a + current_i - 1))
			{
				swap_int(stack_a + current_i, stack_a + current_i - 1);
				add_action(sort_result, "sa");
				is_sorted = 0;
			}
			add_action(sort_result, "ra");
			current_i--;
		}
		add_action(sort_result, "ra");
	}
	return ;
}
