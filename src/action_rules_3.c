/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_rules_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 21:27:21 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/27 21:55:58 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void		create_action_order_v31(t_sort_result *sort_result,
						t_move_action *valid_actions, t_move_action last_action)
{
	t_stack_ptr		stack_ptr;

	stack_ptr = sort_result->stack_ptr;
	if (*(int *)stack_ptr.top_a->content > *(int *)stack_ptr.next_a->content &&
		*(int *)stack_ptr.top_a->content >= sort_result->median &&
		*(int *)stack_ptr.next_a->content >= sort_result->median)
	{
		valid_actions[0] = sa;
		valid_actions[1] = null;
		valid_actions[2] = null;
		valid_actions[3] = null;
	}
	else if (*(int *)stack_ptr.top_a->content < sort_result->median)
	{
		valid_actions[0] = pb;
		valid_actions[1] = null;
		valid_actions[2] = null;
		valid_actions[3] = null;
	}
	else if (*(int *)stack_ptr.bottom_a->content >= sort_result->median &&
		*(int *)stack_ptr.top_a->content >= sort_result->median &&
		*(int *)stack_ptr.top_a->content < *(int *)stack_ptr.bottom_a->content)
	{
		valid_actions[0] = rra;
		valid_actions[1] = null;
		valid_actions[2] = null;
		valid_actions[3] = null;
	}
	else if (*(int *)stack_ptr.top_a->content >= sort_result->median &&
		*(int *)stack_ptr.top_a->content > *(int *)stack_ptr.bottom_a->content)
	{
		valid_actions[0] = ra;
		valid_actions[1] = null;
		valid_actions[2] = null;
		valid_actions[3] = null;
	}
	else if (*(int *)stack_ptr.top_a->content < *(int *)stack_ptr.next_a->content &&
		*(int *)stack_ptr.next_a->content >= sort_result->median)
	{
		valid_actions[0] = sa;
		valid_actions[1] = null;
		valid_actions[2] = null;
		valid_actions[3] = null;
	}
	else if (*(int *)stack_ptr.top_a->content < sort_result->median &&
		*(int *)stack_ptr.next_a->content < sort_result->median &&
		*(int *)stack_ptr.bottom_a->content < sort_result->median)
	{
		valid_actions[0] = v0;
		valid_actions[1] = null;
		valid_actions[2] = null;
		valid_actions[3] = null;
	}
	else if (*(int *)stack_ptr.top_a->content < sort_result->median &&
		*(int *)stack_ptr.next_a->content < sort_result->median &&
		*(int *)stack_ptr.bottom_a->content >= sort_result->median)
	{
		valid_actions[0] = v2;
		valid_actions[1] = null;
		valid_actions[2] = null;
		valid_actions[3] = null;
	}
	else if (last_action == null)
	{
		valid_actions[0] = sa;
		valid_actions[1] = ra;
		valid_actions[2] = rra;
		valid_actions[3] = null;
	}
	else if (last_action == sa)
	{
		valid_actions[0] = ra;
		valid_actions[1] = rra;
		valid_actions[2] = null;
		valid_actions[3] = null;
	}
	else if (last_action == ra)
	{
		valid_actions[0] = sa;
		valid_actions[1] = ra;
		valid_actions[2] = null;
		valid_actions[3] = null;
	}
	else if (last_action == rra)
	{
		valid_actions[0] = sa;
		valid_actions[1] = rra;
		valid_actions[2] = null;
		valid_actions[3] = null;
	}
	else
	{
		valid_actions[0] = null;
		valid_actions[1] = null;
		valid_actions[2] = null;
		valid_actions[3] = null;
	}
	return ;
}
