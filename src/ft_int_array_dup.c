/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_array_dup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 17:12:30 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/13 17:12:47 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_move_action	*ft_int_array_dup(t_move_action *array, size_t size)
{
	t_move_action	*new_array;

	new_array = (t_move_action *)ft_memalloc(sizeof(*new_array) * size);
	while (size--)
		new_array[size] = array[size];
	return (new_array);
}
