/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_next_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 18:49:15 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/13 19:15:28 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static	void		check_rx_rx(t_move_cost *move_cost, t_next_move *next_move,
												t_stack_name source_stack_namme)
{
	size_t			moves;

	if ((source_stack_namme == a &&
			move_cost->source_rx != -1 && move_cost->target_dec_rx != -1) ||
		(source_stack_namme == b &&
			move_cost->source_rx != -1 && move_cost->target_asc_rx != -1))
	{
		if (source_stack_namme == a)
			moves = ft_max(move_cost->source_rx, move_cost->target_dec_rx);
		else
			moves = ft_max(move_cost->source_rx, move_cost->target_asc_rx);
		if (next_move->best_num_of_moves > moves)
		{
			next_move->best_num_of_moves = moves;
			next_move->integer = move_cost->integer;
			if (source_stack_namme == a)
				save_next_move(next_move, ra, rb, *move_cost);
			else
				save_next_move(next_move, rb, ra, *move_cost);
		}
	}
	return ;
}

static	void		check_rrx_rrx(t_move_cost *move_cost,
						t_next_move *next_move, t_stack_name source_stack_namme)
{
	size_t			moves;

	if ((source_stack_namme == a &&
			move_cost->source_rrx != -1 && move_cost->target_dec_rrx != -1) ||
		(source_stack_namme == b &&
			move_cost->source_rrx != -1 && move_cost->target_asc_rrx != -1))
	{
		if (source_stack_namme == a)
			moves = ft_max(move_cost->source_rrx, move_cost->target_dec_rrx);
		else
			moves = ft_max(move_cost->source_rrx, move_cost->target_asc_rrx);
		if (next_move->best_num_of_moves > moves)
		{
			next_move->best_num_of_moves = moves;
			next_move->integer = move_cost->integer;
			if (source_stack_namme == a)
				save_next_move(next_move, rra, rrb, *move_cost);
			else
				save_next_move(next_move, rrb, rra, *move_cost);
		}
	}
	return ;
}

static	void		check_rx_rrx(t_move_cost *move_cost, t_next_move *next_move,
												t_stack_name source_stack_namme)
{
	size_t			moves;

	if ((source_stack_namme == a &&
			move_cost->source_rx != -1 && move_cost->target_dec_rrx != -1) ||
		(source_stack_namme == b &&
			move_cost->source_rx != -1 && move_cost->target_asc_rrx != -1))
	{
		if (source_stack_namme == a)
			moves = move_cost->source_rx + move_cost->target_dec_rrx;
		else
			moves = move_cost->source_rx + move_cost->target_asc_rrx;
		if (next_move->best_num_of_moves > moves)
		{
			next_move->best_num_of_moves = moves;
			if (source_stack_namme == a)
				save_next_move(next_move, ra, rrb, *move_cost);
			else
				save_next_move(next_move, rb, rra, *move_cost);
		}
	}
	return ;
}

static	void		check_rrx_rx(t_move_cost *move_cost, t_next_move *next_move,
												t_stack_name source_stack_name)
{
	size_t			moves;

	if ((source_stack_name == a &&
			move_cost->source_rrx != -1 && move_cost->target_dec_rx != -1) ||
		(source_stack_name == b &&
			move_cost->source_rrx != -1 && move_cost->target_asc_rx != -1))
	{
		if (source_stack_name == a)
			moves = move_cost->source_rrx + move_cost->target_dec_rx;
		else
			moves = move_cost->source_rrx + move_cost->target_asc_rx;
		if (next_move->best_num_of_moves > moves)
		{
			next_move->best_num_of_moves = moves;
			if (source_stack_name == a)
				save_next_move(next_move, rra, rb, *move_cost);
			else
				save_next_move(next_move, rrb, ra, *move_cost);
		}
	}
	return ;
}

int					get_next_move(t_sort_result *sort_result,
								t_stack_name source_stack_namme,
								t_sort_group sort_group, t_sort_mode sort_mode)
{
	t_next_move		*next_move;
	size_t			c;
	t_move_cost		*move_cost;

	move_cost = sort_result->move_cost;
	count_move_cost_v4_1(sort_result, source_stack_namme, sort_group,
																	sort_mode);
	next_move = &sort_result->next_move;
	next_move->integer = NULL;
	next_move->best_num_of_moves = INT_MAX;
	if (source_stack_namme == b || sort_result->stack_a.int_lst_size > 2)
	{
		c = -1;
		while (++c < (size_t)sort_result->move_cost_size)
		{
			check_rx_rx(&move_cost[c], next_move, source_stack_namme);
			check_rx_rrx(&move_cost[c], next_move, source_stack_namme);
			check_rrx_rrx(&move_cost[c], next_move, source_stack_namme);
			check_rrx_rx(&move_cost[c], next_move, source_stack_namme);
		}
	}
	if (next_move->integer)
		return (1);
	return (0);
}
