/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_less_moves_v4_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 19:49:14 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/04 19:50:12 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static size_t	ft_max(size_t nbr1, size_t nbr2)
{
	return (nbr1 > nbr2 ? nbr1 : nbr2);
}

static t_list	*select_next_integer(t_sort_result *sort_result)
{
	t_list		*selected;
	t_list		*ptr;
	int			previous_int;
	size_t		c;

	selected = NULL;
	if (sort_result->stack_a.top)
	{
		ptr = sort_result->stack_b.top;
		previous_int = *(int *)sort_result->stack_a.top->content;
		c = 4;
		while (c--)
		{
			if (previous_int + 0 > *(int *)ptr->content)
			{
				if (selected)
				{
					if (*(int *)selected->content > *(int *)ptr->content &&
						previous_int < *(int *)ptr->content)
						selected = ptr;
				}
				else if (previous_int < *(int *)ptr->content)
					selected = ptr;
			}
			ptr = ptr->next;
		}
	}
	if (!selected)
	{
		if (sort_result->stack_b.top)
			selected = sort_result->stack_b.top;
		else
			selected = NULL;
	}
	return (selected);
}

static t_stack_status	target_stack_action_asc(t_sort_result *sort_result,
					t_stack *stack, t_list *next_to_move, t_move_action action)
{
	if (stack->top)
	{
		if (*(int *)next_to_move->content > stack->max ||
			*(int *)next_to_move->content < stack->min)
		{
			if (*(int *)stack->top->content != stack->min)
			{
				execute_action(sort_result, action);
				return (0);
			}
		}
		else
		{
			if (!(*(int *)stack->top->content > *(int *)next_to_move->content &&
				*(int *)stack->top->prev->content < *(int *)next_to_move->content))
			{
				execute_action(sort_result, action);
				return (0);
			}
		}
	}
	return (target_stack_ready);
}

static t_stack_status	target_stack_action_dec(t_sort_result *sort_result,
					t_stack *stack, t_list *next_to_move, t_move_action action)
{
	if (stack->top)
	{
		if (*(int *)next_to_move->content > stack->max ||
			*(int *)next_to_move->content < stack->min)
		{
			if (*(int *)stack->top->content != stack->max)
			{
				execute_action(sort_result, action);
				return (0);
			}
		}
		else
		{
			if (!(*(int *)stack->top->content < *(int *)next_to_move->content &&
				*(int *)stack->top->prev->content > *(int *)next_to_move->content))
			{
				execute_action(sort_result, action);
				return (0);
			}
		}
	}
	return (target_stack_ready);
}

static t_stack_status	source_stack_action(t_sort_result *sort_result,
					t_stack *stack, t_list *next_to_move, t_move_action action)
{
	if (stack->top == next_to_move)
		return (source_stack_ready);
	execute_action(sort_result, action);
	return (0);
}

static t_list	*get_best_move(t_sort_result *sort_result, size_t lst_size)
{
	size_t			best_num_of_moves;
	size_t			moves;
	t_list			*best_move;
	size_t			c;

	best_num_of_moves = INT_MAX;
	c = -1;
	best_move = sort_result->stack_a.top;
	while (++c < lst_size)
	{
		if (sort_result->stack_a.move_cost[c].source_forward != -1 &&
			sort_result->stack_a.move_cost[c].target_dec_forward != -1)
		{
			moves = ft_max(sort_result->stack_a.move_cost[c].source_forward,
			sort_result->stack_a.move_cost[c].target_dec_forward);
			if (best_num_of_moves > moves)
			{
				best_num_of_moves = moves;
				best_move = sort_result->stack_a.move_cost[c].elem;
				if (!best_move)
					ft_dprintf(2, "MOI! %lld\n", best_move->content);
			}
		}
	}
	return (best_move);
}

static void		move_and_sort_to_stack_b_v1(t_sort_result *sort_result,
																int percentage)
{
	t_stack				*stack_a;
	t_stack				*stack_b;
	size_t				target_size;
	t_list				*next_to_move;
	t_stack_status		move_status;
	size_t				lst_size;

	stack_b = &sort_result->stack_b;
	stack_a = &sort_result->stack_a;
	target_size = stack_a->int_lst_size * percentage / (double)100;
	while (stack_a->int_lst_size > target_size)
	{
		lst_size = sort_result->stack_a.int_lst_size + sort_result->stack_b.int_lst_size;
		count_move_cost_v2(sort_result);
		next_to_move = get_best_move(sort_result, lst_size);
		move_status = 0;
		while (move_status != (source_stack_ready | target_stack_ready) &&
				sort_result->total_num_of_actions < 80000)
		{
			move_status |= source_stack_action(sort_result, stack_a, next_to_move, ra);
			move_status |= target_stack_action_dec(sort_result, stack_b, next_to_move, rb);
		}
		execute_action(sort_result, pb);
	}
	return ;
}

void			less_moves_sort_v4_1(t_sort_result *sort_result,
									t_list **result_array, size_t *max_actions)
{
	t_list				*next_to_move;
	t_stack_status		move_status;

	move_and_sort_to_stack_b_v1(sort_result, 50);
	while (*(int *)sort_result->stack_b.top->content != sort_result->stack_b.max)
		execute_action(sort_result, rb);
//	move_max_to_top(sort_result, &sort_result->stack_b, sort_result->stack_b.max, rrb);
	move_all_to_stack_b_v1(sort_result);
	while (sort_result->stack_b.top)
	{
		next_to_move = select_next_integer(sort_result);
		move_status = 0;
		while (move_status != (source_stack_ready | target_stack_ready) &&
				sort_result->total_num_of_actions < 80000)
		{
			move_status |= source_stack_action(sort_result,
									&sort_result->stack_b, next_to_move, rb);
			move_status |= target_stack_action_asc(sort_result,
									&sort_result->stack_a, next_to_move, ra);
		}
		execute_action(sort_result, pa);
	}
	save_result(sort_result, max_actions, result_array);
	return ;
}
