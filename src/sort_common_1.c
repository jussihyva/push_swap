/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_common_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 14:08:42 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/27 08:02:40 by jkauppi          ###   ########.fr       */
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
	sort_result->stack_size = 0;
	sort_result->average = 0;
	sort_result->action_list_size = 0;
	sort_result->action_list = NULL;
	sort_result->last_action = null;
	sort_result->total_num_of_actions = 0;
	return ;
}

void			execute_action(t_sort_result *sort_result, t_move_action action)
{
	t_stack_ptr		*stack_ptr;

	stack_ptr = &sort_result->stack_ptr;
	sort_result->total_num_of_actions++;
	add_action(sort_result, action);
	if (action == sa)
	{
		ft_intswap(stack_ptr->top, stack_ptr->next);
		stack_ptr->next_a->prev = stack_ptr->top_a->prev;
		stack_ptr->top_a->next = stack_ptr->next_a->next;
		stack_ptr->top_a->prev = stack_ptr->next_a;
		stack_ptr->next_a->next = stack_ptr->top_a;
		stack_ptr->top_a = stack_ptr->next_a;
		stack_ptr->next_a = stack_ptr->top_a->next;
	}
	else if (action == ra)
		step_prt_down(sort_result);
	else if (action == rra)
		step_prt_up(sort_result);
}
