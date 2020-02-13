/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_less_moves_v4_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 19:49:14 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/13 10:51:40 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_stack_status	target_stack_action_asc_v2(t_sort_result *sort_result,
					t_stack *stack)
{
	t_next_move		next_move;

	next_move = sort_result->next_move;
	if (*(int *)next_move.integer->content > stack->max ||
		*(int *)next_move.integer->content < stack->min)
	{
		if (*(int *)stack->top->content != stack->min)
		{
			execute_action(sort_result, next_move.target_stack_action);
			return (0);
		}
	}
	else
	{
		if (!(*(int *)stack->top->content >
										*(int *)next_move.integer->content &&
			*(int *)stack->top->prev->content <
											*(int *)next_move.integer->content))
		{
			execute_action(sort_result, next_move.target_stack_action);
			return (0);
		}
	}
	return (target_stack_ready);
}

static t_stack_status	source_stack_action_v2(t_sort_result *sort_result,
																t_stack *stack)
{
	if (stack->top == sort_result->next_move.integer)
		return (source_stack_ready);
	execute_action(sort_result, sort_result->next_move.source_stack_action);
	return (0);
}

static void				move_and_sort_to_stack_a_v1(t_sort_result *sort_result,
															size_t target_size)
{
	t_stack				*stack_a;
	t_stack				*stack_b;
	t_stack_status		move_status;
	size_t				lst_size;

	stack_b = &sort_result->stack_b;
	stack_a = &sort_result->stack_a;
	while (stack_b->int_lst_size && stack_a->int_lst_size < target_size)
	{
		lst_size = stack_a->int_lst_size + stack_b->int_lst_size;
		count_move_cost_b_v3_3(sort_result);
		get_best_move_b_v2(sort_result, lst_size);
		move_status = 0;
		while (move_status != (source_stack_ready | target_stack_ready) &&
				sort_result->total_num_of_actions < MAX_ACTIONS)
		{
			move_status |= source_stack_action_v2(sort_result, stack_b);
			if (stack_a->top)
				move_status |= target_stack_action_asc_v2(sort_result, stack_a);
			else
				move_status |= target_stack_ready;
		}
		execute_action(sort_result, pa);
	}
	return ;
}

void					less_moves_sort_v4_1(t_sort_result *sort_result,
									t_list **result_array, size_t *max_actions)
{
	int			percentage;
	size_t		target_size;

	devide_integers_into_groups(sort_result);
	move_max_to_top(sort_result, &sort_result->stack_b,
												sort_result->stack_b.max, rrb);
	move_all_to_stack_b_v1(sort_result);
	percentage = 100;
	target_size = sort_result->stack_b.int_lst_size * percentage / (double)100;
	move_and_sort_to_stack_a_v1(sort_result, target_size);
	save_result(sort_result, max_actions, result_array);
	return ;
}
