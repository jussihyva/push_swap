/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_pa_pb_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 18:24:37 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/13 19:37:36 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void					set_stacks(t_sort_result *sort_result,
							t_stack_name source_stack_namme,
							t_stack **source_stack, t_stack **target_stack)
{
	if (source_stack_namme == a)
	{
		*source_stack = &sort_result->stack_a;
		*target_stack = &sort_result->stack_b;
	}
	else
	{
		*source_stack = &sort_result->stack_b;
		*target_stack = &sort_result->stack_a;
	}
	return ;
}

static t_stack_status	target_action(t_sort_result *sort_result,
						t_stack_name source_stack_namme, t_stack *target_stack)
{
	t_stack_status		move_status;

	if (source_stack_namme == a)
		move_status = target_stack_action_dec_v3_1(sort_result,
													target_stack);
	else
		move_status = target_stack_action_asc_v3_1(sort_result,
													target_stack);
	return (move_status);
}

void					move_group_to_another_stack_v1(
								t_sort_result *sort_result,
								t_stack_name source_stack_namme,
								t_sort_group sort_group, t_sort_mode sort_mode)
{
	t_stack_status		move_status;
	t_stack				*source_stack;
	t_stack				*target_stack;

	set_stacks(sort_result, source_stack_namme, &source_stack, &target_stack);
	sort_result->sort_group = sort_group;
	while (get_next_move(sort_result, source_stack_namme, sort_group,
																	sort_mode))
	{
		move_status = 0;
		while (move_status != (source_stack_ready | target_stack_ready) &&
				sort_result->total_num_of_actions < MAX_ACTIONS)
		{
			move_status |= source_stack_action_v3_1(sort_result, source_stack);
			if (sort_mode == none || !target_stack->top)
				move_status |= target_stack_ready;
			else
				move_status |= target_action(sort_result,
											source_stack_namme, target_stack);
		}
		if (source_stack_namme == a)
			execute_action(sort_result, pb);
		else
			execute_action(sort_result, pa);
	}
}
