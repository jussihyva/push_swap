/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_next_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 19:14:56 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/13 19:17:55 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

size_t				ft_max(size_t nbr1, size_t nbr2)
{
	return (nbr1 > nbr2 ? nbr1 : nbr2);
}

size_t				ft_min(size_t nbr1, size_t nbr2)
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
	if (*(int *)sort_result->next_move.integer->content > stack->max ||
		*(int *)sort_result->next_move.integer->content < stack->min)
	{
		if (*(int *)stack->top->content != stack->min)
		{
			execute_action(sort_result,
								sort_result->next_move.target_stack_action);
			return (0);
		}
	}
	else
	{
		if (!(*(int *)stack->top->content >
						*(int *)sort_result->next_move.integer->content &&
			*(int *)stack->top->prev->content <
						*(int *)sort_result->next_move.integer->content))
		{
			execute_action(sort_result,
								sort_result->next_move.target_stack_action);
			return (0);
		}
	}
	return (target_stack_ready);
}

t_stack_status		target_stack_action_dec_v3_1(t_sort_result *sort_result,
																t_stack *stack)
{
	if (*(int *)sort_result->next_move.integer->content > stack->max ||
		*(int *)sort_result->next_move.integer->content < stack->min)
	{
		if (*(int *)stack->top->content != stack->max)
		{
			execute_action(sort_result,
								sort_result->next_move.target_stack_action);
			return (0);
		}
	}
	else
	{
		if (!(*(int *)stack->top->content <
						*(int *)sort_result->next_move.integer->content &&
			*(int *)stack->top->prev->content >
						*(int *)sort_result->next_move.integer->content))
		{
			execute_action(sort_result,
								sort_result->next_move.target_stack_action);
			return (0);
		}
	}
	return (target_stack_ready);
}
