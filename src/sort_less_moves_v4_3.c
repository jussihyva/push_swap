/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_less_moves_v4_3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 20:11:39 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/13 19:44:27 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void			less_moves_sort_v4_3(t_sort_result *sort_result,
									t_list **result_array, size_t *max_actions)
{
	t_stack		*stack_b;

	stack_b = &sort_result->stack_b;
	devide_integers_into_groups_v2(sort_result);
	move_group_to_another_stack_v1(sort_result, a, group1, sort_v2);
	roll_max_to_top(sort_result, stack_b, stack_b->max, rrb);
	move_group_to_another_stack_v1(sort_result, a, group2, sort_v2);
	roll_max_to_top(sort_result, stack_b, stack_b->max, rrb);
	move_group_to_another_stack_v1(sort_result, a, group3, sort_v2);
	roll_max_to_top(sort_result, stack_b, stack_b->max, rrb);
	move_group_to_another_stack_v1(sort_result, a, group4, sort_v2);
	roll_max_to_top(sort_result, stack_b, stack_b->max, rrb);
	move_group_to_another_stack_v1(sort_result, a, group5, sort_v2);
	roll_max_to_top(sort_result, stack_b, stack_b->max, rrb);
	move_group_to_another_stack_v1(sort_result, a, group6, sort_v2);
	roll_max_to_top(sort_result, stack_b, stack_b->max, rrb);
	move_group_to_another_stack_v1(sort_result, b, none, sort_v2);
	save_result(sort_result, max_actions, result_array);
	return ;
}
