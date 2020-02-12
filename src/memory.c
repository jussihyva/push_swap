/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 15:02:28 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/12 16:49:33 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void				del_stack(void *elem, size_t size)
{
	(void)size;
	(void)elem;
	return ;
}

void				del_int_list(void *elem, size_t size)
{
	(void)size;
	if (elem)
	{
		free(elem);
		elem = NULL;
	}
	return ;
}

void				del_int_list_sorted(void *elem, size_t size)
{
	(void)size;
	(void)elem;
	return ;
}

void				del_sort_function_list(void *elem, size_t size)
{
	(void)size;
	if (elem)
	{
		free(elem);
		elem = NULL;
	}
	return ;
}

void				del_result_array(void *elem, size_t size)
{
	(void)size;
	if (elem)
	{
		if (((t_sort_result *)elem)->action_list)
			free(((t_sort_result *)elem)->action_list);
		if (((t_sort_result *)elem)->move_cost)
			free(((t_sort_result *)elem)->move_cost);
		free(elem);
		elem = NULL;
	}
	return ;
}

void				releasse_memory(t_list **sort_function_list,
									t_input_data *input, t_list *result_array)
{
	ft_lstdel(sort_function_list, *del_sort_function_list);
	ft_lstdel(&input->int_list, *del_int_list);
	ft_lstdel(&input->int_list_sorted, *del_int_list_sorted);
	ft_lstdel(&result_array, *del_result_array);
	free(input->int_array);
	free(input);
	return ;
}

void				release_sort_result(t_sort_result *sort_result)
{
	ft_lstdel(&sort_result->stack_a.int_lst, *del_stack);
	ft_lstdel(&sort_result->stack_b.int_lst, *del_stack);
	free(sort_result->stack_array);
	sort_result->stack_array = NULL;
	free(sort_result->action_list);
	sort_result->action_list = NULL;
	free(sort_result->move_cost);
	sort_result->move_cost = NULL;
	return ;
}