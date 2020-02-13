/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_next_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 10:42:31 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/13 10:49:33 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void			save_next_move(t_next_move *next_move,
					t_move_action source_action, t_move_action target_action,
														t_move_cost move_cost)
{
	next_move->integer = move_cost.integer;
	next_move->source_stack_action = source_action;
	next_move->target_stack_action = target_action;
	return ;
}

static void		check_source_rx_and_target_asc(t_next_move *next_move,
							t_move_cost move_cost, size_t *best_num_of_moves)
{
	size_t			moves;

	if (move_cost.target_asc_rx != -1)
	{
		moves = ft_max(move_cost.source_rx, move_cost.target_asc_rx);
		if (*best_num_of_moves > moves)
		{
			save_next_move(next_move, rb, ra, move_cost);
			*best_num_of_moves = moves;
		}
	}
	if (move_cost.target_asc_rrx != -1)
	{
		moves = move_cost.source_rx + move_cost.target_asc_rrx;
		if (*best_num_of_moves > moves)
		{
			save_next_move(next_move, rb, rra, move_cost);
			*best_num_of_moves = moves;
		}
	}
	return ;
}

static void		check_source_rrx_and_target_asc(t_next_move *next_move,
							t_move_cost move_cost, size_t *best_num_of_moves)
{
	size_t			moves;

	if (move_cost.target_asc_rrx != -1)
	{
		moves = ft_max(move_cost.source_rrx, move_cost.target_asc_rrx);
		if (*best_num_of_moves > moves)
		{
			save_next_move(next_move, rrb, rra, move_cost);
			*best_num_of_moves = moves;
		}
	}
	if (move_cost.target_asc_rx != -1)
	{
		moves = move_cost.source_rrx + move_cost.target_asc_rx;
		if (*best_num_of_moves > moves)
		{
			save_next_move(next_move, rrb, ra, move_cost);
			*best_num_of_moves = moves;
		}
	}
	return ;
}

void				get_best_move_b_v2(t_sort_result *sort_result, size_t lst_size)
{
	size_t			best_num_of_moves;
	size_t			c;
	t_next_move		*next_move;
	t_move_cost		*move_cost;

	move_cost = sort_result->move_cost;
	best_num_of_moves = INT_MAX;
	c = -1;
	next_move = &sort_result->next_move;
	while (++c < lst_size)
	{
		if (move_cost[c].source_rx != -1)
			check_source_rx_and_target_asc(next_move, move_cost[c],
															&best_num_of_moves);
		if (move_cost[c].source_rrx != -1)
			check_source_rrx_and_target_asc(next_move, move_cost[c],
															&best_num_of_moves);
	}
	return ;
}
