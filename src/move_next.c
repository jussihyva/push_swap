/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_next.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 18:49:15 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/06 20:19:18 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

size_t	ft_max(size_t nbr1, size_t nbr2)
{
	return (nbr1 > nbr2 ? nbr1 : nbr2);
}

t_stack_status		source_stack_action_v3_1(t_sort_result *sort_result,
																t_stack *stack)
{
	if (stack->top == sort_result->next_move.integer)
		return (source_stack_ready);
	execute_action(sort_result, sort_result->next_move.source_stack_action);
	return (0);
}

t_stack_status		target_stack_action_asc_v3_1(t_sort_result *sort_result,
																t_stack *stack)
{
	if (stack->top)
	{
		if (*(int *)sort_result->next_move.integer->content > stack->max ||
			*(int *)sort_result->next_move.integer->content < stack->min)
		{
			if (*(int *)stack->top->content != stack->min)
			{
				execute_action(sort_result, sort_result->next_move.target_stack_action);
				return (0);
			}
		}
		else
		{
			if (!(*(int *)stack->top->content > *(int *)sort_result->next_move.integer->content &&
				*(int *)stack->top->prev->content < *(int *)sort_result->next_move.integer->content))
			{
				execute_action(sort_result, sort_result->next_move.target_stack_action);
				return (0);
			}
		}
	}
	return (target_stack_ready);
}

t_stack_status		target_stack_action_dec_v3_1(t_sort_result *sort_result,
																t_stack *stack)
{
	if (stack->top)
	{
		if (*(int *)sort_result->next_move.integer->content > stack->max ||
			*(int *)sort_result->next_move.integer->content < stack->min)
		{
			if (*(int *)stack->top->content != stack->max)
			{
				execute_action(sort_result, sort_result->next_move.target_stack_action);
				return (0);
			}
		}
		else
		{
			if (!(*(int *)stack->top->content < *(int *)sort_result->next_move.integer->content &&
				*(int *)stack->top->prev->content > *(int *)sort_result->next_move.integer->content))
			{
				execute_action(sort_result, sort_result->next_move.target_stack_action);
				return (0);
			}
		}
	}
	return (target_stack_ready);
}

static	void		check_rx_rx(t_move_cost *move_cost, t_next_move *next_move)
{
	size_t			moves;

	if (move_cost->source_rx != -1 && move_cost->target_dec_rx != -1)
	{
		moves = ft_max(move_cost->source_rx, move_cost->target_dec_rx);
		if (next_move->best_num_of_moves > moves)
		{
			next_move->best_num_of_moves = moves;
			next_move->integer = move_cost->integer;
			next_move->source_stack_action = ra;
			next_move->target_stack_action = rb;
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

	count_move_cost_v4_1(sort_result, source_stack_namme, sort_group, sort_mode);
	next_move = &sort_result->next_move;
	next_move->integer = NULL;
	next_move->source_stack_action = null;
	next_move->target_stack_action = null;
	next_move->best_num_of_moves = INT_MAX;
	c = -1;
	while (++c < (size_t)sort_result->move_cost_size)
	{
		check_rx_rx(&sort_result->move_cost[c], next_move);
	}
	if (next_move->integer)
		return (1);
	return (0);
}