/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_bubble_v1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 13:21:32 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/21 14:27:44 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int		loop_if_swap(t_sort_result *sort_result, size_t top_i)
{
	int			is_sorted;
	size_t		current;
	size_t		current_1;
	int			*stack;

	stack = sort_result->stack;
	current = top_i;
	current_1 = current ? current - 1 : sort_result->stack_size - 1;
	is_sorted = 1;
	while (current_1 != top_i)
	{
		if (*(stack + current) > *(stack + current_1))
		{
			ft_int_swap(stack + current, stack + current_1);
			add_action(sort_result, "sa");
			is_sorted = 0;
		}
		add_action(sort_result, "ra");
		current = current ? current - 1 : sort_result->stack_size - 1;
		current_1 = current ? current - 1 : sort_result->stack_size - 1;
	}
	add_action(sort_result, "ra");
	return (is_sorted);
}

void			bubble_sort_v1(t_sort_result *sort_result,
														t_list **result_array)
{
	int			is_sorted;
	size_t		top_i;

	(void)result_array;
	top_i = sort_result->stack_size - 1;
	sort_result->action_list_size = 0;
	is_sorted = 0;
	while (!is_sorted)
	{
		is_sorted = loop_if_swap(sort_result, top_i);
	}
	optimize_last_actions(sort_result);
	return ;
}
