/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cost_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 11:16:59 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/13 19:38:10 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void		set_all_target_costs_to_zero(t_sort_result *sort_result)
{
	int			c;

	c = -1;
	while (++c < sort_result->move_cost_size)
	{
		sort_result->move_cost[c].target_asc_rx = 0;
		sort_result->move_cost[c].target_asc_rrx = 0;
		sort_result->move_cost[c].target_dec_rx = 0;
		sort_result->move_cost[c].target_dec_rrx = 0;
	}
	return ;
}

static void		target_cost_v3_3(t_sort_result *sort_result,
								t_stack_name stack_name, t_stack *target_stack)
{
	t_list			*ptr;
	size_t			cost_cnt;
	int				first_lap;

	cost_cnt = 0;
	ptr = target_stack->top;
	first_lap = 1;
	if (ptr && target_stack->int_lst_size > 1)
	{
		while (ptr != target_stack->top || first_lap)
		{
			first_lap = 0;
			set_target_asc_cost(sort_result, stack_name, ptr, cost_cnt);
			set_target_dec_cost(sort_result, stack_name, ptr, cost_cnt);
			cost_cnt++;
			ptr = ptr->next;
		}
	}
	else
		set_all_target_costs_to_zero(sort_result);
	return ;
}

void			count_move_cost_b_v3_3(t_sort_result *sort_result)
{
	t_list			*start_ptr;
	t_move_cost		*move_cost;
	size_t			lst_size;

	reset_cost_counters(sort_result);
	move_cost = sort_result->move_cost;
	start_ptr = sort_result->stack_b.top;
	lst_size = sort_result->stack_b.int_lst_size;
	source_cost(start_ptr, move_cost, lst_size);
	target_cost_v3_3(sort_result, b, &sort_result->stack_a);
	return ;
}

void			count_move_cost_v4_1(t_sort_result *sort_result,
								t_stack_name source_stack_namme,
								t_sort_group sort_group, t_sort_mode sort_mode)
{
	t_stack			*source_stack;
	t_stack			*target_stack;

	(void)sort_group;
	set_stacks(sort_result, source_stack_namme, &source_stack, &target_stack);
	reset_cost_counters(sort_result);
	source_cost_v3(source_stack->top, sort_result->move_cost,
										source_stack->int_lst_size, sort_group);
	if (sort_mode == none)
		set_all_target_costs_to_zero(sort_result);
	else if (sort_mode == sort_v2)
		set_all_target_costs_to_zero(sort_result);
	else
		target_cost_v3_3(sort_result, b, target_stack);
	return ;
}
