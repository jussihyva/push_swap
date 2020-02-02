/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_bubble_v1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 13:21:32 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/02 16:10:02 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int		loop_if_swap(t_sort_result *sort_result)
{
	int			is_sorted;
	t_list		*end_ptr;
	int			*stack;
	t_stack_ptr	*stack_ptr;

	stack = sort_result->stack;
	stack_ptr = &sort_result->stack_ptr;
	end_ptr = stack_ptr->top_a->prev;
	is_sorted = 1;
	while (end_ptr != stack_ptr->top_a)
	{
		if (*(int *)stack_ptr->top_a->content > *(int *)stack_ptr->top_a->next->content)
		{
			if (end_ptr == stack_ptr->top_a->next)
				end_ptr = stack_ptr->top_a;
			execute_action(sort_result, sa);
			is_sorted = 0;
		}
		execute_action(sort_result, ra);
	}
	execute_action(sort_result, ra);
	return (is_sorted);
}

void			bubble_sort_v1(t_sort_result *sort_result,
									t_list **result_array, size_t *max_actions)
{
	int			is_sorted;

	sort_result->action_list_size = 0;
	is_sorted = 0;
	while (!is_sorted && sort_result->total_num_of_actions < 80000)
	{
		is_sorted = loop_if_swap(sort_result);
	}
//	optimize_last_actions(sort_result);
//	*max_actions = (*max_actions > sort_result->action_list_size) ?
//				sort_result->action_list_size : *max_actions;
	save_result(sort_result, max_actions, result_array);
	return ;
}
