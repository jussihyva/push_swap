/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_rules_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 10:01:04 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/03 07:55:24 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void		create_action_order_v11(t_sort_result *sort_result,
						t_move_action *valid_actions, t_move_action last_action)
{
	t_stack			stack_a;

	(void)last_action;
	stack_a = sort_result->stack_a;
	if ((*(int *)stack_a.top->content >= sort_result->median ||
		*(int *)stack_a.top->next->content >= sort_result->median) &&
		*(int *)stack_a.top->prev->content < sort_result->median)
	{
		valid_actions[0] = rra;
		valid_actions[1] = null;
		valid_actions[2] = null;
		valid_actions[3] = null;
	}
	else if (*(int *)stack_a.top->content < sort_result->median &&
		*(int *)stack_a.top->next->content < sort_result->median &&
		*(int *)stack_a.top->content > *(int *)stack_a.top->next->content)
	{
		valid_actions[0] = sa;
		valid_actions[1] = null;
		valid_actions[2] = null;
		valid_actions[3] = null;
	}
	else if (last_action == ra)
	{
		valid_actions[0] = ra;
		valid_actions[1] = null;
		valid_actions[2] = null;
		valid_actions[3] = null;
	}
	else if (*(int *)stack_a.top->prev->content < sort_result->median)
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
