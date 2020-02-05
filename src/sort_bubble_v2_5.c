/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_bubble_v2_5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 13:57:37 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/05 18:06:52 by jkauppi          ###   ########.fr       */
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
	if (*(int *)stack_b->top->next->content != sort_result->stack_b.max &&
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
	if (*(int *)stack_b->top->content == sort_result->stack_b.max)
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

static int		loop_down_if_swap(t_sort_result *sort_result,
													t_stack *stack_a)
{
	int				is_sorted;
	size_t			loop_cnt;
	double			factor;

	factor = 1.5;
	is_sorted = 1;
	loop_cnt = 0;
	while (*(int *)stack_a->top->content != sort_result->stack_a.max)
	{
		loop_cnt++;
		if (*(int *)stack_a->top->content >
										*(int *)stack_a->top->next->content)
		{
			execute_action(sort_result, sa);
			is_sorted = 0;
			execute_rr_action(sort_result);
		}
		else
		{
			if (!is_sorted && *(int *)stack_a->top->prev->content <=
												(int)(sort_result->stack_a.median * factor))
				break ;
			execute_rr_action(sort_result);
		}
	}
	if (loop_cnt != sort_result->stack_a.int_lst_size - 1)
		is_sorted = 0;
	return (is_sorted);
}

static int		loop_up_if_swap(t_sort_result *sort_result,
													t_stack *stack_a)
{
	int				is_sorted;

	is_sorted = 0;
	while (*(int *)stack_a->top->content != sort_result->stack_a.max)
	{
		if (*(int *)stack_a->top->next->content <
											*(int *)stack_a->top->content)
		{
			execute_action(sort_result, sa);
			execute_action(sort_result, rra);
		}
		else
			execute_action(sort_result, rra);
	}
	execute_action(sort_result, ra);
	return (is_sorted);
}

static int		sort_a(t_sort_result *sort_result)
{
	int				is_sorted;
	t_stack			*stack_a;

	stack_a = &sort_result->stack_a;
	is_sorted = loop_down_if_swap(sort_result, stack_a);
	if (!is_sorted)
		is_sorted = loop_up_if_swap(sort_result, stack_a);
	return (is_sorted);
}

static void		sort_b(t_sort_result *sort_result)
{
	int				is_sorted;
	t_stack			*stack_b;

	stack_b = &sort_result->stack_b;
	if (check_order(stack_b->top))
		return ;
	while (*(int *)stack_b->top->content != sort_result->stack_b.min)
		if (!swap_stack_b(sort_result))
			execute_action(sort_result, rb);
	execute_action(sort_result, rb);
	is_sorted = 0;
	while (!is_sorted)
	{
		is_sorted = 1;
		while (*(int *)stack_b->top->content != sort_result->stack_b.min)
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

void			bubble_sort_v2_5(t_sort_result *sort_result,
									t_list **result_array, size_t *max_actions)
{
	int				is_sorted;
	t_stack			*stack_a;

	stack_a = &sort_result->stack_a;
	if (sort_result->stack_a.min != sort_result->stack_a.max)
	{
		split_one_stack_to_two_v5(sort_result);
		is_sorted = 0;
		while (!is_sorted && sort_result->total_num_of_actions < MAX_ACTIONS)
			is_sorted = sort_a(sort_result);
		while (*(int *)stack_a->top->prev->content != sort_result->stack_a.max)
			execute_action(sort_result, ra);
		sort_b(sort_result);
		move_stack_b_to_a(sort_result);
	}
	save_result(sort_result, max_actions, result_array);
	return ;
}
