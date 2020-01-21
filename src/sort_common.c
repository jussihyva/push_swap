/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_common.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 14:08:42 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/21 15:22:55 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int				*ft_intcpy(int const *array, size_t size)
{
	int			*new_array;

	new_array = (int *)ft_memalloc(sizeof(*new_array) * size);
	while (size--)
		new_array[size] = array[size];
	return (new_array);
}

char			**ft_str_array_dup(char **array, size_t size)
{
	char		**new_array;

	new_array = (char **)ft_memalloc(sizeof(*new_array) * size);
	while (size--)
		new_array[size] = ft_strdup(array[size]);
	return (new_array);
}

t_sort_result	*init_sort_result(void)
{
	t_sort_result	*sort_result;

	sort_result = (t_sort_result *)ft_memalloc(sizeof(*sort_result));
	sort_result->seq_action_counter = 0;
	sort_result->stack_size = 0;
	sort_result->average = 0;
	sort_result->action_list_size = 0;
	sort_result->action_list = NULL;
	sort_result->last_action = NULL;
	return (sort_result);
}
