/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_two_stacks_v1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 12:13:23 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/28 12:26:48 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void		split_two_stacks_v1(t_sort_result *sort_result)
{
	t_stack_ptr		*stack_ptr;
	t_list			*start_ptr;
	t_list			*ptr;

	stack_ptr = &sort_result->stack_ptr;
	start_ptr = NULL;
	ptr = start_ptr->next;
	while (stack_ptr->top_a != start_ptr)
	{
		if (*(int *)stack_ptr->top_a->content < sort_result->median)
			execute_action(sort_result, pb);
		else
		{
			if (!start_ptr)
				start_ptr = stack_ptr->top_a;
			execute_action(sort_result, ra);
		}
	}
	return ;
}