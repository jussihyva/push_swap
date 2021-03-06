/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_common_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:35:59 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/13 20:48:54 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int					cmp_elem(t_list *elem1, t_list *elem2)
{
	if (*(int *)elem1->content < *(int *)elem2->content)
		return (1);
	else
		return (0);
}

t_list						*ft_lstcpy(t_list *elem)
{
	t_list		*new_elem;

	new_elem = ft_lstnew(elem->content, elem->content_size);
	free(new_elem->content);
	new_elem->content = elem->content;
	return (new_elem);
}

static void					set_order(t_list *elem)
{
	static int		order_num;

	*(int *)elem->content = order_num;
	order_num++;
}

static t_validation_result	prepare_input_data(t_input_data *input,
														int argc, char **argv)
{
	int						*sorted_array;
	t_validation_result		result;

	input->int_array_size = 0;
	input->int_list = NULL;
	result = read_integer_values(input, argc, argv);
	if (result != ok)
		return (result);
	sorted_array = ft_intsort(input->int_array, input->int_array_size);
	input->int_list_sorted = ft_lstmap(input->int_list, ft_lstcpy);
	ft_lstsort(&input->int_list_sorted, cmp_elem);
	ft_lstiter(input->int_list_sorted, set_order);
	input->median = sorted_array[(input->int_array_size + 1) / 2 - 1];
	free(sorted_array);
	sorted_array = NULL;
	return (result);
}

t_validation_result			read_input_data(t_input_data *input, int *argc,
											char ***argv, t_opt_attr *opt_attr)
{
	t_validation_result		result;
	int						valid_opt_flags;

	valid_opt_flags = verbose | leaks_pause;
	if (*argc == 1)
		return (no_param);
	--(*argc);
	++(*argv);
	if (read_optional_attributes(valid_opt_flags, argc, argv, opt_attr))
	{
		if (argc)
		{
			result = prepare_input_data(input, *argc, *argv);
		}
		else
			result = no_param;
	}
	else
		result = error;
	return (result);
}
