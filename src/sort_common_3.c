/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_common_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 12:30:27 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/02 16:12:18 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	min_max(t_sort_result *sort_result)
{
	t_list		*start_ptr;
	t_list		*ptr;

	sort_result->min = INT_MAX;
	sort_result->max = INT_MIN;
	start_ptr = sort_result->stack_ptr.top_a;
	if (start_ptr)
	{
		ptr = start_ptr;
		sort_result->min = *(int *)ptr->content;
		sort_result->max = *(int *)ptr->content;
		ptr = ptr->next;
		while(ptr != start_ptr)
		{
			if (sort_result->min > *(int *)ptr->content)
				sort_result->min = *(int *)ptr->content;
			else if (sort_result->max < *(int *)ptr->content)
				sort_result->max = *(int *)ptr->content;
			ptr = ptr->next;
		}
	}
	return ;
}

int				*count_max_average(int *array, size_t size)
{
	int			*ptr;
	int			*start_ptr;
	double		average;
	long long	sum;
	size_t		group;

	group = size / 2;
	ptr = array;
	sum = 0;
	while (ptr < (array + group))
	{
		sum += *ptr;
		++ptr;
	}
	start_ptr = ptr - 1;
	average = sum / (double)group;
	while (ptr < (array + size))
	{
		sum -= *(ptr - group);
		sum += *ptr;
		if (average < sum / (double)group)
		{
			average = sum / (double)group;
			start_ptr = ptr;
		}
		++ptr;
	}
	ptr = array;
	while (ptr < (array + group - 1))
	{
		sum -= *(ptr + size - group);
		sum += *ptr;
		if (average < (int)(sum / (double)group))
		{	
			average = sum / (double)group;
			start_ptr = ptr;
		}
		++ptr;
	}
	return (start_ptr);
}

void			save_result(t_sort_result *sort_result, size_t *max_actions,
													t_list **result_array)
{
	size_t				c;
	t_sort_result		*valid_result;
	t_stack_ptr		*stack_ptr;

	stack_ptr = &sort_result->stack_ptr;
	min_max(sort_result);
	c = 0;
	if (sort_result->stack_ptr.top_a)
	{
		while (*(int *)sort_result->stack_ptr.top_a->content != sort_result->min)
		{
			execute_action(sort_result, rra);
			c++;
		}
	}
	valid_result = (t_sort_result *)ft_memalloc(sizeof(*valid_result));
	init_sort_result(valid_result);
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

void			move_to_stack(t_sort_result *sort_result, t_move_action action)
{
	t_stack_ptr		*stack_ptr;
	t_list			*tmp;

	stack_ptr = &sort_result->stack_ptr;
	if (action == pa)
	{
		sort_result->stack_b_size--;
		sort_result->stack_a_size++;
		stack_ptr->top_b->prev->next = stack_ptr->top_b->next;
		stack_ptr->top_b->next->prev = stack_ptr->top_b->prev;
		if (stack_ptr->top_a == NULL)
		{
			stack_ptr->top_a = stack_ptr->top_b;
			if (stack_ptr->top_b == stack_ptr->top_b->next)
				stack_ptr->top_b = NULL;
			else
				step_prt_down_b(sort_result);
			stack_ptr->top_a->prev = stack_ptr->top_a;
			stack_ptr->top_a->next = stack_ptr->top_a;
		}
		else
		{
			tmp = stack_ptr->top_b;
			if (stack_ptr->top_b == stack_ptr->top_b->next)
				stack_ptr->top_b = NULL;
			else
				step_prt_down_b(sort_result);
			stack_ptr->top_a->prev->next = tmp;
			tmp->prev = stack_ptr->top_a->prev;
			tmp->next = stack_ptr->top_a;
			stack_ptr->top_a->prev = tmp;
			stack_ptr->top_a = tmp;
		}
	}
	else if (action == pb)
	{
		sort_result->stack_a_size--;
		sort_result->stack_b_size++;
		stack_ptr->top_a->prev->next = stack_ptr->top_a->next;
		stack_ptr->top_a->next->prev = stack_ptr->top_a->prev;
		if (stack_ptr->top_b == NULL)
		{
			sort_result->min_b = INT_MAX;
			sort_result->max_b = INT_MIN;
			stack_ptr->top_b = stack_ptr->top_a;
			if (stack_ptr->top_a == stack_ptr->top_a->next)
				stack_ptr->top_a = NULL;
			else
				step_prt_down(sort_result);
			stack_ptr->top_b->prev = stack_ptr->top_b;
			stack_ptr->top_b->next = stack_ptr->top_b;
		}
		else
		{
			tmp = stack_ptr->top_a;
			if (stack_ptr->top_a == stack_ptr->top_a->next)
				stack_ptr->top_a = NULL;
			else
				step_prt_down(sort_result);
			stack_ptr->top_b->prev->next = tmp;
			tmp->prev = stack_ptr->top_b->prev;
			tmp->next = stack_ptr->top_b;
			stack_ptr->top_b->prev = tmp;
			stack_ptr->top_b = tmp;
		}
		if (sort_result->min_b > *(int *)stack_ptr->top_b->content)
			sort_result->min_b = *(int *)stack_ptr->top_b->content;
		if (sort_result->max_b < *(int *)stack_ptr->top_b->content)
			sort_result->max_b = *(int *)stack_ptr->top_b->content;
	}
}
