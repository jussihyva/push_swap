/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_two_stacks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 12:13:23 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/02 08:52:58 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void		move_all_to_stack_b_v1(t_sort_result *sort_result)
{
	while (sort_result->stack_a_size)
		execute_action(sort_result, pb);
	return ;
}

void		move_all_to_stack_b_v2(t_sort_result *sort_result)
{
	t_stack_ptr		*stack_ptr;

	stack_ptr = &sort_result->stack_ptr;
	while (sort_result->stack_a_size)
	{
		execute_action(sort_result, pb);
		if (stack_ptr->top_a &&
			*(int *)stack_ptr->top_b->content <= sort_result->median &&
			*(int *)stack_ptr->top_b->next->content > sort_result->median &&
			*(int *)stack_ptr->top_a->content > sort_result->median)
			execute_action(sort_result, rr);
		else if (*(int *)stack_ptr->top_b->content <= sort_result->median &&
			*(int *)stack_ptr->top_b->next->content > sort_result->median)
			execute_action(sort_result, rb);
	}
	return ;
}

void		move_all_to_stack_b_v3(t_sort_result *sort_result)
{
	t_stack_ptr		*stack_ptr;
	double			factor;

	factor = 1.5;
	stack_ptr = &sort_result->stack_ptr;
	while (sort_result->stack_a_size)
	{
		execute_action(sort_result, pb);
		if (stack_ptr->top_a &&
			*(int *)stack_ptr->top_b->content <= sort_result->median &&
			*(int *)stack_ptr->top_b->next->content > sort_result->median &&
			*(int *)stack_ptr->top_a->content > sort_result->median / 2 &&
			*(int *)stack_ptr->top_a->content < sort_result->median * factor)
			execute_action(sort_result, rr);
		else if (*(int *)stack_ptr->top_b->content <= sort_result->median &&
			*(int *)stack_ptr->top_b->next->content > sort_result->median)
			execute_action(sort_result, rb);
	}
	return ;
}

void		move_all_to_stack_b_v4(t_sort_result *sort_result)
{
	t_stack_ptr		*stack_ptr;
	double			factor;

	factor = 1.5;
	stack_ptr = &sort_result->stack_ptr;
	while (sort_result->stack_a_size)
	{
		execute_action(sort_result, pb);
		if (stack_ptr->top_a &&
			*(int *)stack_ptr->top_b->content <= sort_result->median &&
			*(int *)stack_ptr->top_b->next->content > sort_result->median &&
			*(int *)stack_ptr->top_a->content > sort_result->median / 2 &&
			*(int *)stack_ptr->top_a->content < sort_result->median * factor)
			execute_action(sort_result, rr);
		else if (*(int *)stack_ptr->top_b->content <= sort_result->median &&
			*(int *)stack_ptr->top_b->next->content > sort_result->median)
			execute_action(sort_result, rb);
		else if (stack_ptr->top_a &&
			*(int *)stack_ptr->top_b->content
									< *(int *)stack_ptr->top_b->next->content &&
			*(int *)stack_ptr->top_a->content
									> *(int *)stack_ptr->top_a->next->content)
			execute_action(sort_result, ss);
		// else if (*(int *)stack_ptr->top_b->content
		// 							< *(int *)stack_ptr->top_b->next->content)
		// 	execute_action(sort_result, sb);
	}
	return ;
}

void		split_one_stack_to_two_v1(t_sort_result *sort_result)
{
	t_stack_ptr		*stack_ptr;
	t_list			*start_ptr;

	stack_ptr = &sort_result->stack_ptr;
	start_ptr = NULL;
	while (stack_ptr->top_a != start_ptr)
	{
		if (*(int *)stack_ptr->top_a->content <= sort_result->median)
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

void		split_one_stack_to_two_v2(t_sort_result *sort_result)
{
	t_stack_ptr		*stack_ptr;
	t_list			*start_ptr;

	stack_ptr = &sort_result->stack_ptr;
	start_ptr = NULL;
	while (stack_ptr->top_a != start_ptr)
	{
		if (*(int *)stack_ptr->top_a->content <= sort_result->median)
		{
			execute_action(sort_result, pb);
			if (*(int *)stack_ptr->top_b->content <
										*(int *)stack_ptr->top_b->next->content)
				execute_action(sort_result, sb);
		}
		else
		{
			if (!start_ptr)
				start_ptr = stack_ptr->top_a;
			execute_action(sort_result, ra);
		}
	}
	return ;
}

void		split_one_stack_to_two_v3(t_sort_result *sort_result)
{
	t_stack_ptr		*stack_ptr;
	t_list			*start_ptr;

	stack_ptr = &sort_result->stack_ptr;
	start_ptr = NULL;
	while (stack_ptr->top_a != start_ptr)
	{
		if (*(int *)stack_ptr->top_a->content <= sort_result->median)
		{
			execute_action(sort_result, pb);
			if (*(int *)stack_ptr->top_b->content < sort_result->median / 2)
				execute_action(sort_result, rb);
			if (*(int *)stack_ptr->top_b->content <
										*(int *)stack_ptr->top_b->next->content)
				execute_action(sort_result, sb);
		}
		else
		{
			if (!start_ptr)
				start_ptr = stack_ptr->top_a;
			execute_action(sort_result, ra);
		}
	}
	return ;
}

void		split_one_stack_to_two_v4(t_sort_result *sort_result)
{
	t_stack_ptr		*stack_ptr;
	t_list			*start_ptr;
	double			factor;

	factor = 1.1;
	stack_ptr = &sort_result->stack_ptr;
	start_ptr = NULL;
	while (stack_ptr->top_a != start_ptr)
	{
		if (*(int *)stack_ptr->top_a->content <= (int)(sort_result->median * factor))
		{
			execute_action(sort_result, pb);
			if (*(int *)stack_ptr->top_b->content < sort_result->median / 2)
				execute_action(sort_result, rb);
			if (*(int *)stack_ptr->top_b->content <
										*(int *)stack_ptr->top_b->next->content)
				execute_action(sort_result, sb);
		}
		else
		{
			if (!start_ptr)
				start_ptr = stack_ptr->top_a;
			execute_action(sort_result, ra);
		}
	}
	return ;
}

void		split_one_stack_to_two_v5(t_sort_result *sort_result)
{
	t_stack_ptr		*stack_ptr;
	t_list			*start_ptr;
	double			factor;

	factor = 1.0;
	stack_ptr = &sort_result->stack_ptr;
	start_ptr = NULL;
	while (stack_ptr->top_a != start_ptr)
	{
		if (*(int *)stack_ptr->top_a->content <= (int)(sort_result->median * factor))
		{
			execute_action(sort_result, pb);
			if (*(int *)stack_ptr->top_b->content < (sort_result->median * factor) / 2)
				execute_action(sort_result, rb);
			if (*(int *)stack_ptr->top_b->content <
										*(int *)stack_ptr->top_b->next->content)
				execute_action(sort_result, sb);
		}
		else
		{
			if (!start_ptr)
				start_ptr = stack_ptr->top_a;
			execute_action(sort_result, ra);
		}
	}
	return ;
}

void		split_one_stack_to_two_v3_1(t_sort_result *sort_result)
{
	t_stack_ptr		*stack_ptr;
	t_list			*start_ptr;
	double			factor;

	factor = 1.0;
	stack_ptr = &sort_result->stack_ptr;
	start_ptr = NULL;
	while (stack_ptr->top_a != start_ptr)
	{
		if (*(int *)stack_ptr->top_a->content <= (int)(sort_result->median * factor))
		{
			execute_action(sort_result, pb);
			if (*(int *)stack_ptr->top_b->content < (sort_result->median * factor) / 2)
				execute_action(sort_result, rb);
			if (*(int *)stack_ptr->top_b->content <
										*(int *)stack_ptr->top_b->next->content)
				execute_action(sort_result, sb);
		}
		else
		{
			if (!start_ptr)
				start_ptr = stack_ptr->top_a;
			execute_action(sort_result, ra);
		}
	}
	return ;
}
