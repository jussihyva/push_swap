/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_common_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 14:08:42 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/22 11:35:07 by jkauppi          ###   ########.fr       */
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

void			execute_action(t_sort_result *sort_result, char *action_string)
{
	t_stack_ptr		*stack_ptr;

	stack_ptr = &sort_result->stack_ptr;
	add_action(sort_result, action_string);
	if (ft_strequ(action_string, "sa"))
		ft_intswap(stack_ptr->top, stack_ptr->next);
	else if (ft_strequ(action_string, "ra"))
		step_prt_down(sort_result);
	else if (ft_strequ(action_string, "rra"))
		step_prt_up(sort_result);
}
