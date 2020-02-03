/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_less_moves_v2_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 11:03:25 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/03 12:09:32 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

static t_stack_status	stack_a_action(t_sort_result *sort_result,
														t_list *next_to_move)
{
	t_stack		stack_a;

	stack_a = sort_result->stack_a;
	if (stack_a.top)
	{
		if (*(int *)next_to_move->content > stack_a.max ||
			*(int *)next_to_move->content < stack_a.min)
		{
			if (*(int *)stack_a.top->content != stack_a.min)
			{
				execute_action(sort_result, ra);
				return (0);
			}
		}
		else
		{
			if (!(*(int *)stack_a.top->content > *(int *)next_to_move->content &&
				*(int *)stack_a.top->prev->content < *(int *)next_to_move->content))
			{
				execute_action(sort_result, ra);
				return (0);
			}
		}
	}
	return (stack_a_ready);
}

static t_stack_status	stack_b_action(t_sort_result *sort_result, t_list *next_to_move)
{
	if (sort_result->stack_b.top == next_to_move)
		return (stack_b_ready);
	execute_action(sort_result, rb);
	return (0);
}

void			less_moves_sort_v2_1(t_sort_result *sort_result,
									t_list **result_array, size_t *max_actions)
{
	t_list				*next_to_move;
	t_stack_status		move_status;

	move_to_stack_b_v1(sort_result, 50);
	while (sort_result->stack_b.top)
	{
		next_to_move = select_next_integer(sort_result);
		move_status = 0;
		while (move_status != (stack_a_ready | stack_b_ready) &&
				sort_result->total_num_of_actions < 80000)
		{
			move_status |= stack_b_action(sort_result, next_to_move);
			move_status |= stack_a_action(sort_result, next_to_move);
		}
		execute_action(sort_result, pa);
	}
	save_result(sort_result, max_actions, result_array);
	return ;
}
