/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_less_moves_v1_3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 08:21:48 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/03 11:01:52 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_list	*select_next_integer(t_sort_result *sort_result)
{
	if (sort_result->stack_a.top)
	{
		return (sort_result->stack_b.top);
	}
	else
	{
		if (sort_result->stack_b.top)
			return (sort_result->stack_b.top);
		else
			return (NULL);
	}
}

void			less_moves_sort_v1_3(t_sort_result *sort_result,
									t_list **result_array, size_t *max_actions)
{
	t_list		*next_to_move;

	move_all_to_stack_b_v3(sort_result);
	while (sort_result->stack_b.top)
	{
		next_to_move = select_next_integer(sort_result);
		while (sort_result->stack_b.top != next_to_move)
		{
			if (!(sort_result->total_num_of_actions < 80000))
				break ;
			execute_action(sort_result, rb);
		}
		if (sort_result->stack_a.top)
		{
			if (*(int *)sort_result->stack_b.top->content > sort_result->stack_a.max ||
				*(int *)sort_result->stack_b.top->content < sort_result->stack_a.min)
			{
				while (*(int *)sort_result->stack_a.top->content !=
								sort_result->stack_a.min)
				{
					if (!(sort_result->total_num_of_actions < 80000))
						break ;
					execute_action(sort_result, ra);
				}
			}
			else
			{
				while (!(*(int *)sort_result->stack_a.top->content >
								*(int *)sort_result->stack_b.top->content &&
						*(int *)sort_result->stack_a.top->prev->content <
								*(int *)sort_result->stack_b.top->content))
				{
					if (!(sort_result->total_num_of_actions < 80000))
						break ;
					execute_action(sort_result, ra);
				}
			}
		}
		execute_action(sort_result, pa);
	}
	save_result(sort_result, max_actions, result_array);
	return ;
}
