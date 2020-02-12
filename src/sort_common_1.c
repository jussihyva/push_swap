/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_common_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 14:08:42 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/12 09:24:42 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_move_action	*ft_int_array_dup(t_move_action *array, size_t size)
{
	t_move_action	*new_array;

	new_array = (t_move_action *)ft_memalloc(sizeof(*new_array) * size);
	while (size--)
		new_array[size] = array[size];
	return (new_array);
}

void			init_sort_result(t_sort_result *sort_result)
{
	sort_result->seq_action_counter = 0;
	sort_result->stack_a.int_lst_size = 0;
	sort_result->stack_b.int_lst_size = 0;
	sort_result->stack_a.int_lst = NULL;
	sort_result->stack_b.int_lst = NULL;
	sort_result->stack_a.top = NULL;
	sort_result->stack_b.top = NULL;
	sort_result->stack_a.average = 0;
	sort_result->action_list_size = 0;
	sort_result->action_list = NULL;
	sort_result->total_num_of_actions = 0;
	sort_result->action_list =
			(t_move_action *)ft_memalloc(sizeof(*sort_result->action_list) *
																MAX_ACTIONS);
	return ;
}

void			execute_action(t_sort_result *sort_result, t_move_action action)
{
	t_stack			*stack_b;
	t_stack			*stack_a;
	t_list			*tmp_ptr;

	stack_b = &sort_result->stack_b;
	stack_a = &sort_result->stack_a;
	sort_result->total_num_of_actions++;
	if (sort_result->total_num_of_actions < MAX_ACTIONS)
		add_action(sort_result, action);
	if (action == sa || action == sb || action == ss)
	{
		if ((action == sa || action == ss) && stack_a->int_lst_size)
		{
			stack_a->top->next->next->prev = stack_a->top; /* -1 */
			tmp_ptr = stack_a->top->next->next; /* 0 */
			stack_a->top->next->next = stack_a->top; /* 1 */
			stack_a->top = stack_a->top->next; /* 2 */
			stack_a->top->next->next = tmp_ptr; /* 0 */
			stack_a->top->prev->prev->next = stack_a->top; /* 3 */
			stack_a->top->prev = stack_a->top->next->prev; /* 5 */
			stack_a->top->next->prev = stack_a->top; /* 4 */
		}
		if ((action == sb || action == ss) && stack_b->int_lst_size)
		{
			stack_b->top->next->next->prev = stack_b->top; /* -1 */
			tmp_ptr = stack_b->top->next->next; /* 0 */
			stack_b->top->next->next = stack_b->top; /* 1 */
			stack_b->top = stack_b->top->next; /* 2 */
			stack_b->top->next->next = tmp_ptr; /* 0 */
			stack_b->top->prev->prev->next = stack_b->top; /* 3 */
			stack_b->top->prev = stack_b->top->next->prev; /* 5 */
			stack_b->top->next->prev = stack_b->top; /* 4 */
		}
	}
	else if (action == pb || action == pa)
	{
		move_to_stack(sort_result, action);
		min_max(sort_result);
	}
	else if (action == ra)
		step_prt_down(sort_result);
	else if (action == rb)
		step_prt_down_b(sort_result);
	else if (action == rr)
	{
		step_prt_down(sort_result);
		step_prt_down_b(sort_result);
	}
	else if (action == rra)
		step_prt_up(sort_result);
	else if (action == rrb)
		step_prt_up_b(sort_result);
	else if (action == rrr)
	{
		step_prt_up(sort_result);
		step_prt_up_b(sort_result);
	}
}
