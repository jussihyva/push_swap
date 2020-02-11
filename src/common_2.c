/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 14:44:30 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/11 14:45:34 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "checker.h"

void					activate_linked_list_loop(t_list *int_lst)
{
	t_list					*elem;

	elem = int_lst;
	while (elem->next)
		elem = elem->next;
	int_lst->prev = elem;
	elem->next = int_lst;
	return ;
}
