/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cost.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 11:16:59 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/04 12:55:16 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void		reset_cost_counters(t_sort_result *sort_result)
{
	size_t			lst_size;
	size_t			c;

	lst_size = sort_result->stack_a.int_lst_size + sort_result->stack_b.int_lst_size;
	c = -1;
	while (++c < lst_size)
	{
		sort_result->stack_a.move_cost[c].source_forward = -1;
		sort_result->stack_a.move_cost[c].source_backward = -1;
		sort_result->stack_a.move_cost[c].target_forward = -1;
		sort_result->stack_a.move_cost[c].target_backward = -1;
		sort_result->stack_b.move_cost[c].source_forward = -1;
		sort_result->stack_b.move_cost[c].source_backward = -1;
		sort_result->stack_b.move_cost[c].target_forward = -1;
		sort_result->stack_b.move_cost[c].target_backward = -1;
	}
	return ;
}

static void		source_cost(t_list *start_ptr, t_move_cost *move_cost,
																size_t lst_size)
{
	t_list			*ptr;
	size_t			cost_cnt;

	ptr = start_ptr;
	cost_cnt = 0;
	while (ptr && ptr->next != start_ptr)
	{
		move_cost[*(int *)ptr->content].source_forward = cost_cnt;
		move_cost[*(int *)ptr->content].source_backward =
											(lst_size - cost_cnt) % lst_size;
		cost_cnt++;
		ptr = ptr->next;
	}
	return ;
}

// static void		target_cost(t_list *start_ptr, t_move_cost *move_cost,
// 												size_t lst_size, s_sort_dir dir)
// {
// 	t_list			*ptr;
// 	size_t			cost_cnt;
// 	int				start_int;
// 	int				end_int;

// 	ptr = start_ptr;
// 	cost_cnt = 0;
// 	while (ptr && ptr->next != start_ptr)
// 	{
// 		start_int = *(int *)ptr->content;
// 		end_int = *(int *)ptr->prev->content;
// 		move_cost[*(int *)ptr->content].source_forward = cost_cnt;
// 		move_cost[*(int *)ptr->content].source_backward =
// 											(lst_size - cost_cnt) % lst_size;
// 		cost_cnt++;
// 		ptr = ptr->next;
// 	}
// 	return ;
// }

void			count_move_cost(t_sort_result *sort_result)
{
	t_list			*start_ptr;
	t_move_cost		*move_cost;
	size_t			lst_size;

	reset_cost_counters(sort_result);
	move_cost = sort_result->stack_a.move_cost;
	start_ptr = sort_result->stack_a.top;
	lst_size = sort_result->stack_a.int_lst_size;
	source_cost(start_ptr, move_cost, lst_size);
	move_cost = sort_result->stack_b.move_cost;
	start_ptr = sort_result->stack_b.top;
	lst_size = sort_result->stack_b.int_lst_size;
	source_cost(start_ptr, move_cost, lst_size);
	return ;
}