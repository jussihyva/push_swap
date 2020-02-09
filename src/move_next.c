/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_next.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 18:49:15 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/09 12:43:37 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

size_t	ft_max(size_t nbr1, size_t nbr2)
{
	return (nbr1 > nbr2 ? nbr1 : nbr2);
}

size_t	ft_min(size_t nbr1, size_t nbr2)
{
	return (nbr1 < nbr2 ? nbr1 : nbr2);
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

static	void		check_rx_rx(t_move_cost *move_cost, t_next_move *next_move,
												t_stack_name source_stack_namme)
{
	size_t			moves;

	if ((source_stack_namme == a && move_cost->source_rx != -1 && move_cost->target_dec_rx != -1) ||
		(source_stack_namme == b && move_cost->source_rx != -1 && move_cost->target_asc_rx != -1))
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
			{
				next_move->source_stack_action = ra;
				next_move->target_stack_action = rb;
			}
			else
			{
				next_move->source_stack_action = rb;
				next_move->target_stack_action = ra;
			}
		}
	}
	return ;
}

static	void		check_rrx_rrx(t_move_cost *move_cost, t_next_move *next_move,
												t_stack_name source_stack_namme)
{
	size_t			moves;

	if ((source_stack_namme == a && move_cost->source_rrx != -1 && move_cost->target_dec_rrx != -1) ||
		(source_stack_namme == b && move_cost->source_rrx != -1 && move_cost->target_asc_rrx != -1))
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
			{
				next_move->source_stack_action = rra;
				next_move->target_stack_action = rrb;
			}
			else
			{
				next_move->source_stack_action = rrb;
				next_move->target_stack_action = rra;
			}
		}
	}
	return ;
}

static	void		check_rx_rrx(t_move_cost *move_cost, t_next_move *next_move,
												t_stack_name source_stack_namme)
{
	size_t			moves;

	if ((source_stack_namme == a && move_cost->source_rx != -1 && move_cost->target_dec_rrx != -1) ||
		(source_stack_namme == b && move_cost->source_rx != -1 && move_cost->target_asc_rrx != -1))
	{
		if (source_stack_namme == a)
			moves = move_cost->source_rx + move_cost->target_dec_rrx;
		else
			moves = move_cost->source_rx + move_cost->target_asc_rrx;
		if (next_move->best_num_of_moves > moves)
		{
			next_move->best_num_of_moves = moves;
			next_move->integer = move_cost->integer;
			if (source_stack_namme == a)
			{
				next_move->source_stack_action = ra;
				next_move->target_stack_action = rrb;
			}
			else
			{
				next_move->source_stack_action = rb;
				next_move->target_stack_action = rra;
			}
		}
	}
	return ;
}

static	void		check_rrx_rx(t_move_cost *move_cost, t_next_move *next_move,
												t_stack_name source_stack_namme)
{
	size_t			moves;

	if ((source_stack_namme == a && move_cost->source_rrx != -1 && move_cost->target_dec_rx != -1) ||
		(source_stack_namme == b && move_cost->source_rrx != -1 && move_cost->target_asc_rx != -1))
	{
		if (source_stack_namme == a)
			moves = move_cost->source_rrx + move_cost->target_dec_rx;
		else
			moves = move_cost->source_rrx + move_cost->target_asc_rx;
		if (next_move->best_num_of_moves > moves)
		{
			next_move->best_num_of_moves = moves;
			next_move->integer = move_cost->integer;
			if (source_stack_namme == a)
			{
				next_move->source_stack_action = rra;
				next_move->target_stack_action = rb;
			}
			else
			{
				next_move->source_stack_action = rrb;
				next_move->target_stack_action = ra;
			}
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
	if (source_stack_namme == b || sort_result->stack_a.int_lst_size > 2)
	{
		c = -1;
		while (++c < (size_t)sort_result->move_cost_size)
		{
			check_rx_rx(&sort_result->move_cost[c], next_move, source_stack_namme);
			check_rx_rrx(&sort_result->move_cost[c], next_move, source_stack_namme);
			check_rrx_rrx(&sort_result->move_cost[c], next_move, source_stack_namme);
			check_rrx_rx(&sort_result->move_cost[c], next_move, source_stack_namme);
		}
	}
	if (next_move->integer)
		return (1);
	return (0);
}