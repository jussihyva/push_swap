/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_bubble_v2_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 12:29:47 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/28 13:23:51 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void			bubble_sort_v2_1(t_sort_result *sort_result,
									t_list **result_array, size_t *max_actions)
{
	int				is_sorted;
	t_stack_ptr		*stack_ptr;

	stack_ptr = &sort_result->stack_ptr;
	while (*(int *)stack_ptr->top_a->content != sort_result->max)
	{
		if (*(int *)stack_ptr->top_a->content > *(int *)stack_ptr->next_a->content)
			execute_action(sort_result, sa);
		execute_action(sort_result, ra);
	}
	execute_action(sort_result, ra);
	is_sorted = 0;
	while (!is_sorted)
	{
		is_sorted = 1;
		while (*(int *)stack_ptr->top_a->content != sort_result->max)
		{
			if (*(int *)stack_ptr->top_a->content > *(int *)stack_ptr->next_a->content)
			{
				execute_action(sort_result, sa);
				is_sorted = 0;
			}
			execute_action(sort_result, ra);
		}
		execute_action(sort_result, ra);
	}
	*max_actions = (*max_actions > sort_result->action_list_size) ?
				sort_result->action_list_size : *max_actions;
	save_result(sort_result, max_actions, result_array);
	return ;
}
