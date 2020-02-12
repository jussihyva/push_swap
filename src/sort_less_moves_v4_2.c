/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_less_moves_v4_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 18:07:15 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/12 19:17:12 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void					less_moves_sort_v4_2(t_sort_result *sort_result,
									t_list **result_array, size_t *max_actions)
{
	devide_integers_into_groups_v1(sort_result);
	move_max_to_top(sort_result, &sort_result->stack_b,
												sort_result->stack_b.max, rrb);
	move_group_to_another_stack_v1(sort_result, a, group1, no_sort);
	move_all_to_stack_b_v4_1(sort_result);
	move_group_to_another_stack_v1(sort_result, b, group2, sort_v1);
	move_group_to_another_stack_v1(sort_result, b, none, sort_v1);
	save_result(sort_result, max_actions, result_array);
	return ;
}
