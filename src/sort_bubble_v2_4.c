/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_bubble_v2_4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 10:21:23 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/02 16:11:28 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	check_order(t_list *top)
{
	t_list		*ptr;

	ptr = top;
	while (top != ptr->next && *(int *)ptr->content > *(int *)ptr->next->content)
	{
		ptr = ptr->next;
	}
	ptr = ptr->next;
	if (ptr == top)
		return (1);
	return (0);
}

static int		swap_stack_b(t_sort_result *sort_result)
{
	t_stack_ptr		*stack_ptr;

	stack_ptr = &sort_result->stack_ptr;
	if (*(int *)stack_ptr->top_b->next->content != sort_result->max_b &&
		*(int *)stack_ptr->top_b->content < *(int *)stack_ptr->top_b->next->content)
	{
		execute_action(sort_result, sb);
		return (1);
	}
	return (0);
}

static void		execute_rr_action(t_sort_result *sort_result)
{
	t_stack_ptr		*stack_ptr;

	stack_ptr = &sort_result->stack_ptr;
	if (*(int *)stack_ptr->top_b->content == sort_result->max_b)
	{
		if (check_order(stack_ptr->top_b))
		{
			execute_action(sort_result, ra);
		}
		else
		{
			execute_action(sort_result, rr);
			swap_stack_b(sort_result);
		}
	}
	else
	{
		execute_action(sort_result, rr);
		swap_stack_b(sort_result);
	}
	return ;
}

static void		sort_a(t_sort_result *sort_result)
{
	int				is_sorted;
	t_stack_ptr		*stack_ptr;

	stack_ptr = &sort_result->stack_ptr;
	while (*(int *)stack_ptr->top_a->content != sort_result->max)
	{
		if (*(int *)stack_ptr->top_a->content > *(int *)stack_ptr->next_a->content)
			execute_action(sort_result, sa);
		execute_rr_action(sort_result);
	}
	execute_rr_action(sort_result);
	is_sorted = 0;
	while (!is_sorted)
	{
		is_sorted = 1;
		while (*(int *)stack_ptr->top_a->content != sort_result->max)
		{
			if (*(int *)stack_ptr->top_a->content > *(int *)stack_ptr->top_a->next->content)
			{
				execute_action(sort_result, sa);
				is_sorted = 0;
			}
			execute_rr_action(sort_result);
		}
		execute_rr_action(sort_result);
	}
	return ;
}

static void		sort_b(t_sort_result *sort_result)
{
	int				is_sorted;
	t_stack_ptr		*stack_ptr;

	stack_ptr = &sort_result->stack_ptr;
	if (check_order(stack_ptr->top_b))
		return ;
	while (*(int *)stack_ptr->top_b->content != sort_result->min_b)
		if (!swap_stack_b(sort_result))
			execute_action(sort_result, rb);
	execute_action(sort_result, rb);
	is_sorted = 0;
	while (!is_sorted)
	{
		is_sorted = 1;
		while (*(int *)stack_ptr->top_b->content != sort_result->min_b)
		{
			if (*(int *)stack_ptr->top_b->content <
										*(int *)stack_ptr->top_b->next->content)
			{
				execute_action(sort_result, sb);
				is_sorted = 0;
			}
			else
				execute_action(sort_result, rb);
		}
		execute_action(sort_result, rb);
	}
	return ;
}

static void		move_stack_b_to_a(t_sort_result *sort_result)
{
	t_stack_ptr		*stack_ptr;

	stack_ptr = &sort_result->stack_ptr;
	while (sort_result->stack_ptr.top_b)
		execute_action(sort_result, pa);
}

void			bubble_sort_v2_4(t_sort_result *sort_result,
									t_list **result_array, size_t *max_actions)
{
	if (sort_result->min != sort_result->max)
	{
		split_one_stack_to_two_v4(sort_result);
		sort_a(sort_result);
		sort_b(sort_result);
		move_stack_b_to_a(sort_result);
	}
//	*max_actions = (*max_actions > sort_result->action_list_size) ?
//				sort_result->action_list_size : *max_actions;
	save_result(sort_result, max_actions, result_array);
	return ;
}
