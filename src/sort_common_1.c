/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_common_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 14:08:42 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/13 19:39:11 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void			init_sort_result(t_sort_result *sort_result)
{
	sort_result->seq_action_counter = 0;
	sort_result->stack_a.int_lst_size = 0;
	sort_result->stack_b.int_lst_size = 0;
	sort_result->stack_a.int_lst = NULL;
	sort_result->stack_b.int_lst = NULL;
	sort_result->stack_a.top = NULL;
	sort_result->stack_b.top = NULL;
	sort_result->stack_a.average = 0;
	sort_result->action_list_size = 0;
	sort_result->action_list = NULL;
	sort_result->total_num_of_actions = 0;
	sort_result->action_list =
			(t_move_action *)ft_memalloc(sizeof(*sort_result->action_list) *
																MAX_ACTIONS);
	return ;
}

static void		execute_sx_action(t_sort_result *sort_result,
														t_move_action action)
{
	t_stack			*stack_b;
	t_stack			*stack_a;

	stack_b = &sort_result->stack_b;
	stack_a = &sort_result->stack_a;
	if ((action == sa || action == ss) && stack_a->int_lst_size)
	{
		ft_lstswap(stack_a->top, stack_a->top->next);
		stack_a->top = stack_a->top->prev;
	}
	if ((action == sb || action == ss) && stack_b->int_lst_size)
	{
		ft_lstswap(stack_b->top, stack_b->top->next);
		stack_b->top = stack_b->top->prev;
	}
	return ;
}

static void		execute_rrx_action(t_sort_result *sort_result,
														t_move_action action)
{
	if ((action == rra || action == rrr) && sort_result->stack_a.int_lst_size)
		sort_result->stack_a.top = sort_result->stack_a.top->prev;
	if ((action == rrb || action == rrr) && sort_result->stack_b.int_lst_size)
		sort_result->stack_b.top = sort_result->stack_b.top->prev;
	return ;
}

static void		add_action(t_sort_result *sort_result, t_move_action action)
{
	t_move_action	last_action;

	last_action = !sort_result->action_list_size ? null :
		sort_result->action_list[sort_result->action_list_size - 1];
	if (last_action &&
		((last_action == ra && action == rra) ||
		(last_action == rra && action == ra) ||
		(last_action == rb && action == rrb) ||
		(last_action == rrb && action == rb) ||
		(last_action == sa && action == sa)))
	{
		sort_result->action_list_size--;
		count_num_of_consecutive(sort_result);
	}
	else if (check_merge_actions(sort_result, last_action, action))
		;
	else
	{
		if (last_action == action)
			sort_result->seq_action_counter++;
		else
			sort_result->seq_action_counter = 1;
		sort_result->action_list[sort_result->action_list_size] = action;
		sort_result->action_list_size++;
	}
}

void			execute_action(t_sort_result *sort_result, t_move_action action)
{
	sort_result->total_num_of_actions++;
	if (sort_result->total_num_of_actions < MAX_ACTIONS)
	{
		add_action(sort_result, action);
		optimize_last_actions(sort_result);
	}
	if (action == sa || action == sb || action == ss)
		execute_sx_action(sort_result, action);
	if (action == pb || action == pa)
	{
		move_to_stack(sort_result, action);
		min_max(sort_result);
	}
	if ((action == ra || action == rr) && sort_result->stack_a.int_lst_size)
		sort_result->stack_a.top = sort_result->stack_a.top->next;
	if ((action == rb || action == rr) && sort_result->stack_b.int_lst_size)
		sort_result->stack_b.top = sort_result->stack_b.top->next;
	if (action == rra || action == rrb || action == rrr)
		execute_rrx_action(sort_result, action);
	return ;
}
