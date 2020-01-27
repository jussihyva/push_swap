/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_bubble_v2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 12:39:52 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/27 15:54:08 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int		loop_down_if_swap(t_sort_result *sort_result)
{
	int				is_sorted;
	t_stack_ptr		*stack_ptr;
	int				*end_ptr;

	end_ptr = sort_result->stack_ptr.top;
	stack_ptr = &sort_result->stack_ptr;
	is_sorted = 1;
	while (stack_ptr->next != end_ptr)
	{
		if (*stack_ptr->top > *stack_ptr->next)
		{
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
	t_stack_ptr		*stack_ptr;

	stack_ptr = &sort_result->stack_ptr;
	if (*stack_ptr->top > sort_result->median)
	{
		sort_result->action_list_size = 0;
		execute_action(sort_result, ra);
	}
	else if (sort_result->stack[0] <= sort_result->median)
	{
		sort_result->action_list_size = 0;
		execute_action(sort_result, rra);
	}
	is_sorted = 0;
	while (!is_sorted && sort_result->total_num_of_actions < 80000)
	{
		is_sorted = loop_if_swap(sort_result);
	}
	optimize_last_actions(sort_result);
	ft_lstadd_e(result_array, ft_lstnew(sort_result, sizeof(*sort_result)));
	*max_actions = (*max_actions > sort_result->action_list_size) ?
				sort_result->action_list_size : *max_actions;
	return ;
}
