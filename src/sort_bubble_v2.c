/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_bubble_v2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 12:39:52 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/13 18:10:33 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int		loop_down_if_swap(t_sort_result *sort_result)
{
	int				is_sorted;
	t_stack			*stack_a;
	t_list			*end_ptr;

	end_ptr = sort_result->stack_a.top->prev;
	stack_a = &sort_result->stack_a;
	is_sorted = 1;
	while (stack_a->top != end_ptr)
	{
		if (*(int *)stack_a->top->content > *(int *)stack_a->top->next->content)
		{
			if (end_ptr == stack_a->top->next)
				end_ptr = stack_a->top;
			execute_action(sort_result, sa);
			is_sorted = 0;
		}
		execute_action(sort_result, ra);
	}
	execute_action(sort_result, ra);
	return (is_sorted);
}

static int		loop_if_swap(t_sort_result *sort_result)
{
	int			is_sorted;

	is_sorted = loop_down_if_swap(sort_result);
	return (is_sorted);
}

void			bubble_sort_v2(t_sort_result *sort_result,
									t_list **result_array, size_t *max_actions)
{
	int				is_sorted;
	t_stack			*stack_a;

	stack_a = &sort_result->stack_a;
	if (*(int *)stack_a->top->content > sort_result->stack_a.median)
	{
		sort_result->action_list_size = 0;
		execute_action(sort_result, ra);
	}
	else if (*(int *)sort_result->stack_a.top->content <=
													sort_result->stack_a.median)
	{
		sort_result->action_list_size = 0;
		execute_action(sort_result, rra);
	}
	is_sorted = 0;
	while (!is_sorted && sort_result->total_num_of_actions < MAX_ACTIONS)
	{
		is_sorted = loop_if_swap(sort_result);
	}
	optimize_last_actions(sort_result);
	save_result(sort_result, max_actions, result_array);
	return ;
}
