/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_common_5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 14:34:23 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/13 17:38:49 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void		first_integer(t_stack *source_stack, t_stack *target_stack)
{
	target_stack->top = source_stack->top;
	if (source_stack->top == source_stack->top->next)
		source_stack->top = NULL;
	else
		source_stack->top = source_stack->top->next;
	target_stack->top->prev = target_stack->top;
	target_stack->top->next = target_stack->top;
	return ;
}

static void		next_integer(t_stack *source_stack, t_stack *target_stack)
{
	t_list			*tmp;

	tmp = source_stack->top;
	if (source_stack->top == source_stack->top->next)
		source_stack->top = NULL;
	else
		source_stack->top = source_stack->top->next;
	target_stack->top->prev->next = tmp;
	tmp->prev = target_stack->top->prev;
	tmp->next = target_stack->top;
	target_stack->top->prev = tmp;
	target_stack->top = tmp;
	return ;
}

void			move_to_stack(t_sort_result *sort_result, t_move_action action)
{
	t_stack			*source_stack;
	t_stack			*target_stack;

	target_stack = &sort_result->stack_b;
	source_stack = &sort_result->stack_a;
	if (action == pa && sort_result->stack_b.int_lst_size)
	{
		source_stack = &sort_result->stack_b;
		target_stack = &sort_result->stack_a;
	}
	else if (action == pb && sort_result->stack_a.int_lst_size)
	{
		target_stack = &sort_result->stack_b;
		source_stack = &sort_result->stack_a;
	}
	source_stack->int_lst_size--;
	target_stack->int_lst_size++;
	source_stack->top->prev->next = source_stack->top->next;
	source_stack->top->next->prev = source_stack->top->prev;
	if (target_stack->top == NULL)
		first_integer(source_stack, target_stack);
	else
		next_integer(source_stack, target_stack);
}

void			init_move_cost(t_sort_result *sort_result)
{
	t_list			*elem;
	size_t			nbr;

	sort_result->move_cost =
			(t_move_cost *)ft_memalloc(sizeof(*sort_result->move_cost) *
											sort_result->stack_a.int_lst_size);
	sort_result->move_cost_size = sort_result->stack_a.int_lst_size;
	elem = sort_result->stack_a.int_lst;
	while (elem->next)
	{
		nbr = *(int *)elem->content;
		sort_result->move_cost[nbr].integer = elem;
		sort_result->move_cost[nbr].integer = elem;
		elem = elem->next;
	}
	nbr = *(int *)elem->content;
	sort_result->move_cost[nbr].integer = elem;
	sort_result->move_cost[nbr].integer = elem;
	sort_result->stack_a.int_lst->prev = elem;
	elem->next = sort_result->stack_a.int_lst;
	return ;
}
