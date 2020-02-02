/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_less_moves_v1_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 07:14:27 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/02 16:13:06 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_list	*select_next_integer(t_sort_result *sort_result)
{
	if (sort_result->stack_ptr.top_a)
	{
		return (sort_result->stack_ptr.top_b);
	}
	else
	{
		if (sort_result->stack_ptr.top_b)
			return (sort_result->stack_ptr.top_b);
		else
			return (NULL);
	}
}

void			less_moves_sort_v1_2(t_sort_result *sort_result,
									t_list **result_array, size_t *max_actions)
{
	t_list		*next_to_move;
	t_stack_ptr		*stack_ptr;

	stack_ptr = &sort_result->stack_ptr;
	move_all_to_stack_b_v2(sort_result);
	while (sort_result->stack_ptr.top_b)
	{
		next_to_move = select_next_integer(sort_result);
		while (sort_result->stack_ptr.top_b != next_to_move)
		{
			if (!(sort_result->total_num_of_actions < 80000))
				break ;
			execute_action(sort_result, rb);
		}
		if (sort_result->stack_ptr.top_a)
		{
			if (*(int *)sort_result->stack_ptr.top_b->content > sort_result->max ||
				*(int *)sort_result->stack_ptr.top_b->content < sort_result->min)
			{
				while (*(int *)sort_result->stack_ptr.top_a->content !=
								sort_result->min)
				{
					if (!(sort_result->total_num_of_actions < 80000))
						break ;
					execute_action(sort_result, ra);
				}
			}
			else
			{
				while (!(*(int *)sort_result->stack_ptr.top_a->content >
								*(int *)sort_result->stack_ptr.top_b->content &&
						*(int *)sort_result->stack_ptr.top_a->prev->content <
								*(int *)sort_result->stack_ptr.top_b->content))
				{
					if (!(sort_result->total_num_of_actions < 80000))
						break ;
					execute_action(sort_result, ra);
				}
			}
		}
		execute_action(sort_result, pa);
	}
//	*max_actions = (*max_actions > sort_result->action_list_size) ?
//				sort_result->action_list_size : *max_actions;
	save_result(sort_result, max_actions, result_array);
	return ;
}
