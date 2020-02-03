/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_bubble_v3_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 16:49:53 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/03 08:08:39 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	check_order(t_list *top)
{
	t_list		*ptr;

	ptr = top;
	while (top != ptr->next && *(int *)ptr->content < *(int *)ptr->next->content)
	{
		ptr = ptr->next;
	}
	ptr = ptr->next;
	if (ptr == top)
		return (1);
	return (0);
}

static int		swap_stack_a(t_sort_result *sort_result)
{
	t_stack			*stack_a;

	stack_a = &sort_result->stack_a;
	if (*(int *)stack_a->top->content != sort_result->max &&
		*(int *)stack_a->top->content > *(int *)stack_a->top->next->content)
	{
		execute_action(sort_result, sa);
		return (1);
	}
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
	t_stack			*stack_a;

	stack_a = &sort_result->stack_a;
	if (*(int *)stack_a->top->content == sort_result->max)
	{
		if (check_order(stack_a->top->next))
		{
			execute_action(sort_result, rb);
		}
		else
		{
			execute_action(sort_result, rr);
			swap_stack_a(sort_result);
		}
	}
	else
	{
		execute_action(sort_result, rr);
		swap_stack_a(sort_result);
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
		execute_action(sort_result, ra);
	}
	execute_action(sort_result, ra);
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
			execute_action(sort_result, ra);
		}
		execute_action(sort_result, ra);
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
			execute_rr_action(sort_result);
	execute_rr_action(sort_result);
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
				execute_rr_action(sort_result);
		}
		execute_rr_action(sort_result);
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

void			bubble_sort_v3_1(t_sort_result *sort_result,
									t_list **result_array, size_t *max_actions)
{
	if (sort_result->min != sort_result->max)
	{
		split_one_stack_to_two_v3_1(sort_result);
		sort_b(sort_result);
		sort_a(sort_result);
		move_stack_b_to_a(sort_result);
	}
	save_result(sort_result, max_actions, result_array);
	return ;
}
