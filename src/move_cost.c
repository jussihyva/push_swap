/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cost.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 11:16:59 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/08 13:31:39 by jkauppi          ###   ########.fr       */
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

static void		source_cost(t_list *start_ptr, t_move_cost *move_cost,
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

static void		source_cost_v3(t_list *start_ptr, t_move_cost *move_cost,
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

static void		target_cost_v1(t_move_cost *move_cost, int move_cost_size,
														t_stack *tartget_stack)
{
	t_list			*ptr;
	size_t			cost_cnt;
	int				start_int;
	int				end_int;
	int				c;
	size_t			lst_size;
	int				first_lap;

	lst_size = (size_t)move_cost_size;
	cost_cnt = 0;
	ptr = tartget_stack->top;
	first_lap = 1;
	while (ptr && (ptr != tartget_stack->top || first_lap)) 
	{
		first_lap = 0;
		end_int = *(int *)ptr->content;
		start_int = *(int *)ptr->prev->content;
		c = (start_int + 1) % lst_size;
		while (c % lst_size != end_int % lst_size)
		{
			move_cost[c].target_asc_rx = cost_cnt;
			move_cost[c].target_asc_rrx = (lst_size - cost_cnt) % lst_size;
			c = (c + 1) % lst_size;
		}
		start_int = *(int *)ptr->content;
		end_int = *(int *)ptr->prev->content;
		c = (start_int + 1) % lst_size;
		while (c % lst_size != end_int % lst_size)
		{
			move_cost[c].target_dec_rx = cost_cnt;
			move_cost[c].target_dec_rrx = (lst_size - cost_cnt) % lst_size;
			c = (c + 1) % lst_size;
		}
		cost_cnt++;
		ptr = ptr->next;
	}
	return ;
}

static void		target_cost_v2(t_move_cost *move_cost, int move_cost_size,
														t_stack *tartget_stack)
{
	t_list			*ptr;
	size_t			cost_cnt;
	int				start_int;
	int				end_int;
	int				c;
	size_t			lst_size;
	int				first_lap;

	lst_size = (size_t)move_cost_size;
	cost_cnt = 0;
	ptr = tartget_stack->top;
	first_lap = 1;
	while (ptr && (ptr != tartget_stack->top || first_lap)) 
	{
		first_lap = 0;
		end_int = *(int *)ptr->content;
		start_int = *(int *)ptr->prev->content;
		c = (start_int + 1) % lst_size;
		while (c % lst_size != end_int % lst_size)
		{
			if (c < 50)
			{
				move_cost[c].target_asc_rx = cost_cnt;
				move_cost[c].target_asc_rrx =
												(lst_size - cost_cnt) % lst_size;
			}
			c = (c + 1) % lst_size;
		}
		start_int = *(int *)ptr->content;
		end_int = *(int *)ptr->prev->content;
		c = (start_int + 1) % lst_size;
		while (c % lst_size != end_int % lst_size)
		{
			if (c < 50)
			{
				move_cost[c].target_dec_rx = cost_cnt;
				move_cost[c].target_dec_rrx =
											(lst_size - cost_cnt) % lst_size;
			}
			c = (c + 1) % lst_size;
		}
		cost_cnt++;
		ptr = ptr->next;
	}
	return ;
}

static void		set_target_asc_cost(t_sort_result *sort_result,
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

static void		set_target_dec_cost(t_sort_result *sort_result,
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

static void		target_cost_v3_3(t_sort_result *sort_result, t_stack_name stack_name, t_stack *target_stack)
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

void			count_move_cost_v1(t_sort_result *sort_result)
{
	t_list			*start_ptr;
	t_move_cost		*move_cost;
	size_t			lst_size;

	reset_cost_counters(sort_result);
	move_cost = sort_result->move_cost;
	start_ptr = sort_result->stack_a.top;
	lst_size = sort_result->stack_a.int_lst_size;
	source_cost(start_ptr, move_cost, lst_size);
	target_cost_v1(move_cost, sort_result->move_cost_size, &sort_result->stack_b);
	return ;
}

void			count_move_cost_v1_2(t_sort_result *sort_result)
{
	t_list			*start_ptr;
	t_move_cost		*move_cost;
	size_t			lst_size;

	reset_cost_counters(sort_result);
	move_cost = sort_result->move_cost;
	start_ptr = sort_result->stack_b.top;
	lst_size = sort_result->stack_b.int_lst_size;
	source_cost(start_ptr, move_cost, lst_size);
	target_cost_v1(move_cost, sort_result->move_cost_size, &sort_result->stack_a);
	return ;
}

void			count_move_cost_v2(t_sort_result *sort_result)
{
	t_list			*start_ptr;
	t_move_cost		*move_cost;
	size_t			lst_size;

	reset_cost_counters(sort_result);
	move_cost = sort_result->move_cost;
	start_ptr = sort_result->stack_a.top;
	lst_size = sort_result->stack_a.int_lst_size;
	source_cost(start_ptr, move_cost, lst_size);
	target_cost_v2(move_cost, sort_result->move_cost_size, &sort_result->stack_b);
	return ;
}

void			count_move_cost_v3_3(t_sort_result *sort_result)
{
	t_list			*start_ptr;
	t_move_cost		*move_cost;
	size_t			lst_size;

	reset_cost_counters(sort_result);
	move_cost = sort_result->move_cost;
	start_ptr = sort_result->stack_a.top;
	lst_size = sort_result->stack_a.int_lst_size;
	source_cost(start_ptr, move_cost, lst_size);
	target_cost_v3_3(sort_result, a, &sort_result->stack_b);
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

void	count_move_cost_v4_1(t_sort_result *sort_result,
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
