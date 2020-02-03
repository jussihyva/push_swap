/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_rules_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 10:56:26 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/03 07:54:48 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void		create_action_order_v0(t_sort_result *sort_result,
						t_move_action *valid_actions, t_move_action last_action)
{
	t_stack		stack_a;

	(void)last_action;
	stack_a = sort_result->stack_a;
	if (*(int *)stack_a.top->content < sort_result->median)
	{
		valid_actions[0] = rra;
		valid_actions[1] = null;
		valid_actions[2] = null;
		valid_actions[3] = null;
	}
	else
	{
		valid_actions[0] = v1;
		valid_actions[1] = null;
		valid_actions[2] = null;
		valid_actions[3] = null;
	}
	return ;
}

static void		create_action_order_v1(t_sort_result *sort_result,
						t_move_action *valid_actions, t_move_action last_action)
{
	t_stack			stack_a;

	stack_a = sort_result->stack_a;
	if ((*(int *)stack_a.top->content > *(int *)stack_a.top->next->content) &&
		((*(int *)stack_a.top->content >= sort_result->median &&
		*(int *)stack_a.top->next->content >= sort_result->median) ||
		(*(int *)stack_a.top->content < sort_result->median &&
		*(int *)stack_a.top->next->content < sort_result->median)))
	{
		valid_actions[0] = sa;
		valid_actions[1] = null;
		valid_actions[2] = null;
		valid_actions[3] = null;
	}
	else if (*(int *)stack_a.top->prev->content >= sort_result->median &&
		*(int *)stack_a.top->content >= sort_result->median &&
		*(int *)stack_a.top->content < *(int *)stack_a.top->prev)
	{
		valid_actions[0] = rra;
		valid_actions[1] = null;
		valid_actions[2] = null;
		valid_actions[3] = null;
	}
	else if (*(int *)stack_a.top->content >= sort_result->median &&
		*(int *)stack_a.top->content > *(int *)stack_a.top->prev->content)
	{
		valid_actions[0] = ra;
		valid_actions[1] = null;
		valid_actions[2] = null;
		valid_actions[3] = null;
	}
	else if (*(int *)stack_a.top->content < *(int *)stack_a.top->next->content &&
		*(int *)stack_a.top->next->content >= sort_result->median)
	{
		valid_actions[0] = sa;
		valid_actions[1] = null;
		valid_actions[2] = null;
		valid_actions[3] = null;
	}
	else if (*(int *)stack_a.top->content < sort_result->median &&
		*(int *)stack_a.top->next->content < sort_result->median &&
		*(int *)stack_a.top->prev->content < sort_result->median)
	{
		valid_actions[0] = v0;
		valid_actions[1] = null;
		valid_actions[2] = null;
		valid_actions[3] = null;
	}
	else if (*(int *)stack_a.top->content < sort_result->median &&
		*(int *)stack_a.top->next->content < sort_result->median &&
		*(int *)stack_a.top->prev->content >= sort_result->median)
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

static void		create_action_order_v2(t_sort_result *sort_result,
						t_move_action *valid_actions, t_move_action last_action)
{
	t_stack			stack_a;

	(void)last_action;
	stack_a = sort_result->stack_a;
	if (*(int *)stack_a.top->content < sort_result->median &&
						*(int *)stack_a.top->next->content < sort_result->median)
	{
		valid_actions[0] = ra;
		valid_actions[1] = null;
		valid_actions[2] = null;
		valid_actions[3] = null;
	}
	else if (*(int *)stack_a.top->content >= sort_result->median &&
		*(int *)stack_a.top->prev->content >= sort_result->median &&
		*(int *)stack_a.top->content < *(int *)stack_a.top->prev->content)
	{
		valid_actions[0] = rra;
		valid_actions[1] = null;
		valid_actions[2] = null;
		valid_actions[3] = null;
	}
	else if (*(int *)stack_a.top->content < sort_result->median &&
		*(int *)stack_a.top->prev->content >= sort_result->median)
	{
		valid_actions[0] = rra;
		valid_actions[1] = null;
		valid_actions[2] = null;
		valid_actions[3] = null;
	}
	else if (*(int *)stack_a.top->content < sort_result->median)
	{
		valid_actions[0] = ra;
		valid_actions[1] = null;
		valid_actions[2] = null;
		valid_actions[3] = null;
	}
	else if (*(int *)stack_a.top->content < sort_result->median)
	{
		valid_actions[0] = ra;
		valid_actions[1] = null;
		valid_actions[2] = null;
		valid_actions[3] = null;
	}
	else if (*(int *)stack_a.top->content > *(int *)stack_a.top->next->content &&
		*(int *)stack_a.top->next->content >= sort_result->median)
	{
		valid_actions[0] = sa;
		valid_actions[1] = null;
		valid_actions[2] = null;
		valid_actions[3] = null;
	}
	else if (*(int *)stack_a.top->content < *(int *)stack_a.top->next->content)
	{
		valid_actions[0] = ra;
		valid_actions[1] = null;
		valid_actions[2] = null;
		valid_actions[3] = null;
	}
	else if (*(int *)stack_a.top->content > *(int *)stack_a.top->next->content &&
		*(int *)stack_a.top->content >= sort_result->median)
	{
		valid_actions[0] = sa;
		valid_actions[1] = null;
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

void			create_action_order(t_sort_result *sort_result,
						t_move_action *valid_actions, t_move_action last_action,
						t_move_action rule)
{
	if (rule == v0)
		create_action_order_v0(sort_result, valid_actions, last_action);
	else if (rule == v1)
		create_action_order_v1(sort_result, valid_actions, last_action);
	else if (rule == v2)
		create_action_order_v2(sort_result, valid_actions, last_action);
	else if (rule == v11)
		create_action_order_v11(sort_result, valid_actions, last_action);
	else if (rule == v31)
		create_action_order_v31(sort_result, valid_actions, last_action);
	return ;
}
