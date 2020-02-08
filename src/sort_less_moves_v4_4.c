/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_less_moves_v4_4.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 12:47:20 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/08 15:15:24 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void			less_moves_sort_v4_4(t_sort_result *sort_result,
									t_list **result_array, size_t *max_actions)
{
	devide_integers_into_groups_v3(sort_result);
	move_group_to_another_stack_v1(sort_result, a, group1, no_sort);
	move_group_to_another_stack_v1(sort_result, a, group2, no_sort);
	move_group_to_another_stack_v1(sort_result, a, group3, no_sort);
	move_group_to_another_stack_v1(sort_result, a, group4, no_sort);
	move_group_to_another_stack_v1(sort_result, a, group5, no_sort);
	move_group_to_another_stack_v1(sort_result, a, group6, no_sort);
	move_group_to_another_stack_v1(sort_result, a, group7, no_sort);
	move_group_to_another_stack_v1(sort_result, b, group7, sort_v1);
	move_group_to_another_stack_v1(sort_result, b, group6, sort_v1);
	move_group_to_another_stack_v1(sort_result, b, group5, sort_v1);
	move_group_to_another_stack_v1(sort_result, b, group4, sort_v1);
	move_group_to_another_stack_v1(sort_result, b, group3, sort_v1);
	move_group_to_another_stack_v1(sort_result, b, group2, sort_v1);
	move_group_to_another_stack_v1(sort_result, b, group1, sort_v1);
	save_result(sort_result, max_actions, result_array);
	return ;
}
