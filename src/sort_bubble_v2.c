/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_bubble_v2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 12:39:52 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/18 15:20:47 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int		loop_down_if_swap(t_sort_result *sort_result)
{
	int			is_sorted;
	size_t		current;
	size_t		current_1;
	int			*stack;

	stack = sort_result->stack;
	current = sort_result->top_ptr;
	current_1 = current ? current - 1 : sort_result->stack_size - 1;
	is_sorted = 1;
	while (current_1 != sort_result->top_ptr)
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

static int		loop_if_swap(t_sort_result *sort_result)
{
	int			is_sorted;

	is_sorted = loop_down_if_swap(sort_result);
	return (is_sorted);
}

void			bubble_sort_v2(t_sort_result *sort_result)
{
	int			is_sorted;

	sort_result->top_ptr = sort_result->stack_size - 1;
	if (sort_result->stack[sort_result->top_ptr] > sort_result->median)
	{
		sort_result->action_list_size = 0;
		add_action(sort_result, "ra");
		sort_result->top_ptr--;
	}
	else if (sort_result->stack[0] <= sort_result->median)
	{
		sort_result->action_list_size = 0;
		add_action(sort_result, "rra");
		sort_result->top_ptr = 0;
	}
	is_sorted = 0;
	while (!is_sorted)
	{
		is_sorted = loop_if_swap(sort_result);
	}
	optimize_last_actions(sort_result);
	return ;
}
