/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_common_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 12:30:27 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/13 14:37:00 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void			min_max_stack(t_stack *stack)
{
	t_list		*start_ptr;
	t_list		*ptr;

	stack->min = INT_MAX;
	stack->max = INT_MIN;
	start_ptr = stack->top;
	if (start_ptr)
	{
		ptr = start_ptr;
		stack->min = *(int *)ptr->content;
		stack->max = *(int *)ptr->content;
		ptr = ptr->next;
		while (ptr != start_ptr)
		{
			if (stack->min > *(int *)ptr->content)
				stack->min = *(int *)ptr->content;
			else if (stack->max < *(int *)ptr->content)
				stack->max = *(int *)ptr->content;
			ptr = ptr->next;
		}
	}
	return ;
}

void			min_max(t_sort_result *sort_result)
{
	min_max_stack(&sort_result->stack_a);
	min_max_stack(&sort_result->stack_b);
	return ;
}

size_t			roll_min_to_top(t_sort_result *sort_result, t_stack *stack,
												int min, t_move_action action)
{
	size_t		c;
	t_list		*ptr;

	c = 0;
	ptr = stack->top;
	if (stack->top)
	{
		while (*(int *)stack->top->content != min)
		{
			execute_action(sort_result, action);
			c++;
		}
	}
	return (c);
}

void			roll_max_to_top(t_sort_result *sort_result, t_stack *stack,
												int max, t_move_action action)
{
	t_list		*ptr;

	ptr = stack->top;
	if (stack->top)
	{
		while (*(int *)stack->top->content != max)
			execute_action(sort_result, action);
	}
	return ;
}

void			save_result(t_sort_result *sort_result, size_t *max_actions,
													t_list **result_array)
{
	size_t				c;
	t_sort_result		*valid_result;

	min_max(sort_result);
	c = 0;
	if (sort_result->stack_a.top)
		c = roll_min_to_top(sort_result, &sort_result->stack_a,
												sort_result->stack_a.min, rra);
	valid_result = (t_sort_result *)ft_memalloc(sizeof(*valid_result));
	init_sort_result(valid_result);
	free(valid_result->action_list);
	valid_result->action_list = NULL;
	valid_result->action_list = ft_int_array_dup(sort_result->action_list,
											sort_result->action_list_size);
	valid_result->action_list_size = sort_result->action_list_size;
	ft_lstadd_e(result_array, ft_lstnew(valid_result, sizeof(*valid_result)));
	if (*max_actions > valid_result->action_list_size)
		*max_actions = valid_result->action_list_size;
	free(valid_result);
	valid_result = NULL;
	while (c--)
		execute_action(sort_result, ra);
	return ;
}
