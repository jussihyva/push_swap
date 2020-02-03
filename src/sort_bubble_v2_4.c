/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_bubble_v2_4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 10:21:23 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/03 08:37:34 by jkauppi          ###   ########.fr       */
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
	t_stack			*stack_b;

	stack_b = &sort_result->stack_b;
	if (*(int *)stack_b->top->next->content != sort_result->max_b &&
		*(int *)stack_b->top->content < *(int *)stack_b->top->next->content)
	{
		execute_action(sort_result, sb);
		return (1);
	}
	return (0);
}

static void		execute_rr_action(t_sort_result *sort_result)
{
	t_stack			*stack_b;

	stack_b = &sort_result->stack_b;
	if (*(int *)stack_b->top->content == sort_result->max_b)
	{
		if (check_order(stack_b->top))
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
	t_stack			*stack_a;

	stack_a = &sort_result->stack_a;
	while (*(int *)stack_a->top->content != sort_result->max)
	{
		if (*(int *)stack_a->top->content > *(int *)stack_a->top->next->content)
			execute_action(sort_result, sa);
		execute_rr_action(sort_result);
	}
	execute_rr_action(sort_result);
	is_sorted = 0;
	while (!is_sorted)
	{
		is_sorted = 1;
		while (*(int *)stack_a->top->content != sort_result->max)
		{
			if (*(int *)stack_a->top->content > *(int *)stack_a->top->next->content)
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
	t_stack			*stack_b;

	stack_b = &sort_result->stack_b;
	if (check_order(stack_b->top))
		return ;
	while (*(int *)stack_b->top->content != sort_result->min_b)
		if (!swap_stack_b(sort_result))
			execute_action(sort_result, rb);
	execute_action(sort_result, rb);
	is_sorted = 0;
	while (!is_sorted)
	{
		is_sorted = 1;
		while (*(int *)stack_b->top->content != sort_result->min_b)
		{
			if (*(int *)stack_b->top->content <
										*(int *)stack_b->top->next->content)
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
	while (sort_result->stack_b.top)
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
	save_result(sort_result, max_actions, result_array);
	return ;
}
