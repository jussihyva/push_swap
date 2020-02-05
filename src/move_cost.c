/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cost.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 11:16:59 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/05 18:44:23 by jkauppi          ###   ########.fr       */
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
		sort_result->stack_a.move_cost[c].source_rx = -1;
		sort_result->stack_a.move_cost[c].source_rrx = -1;
		sort_result->stack_a.move_cost[c].target_asc_rx = -1;
		sort_result->stack_a.move_cost[c].target_asc_rrx = -1;
		sort_result->stack_a.move_cost[c].target_dec_rx = -1;
		sort_result->stack_a.move_cost[c].target_dec_rrx = -1;
		sort_result->stack_b.move_cost[c].source_rx = -1;
		sort_result->stack_b.move_cost[c].source_rrx = -1;
		sort_result->stack_b.move_cost[c].target_asc_rx = -1;
		sort_result->stack_b.move_cost[c].target_asc_rrx = -1;
		sort_result->stack_b.move_cost[c].target_dec_rx = -1;
		sort_result->stack_b.move_cost[c].target_dec_rrx = -1;
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

static void		target_cost_v1(t_stack *source_stack, t_stack *tartget_stack)
{
	t_list			*ptr;
	size_t			cost_cnt;
	int				start_int;
	int				end_int;
	int				c;
	size_t			lst_size;
	int				first_lap;

	lst_size = tartget_stack->int_lst_size + source_stack->int_lst_size;
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
			source_stack->move_cost[c].target_asc_rx = cost_cnt;
			source_stack->move_cost[c].target_asc_rrx =
											(lst_size - cost_cnt) % lst_size;
			c = (c + 1) % lst_size;
		}
		start_int = *(int *)ptr->content;
		end_int = *(int *)ptr->prev->content;
		c = (start_int + 1) % lst_size;
		while (c % lst_size != end_int % lst_size)
		{
			source_stack->move_cost[c].target_dec_rx = cost_cnt;
			source_stack->move_cost[c].target_dec_rrx =
											(lst_size - cost_cnt) % lst_size;
			c = (c + 1) % lst_size;
		}
		cost_cnt++;
		ptr = ptr->next;
	}
	return ;
}

static void		target_cost_v2(t_stack *source_stack, t_stack *tartget_stack)
{
	t_list			*ptr;
	size_t			cost_cnt;
	int				start_int;
	int				end_int;
	int				c;
	size_t			lst_size;
	int				first_lap;

	lst_size = tartget_stack->int_lst_size + source_stack->int_lst_size;
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
				source_stack->move_cost[c].target_asc_rx = cost_cnt;
				source_stack->move_cost[c].target_asc_rrx =
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
				source_stack->move_cost[c].target_dec_rx = cost_cnt;
				source_stack->move_cost[c].target_dec_rrx =
											(lst_size - cost_cnt) % lst_size;
			}
			c = (c + 1) % lst_size;
		}
		cost_cnt++;
		ptr = ptr->next;
	}
	return ;
}

static void		set_target_asc_cost(t_stack *stack, int start, int end, size_t cost)
{
	int			c;
	int			size;

	size = stack->move_cost_size;
	c = (start + 1) % size;
	while (c % size != end % size)
	{
		stack->move_cost[c].target_asc_rx = cost;
		stack->move_cost[c].target_asc_rrx = (size - cost) % size;
		c = (c + 1) % size;
	}
	return ;
}

static void		set_target_dec_cost(t_stack *stack, int start, int end, size_t cost)
{
	int			c;
	int			size;

	size = stack->move_cost_size;
	c = (start + 1) % size;
	while (c % size != end % size)
	{
		stack->move_cost[c].target_dec_rx = (size - cost) % size;
		stack->move_cost[c].target_dec_rrx = cost;
		c = (c + 1) % size;
	}
	return ;
}

static void		set_all_target_costs_to_zero(t_stack *stack)
{
	int			c;

	c = -1;
	while (++c < stack->move_cost_size)
	{
		stack->move_cost[c].target_asc_rx = 0;
		stack->move_cost[c].target_asc_rrx = 0;
		stack->move_cost[c].target_dec_rx = 0;
		stack->move_cost[c].target_dec_rrx = 0;
	}
	return ;
}

static void		target_cost_v3_3(t_stack *source_stack, t_stack *tartget_stack)
{
	t_list			*ptr;
	size_t			cost_cnt;
	int				start_int;
	int				end_int;
	size_t			lst_size;
	int				first_lap;

	lst_size = tartget_stack->int_lst_size + source_stack->int_lst_size;
	cost_cnt = 0;
	ptr = tartget_stack->top;
	first_lap = 1;
	if (ptr)
	{
		while (ptr != tartget_stack->top || first_lap)
		{
			first_lap = 0;
			end_int = *(int *)ptr->content;
			start_int = *(int *)ptr->prev->content;
			set_target_asc_cost(source_stack, start_int, end_int, cost_cnt);
			start_int = *(int *)ptr->content;
			end_int = *(int *)ptr->prev->content;
			set_target_dec_cost(source_stack, start_int, end_int, cost_cnt);
			cost_cnt++;
			ptr = ptr->next;
		}
	}
	else
		set_all_target_costs_to_zero(source_stack);
	return ;
}

void			count_move_cost_v1(t_sort_result *sort_result)
{
	t_list			*start_ptr;
	t_move_cost		*move_cost;
	size_t			lst_size;

	reset_cost_counters(sort_result);
	move_cost = sort_result->stack_a.move_cost;
	start_ptr = sort_result->stack_a.top;
	lst_size = sort_result->stack_a.int_lst_size;
	source_cost(start_ptr, move_cost, lst_size);
	target_cost_v1(&sort_result->stack_a, &sort_result->stack_b);
	// move_cost = sort_result->stack_b.move_cost;
	// start_ptr = sort_result->stack_b.top;
	// lst_size = sort_result->stack_b.int_lst_size;
	// source_cost(start_ptr, move_cost, lst_size);
	// target_cost(&sort_result->stack_b, &sort_result->stack_a);
	return ;
}

void			count_move_cost_v1_2(t_sort_result *sort_result)
{
	t_list			*start_ptr;
	t_move_cost		*move_cost;
	size_t			lst_size;

	reset_cost_counters(sort_result);
	// move_cost = sort_result->stack_a.move_cost;
	// start_ptr = sort_result->stack_a.top;
	// lst_size = sort_result->stack_a.int_lst_size;
	// source_cost(start_ptr, move_cost, lst_size);
	// target_cost_v1(&sort_result->stack_a, &sort_result->stack_b);
	move_cost = sort_result->stack_b.move_cost;
	start_ptr = sort_result->stack_b.top;
	lst_size = sort_result->stack_b.int_lst_size;
	source_cost(start_ptr, move_cost, lst_size);
	target_cost_v1(&sort_result->stack_b, &sort_result->stack_a);
	return ;
}

void			count_move_cost_v2(t_sort_result *sort_result)
{
	t_list			*start_ptr;
	t_move_cost		*move_cost;
	size_t			lst_size;

	reset_cost_counters(sort_result);
	move_cost = sort_result->stack_a.move_cost;
	start_ptr = sort_result->stack_a.top;
	lst_size = sort_result->stack_a.int_lst_size;
	source_cost(start_ptr, move_cost, lst_size);
	target_cost_v2(&sort_result->stack_a, &sort_result->stack_b);
	// move_cost = sort_result->stack_b.move_cost;
	// start_ptr = sort_result->stack_b.top;
	// lst_size = sort_result->stack_b.int_lst_size;
	// source_cost(start_ptr, move_cost, lst_size);
	// target_cost(&sort_result->stack_b, &sort_result->stack_a);
	return ;
}

void			count_move_cost_v3_3(t_sort_result *sort_result)
{
	t_list			*start_ptr;
	t_move_cost		*move_cost;
	size_t			lst_size;

	reset_cost_counters(sort_result);
	move_cost = sort_result->stack_a.move_cost;
	start_ptr = sort_result->stack_a.top;
	lst_size = sort_result->stack_a.int_lst_size;
	source_cost(start_ptr, move_cost, lst_size);
	target_cost_v3_3(&sort_result->stack_a, &sort_result->stack_b);
	// move_cost = sort_result->stack_b.move_cost;
	// start_ptr = sort_result->stack_b.top;
	// lst_size = sort_result->stack_b.int_lst_size;
	// source_cost(start_ptr, move_cost, lst_size);
	// target_cost(&sort_result->stack_b, &sort_result->stack_a);
	return ;
}

void			count_move_cost_b_v3_3(t_sort_result *sort_result)
{
	t_list			*start_ptr;
	t_move_cost		*move_cost;
	size_t			lst_size;

	// reset_cost_counters(sort_result);
	// move_cost = sort_result->stack_a.move_cost;
	// start_ptr = sort_result->stack_a.top;
	// lst_size = sort_result->stack_a.int_lst_size;
	// source_cost(start_ptr, move_cost, lst_size);
	// target_cost_v3_3(&sort_result->stack_a, &sort_result->stack_b);
	move_cost = sort_result->stack_b.move_cost;
	start_ptr = sort_result->stack_b.top;
	lst_size = sort_result->stack_b.int_lst_size;
	source_cost(start_ptr, move_cost, lst_size);
	target_cost_v3_3(&sort_result->stack_b, &sort_result->stack_a);
	return ;
}
