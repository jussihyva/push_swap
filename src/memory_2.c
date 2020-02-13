/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 20:39:24 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/13 20:40:16 by jkauppi          ###   ########.fr       */
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
