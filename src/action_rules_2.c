/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_rules_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 10:01:04 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/25 10:23:16 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void		create_action_order_v11(t_sort_result *sort_result,
						t_move_action *valid_actions, t_move_action last_action)
{
	t_stack_ptr		stack_ptr;

	(void)last_action;
	stack_ptr = sort_result->stack_ptr;
	if ((*stack_ptr.top >= sort_result->median ||
		*stack_ptr.next >= sort_result->median) &&
		*stack_ptr.bottom < sort_result->median)
	{
		valid_actions[0] = rra;
		valid_actions[1] = null;
		valid_actions[2] = null;
		valid_actions[3] = null;
	}
	else if (*stack_ptr.top < sort_result->median &&
		*stack_ptr.next < sort_result->median &&
		*stack_ptr.top > *stack_ptr.next)
	{
		valid_actions[0] = sa;
		valid_actions[1] = null;
		valid_actions[2] = null;
		valid_actions[3] = null;
	}
	else if (*stack_ptr.bottom < sort_result->median)
	{
		valid_actions[0] = rra;
		valid_actions[1] = null;
		valid_actions[2] = null;
		valid_actions[3] = null;
	}
	else
	{
		valid_actions[0] = ra;
		valid_actions[1] = null;
		valid_actions[2] = null;
		valid_actions[3] = null;
	}
	return ;
}
