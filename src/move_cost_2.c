/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cost_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 19:21:58 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/13 19:23:24 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void		reset_cost_counters(t_sort_result *sort_result)
{
	size_t			lst_size;
	size_t			c;

	lst_size = sort_result->stack_a.int_lst_size +
											sort_result->stack_b.int_lst_size;
	c = -1;
	while (++c < lst_size)
	{
		sort_result->move_cost[c].source_rx = -1;
		sort_result->move_cost[c].source_rrx = -1;
		sort_result->move_cost[c].target_asc_rx = -1;
		sort_result->move_cost[c].target_asc_rrx = -1;
		sort_result->move_cost[c].target_dec_rx = -1;
		sort_result->move_cost[c].target_dec_rrx = -1;
		sort_result->move_cost[c].source_rx = -1;
		sort_result->move_cost[c].source_rrx = -1;
		sort_result->move_cost[c].target_asc_rx = -1;
		sort_result->move_cost[c].target_asc_rrx = -1;
		sort_result->move_cost[c].target_dec_rx = -1;
		sort_result->move_cost[c].target_dec_rrx = -1;
	}
	return ;
}

void		source_cost(t_list *start_ptr, t_move_cost *move_cost,
																size_t lst_size)
{
	t_list			*ptr;
	size_t			cost_cnt;
	int				first_lap;

	ptr = start_ptr;
	cost_cnt = 0;
	first_lap = 1;
	while (ptr && (ptr != start_ptr || first_lap))
	{
		first_lap = 0;
		move_cost[*(int *)ptr->content].source_rx = cost_cnt;
		move_cost[*(int *)ptr->content].source_rrx =
											(lst_size - cost_cnt) % lst_size;
		cost_cnt++;
		ptr = ptr->next;
	}
	return ;
}

void		source_cost_v3(t_list *start_ptr, t_move_cost *move_cost,
									size_t lst_size, t_sort_group sort_group)
{
	t_list			*ptr;
	size_t			cost_cnt;
	int				first_lap;
	int				integer;

	ptr = start_ptr;
	cost_cnt = 0;
	first_lap = 1;
	while (ptr && (ptr != start_ptr || first_lap))
	{
		first_lap = 0;
		integer = *(int *)ptr->content;
		if (sort_group == none || sort_group == move_cost[integer].sort_group)
		{
			move_cost[*(int *)ptr->content].source_rx = cost_cnt;
			move_cost[*(int *)ptr->content].source_rrx =
											(lst_size - cost_cnt) % lst_size;
		}
		cost_cnt++;
		ptr = ptr->next;
	}
	return ;
}

void		set_target_asc_cost(t_sort_result *sort_result,
							t_stack_name stack_name, t_list *ptr, size_t cost)
{
	int			c;
	int			size;
	int			start;
	int			end;

	end = *(int *)ptr->content;
	start = *(int *)ptr->prev->content;
	size = stack_name == a ? sort_result->stack_b.int_lst_size :
											sort_result->stack_a.int_lst_size;
	c = (start + 1) % sort_result->move_cost_size;
	while (c % sort_result->move_cost_size != end % sort_result->move_cost_size)
	{
		sort_result->move_cost[c].target_asc_rx = cost;
		if (size)
			sort_result->move_cost[c].target_asc_rrx = (size - cost) % size;
		else
			sort_result->move_cost[c].target_asc_rrx = cost;
		c = (c + 1) % sort_result->move_cost_size;
	}
	return ;
}

void		set_target_dec_cost(t_sort_result *sort_result,
							t_stack_name stack_name, t_list *ptr, size_t cost)
{
	int			c;
	int			size;
	int			start;
	int			end;

	end = *(int *)ptr->content;
	start = *(int *)ptr->prev->content;
	size = stack_name == a ? sort_result->stack_b.int_lst_size :
											sort_result->stack_a.int_lst_size;
	c = (start + 1) % sort_result->move_cost_size;
	while (c % sort_result->move_cost_size != end % sort_result->move_cost_size)
	{
		if (size)
			sort_result->move_cost[c].target_dec_rx = (size - cost) % size;
		else
			sort_result->move_cost[c].target_dec_rx = cost;
		sort_result->move_cost[c].target_dec_rrx = cost;
		c = (c + 1) % sort_result->move_cost_size;
	}
	return ;
}
