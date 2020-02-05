/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_bubble_v1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 13:21:32 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/05 18:06:52 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int		loop_if_swap(t_sort_result *sort_result)
{
	int				is_sorted;
	t_list			*end_ptr;
	t_stack			*stack_a;

	stack_a = &sort_result->stack_a;
	end_ptr = stack_a->top->prev;
	is_sorted = 1;
	while (end_ptr != stack_a->top)
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

void			bubble_sort_v1(t_sort_result *sort_result,
									t_list **result_array, size_t *max_actions)
{
	int			is_sorted;

	sort_result->action_list_size = 0;
	is_sorted = 0;
	while (!is_sorted && sort_result->total_num_of_actions < MAX_ACTIONS)
	{
		is_sorted = loop_if_swap(sort_result);
	}
	save_result(sort_result, max_actions, result_array);
	return ;
}
