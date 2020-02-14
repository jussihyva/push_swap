/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 17:56:31 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/14 12:02:59 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void					stack_sort(t_input_data *input,
		t_list *function_elem,
							t_list **result_array, size_t *max_actions)
{
	t_sort_result	sort_result;

	init_sort_result(&sort_result);
	sort_result.stack_array =
							ft_intdup(input->int_array, input->int_array_size);
	sort_result.stack_a.int_lst_size = input->int_array_size;
	sort_result.stack_b.int_lst_size = 0;
	sort_result.stack_a.int_lst = ft_lstmap(input->int_list, ft_lstcpy);
	sort_result.stack_b.int_lst = NULL;
	init_move_cost(&sort_result);
	sort_result.stack_a.median = input->median;
	sort_result.stack_a.average = input->average;
	sort_result.stack_a.top = sort_result.stack_a.int_lst;
	sort_result.stack_b.top = NULL;
	sort_result.sort_group = group1;
	min_max(&sort_result);
	((t_sort_function *)function_elem->content)->sort_function(&sort_result,
													result_array, max_actions);
	sort_result.stack_a.int_lst->prev->next = NULL;
	release_sort_result(&sort_result);
	return ;
}

static void					execute_algorithms(t_list **sort_function_list,
									t_input_data *input, t_list **result_array,
									t_opt_attr opt_attr)
{
	t_list					*elem;
	size_t					max_actions;

	max_actions = MAX_ACTIONS / 10;
	elem = *sort_function_list;
	while (elem)
	{
		stack_sort(input, elem, result_array, &max_actions);
		((t_sort_function *)elem->content)->num_of_actions = max_actions;
		max_actions = ft_min(MAX_ACTIONS / 2, max_actions * 2);
		elem = elem->next;
	}
	elem = *sort_function_list;
	if (opt_attr.attr_flags & verbose)
	{
		ft_putstr_fd("Detailed sort result:  ", 2);
		while (elem)
		{
			max_actions = ((t_sort_function *)elem->content)->num_of_actions;
			ft_putstr_fd("       ", 2);
			ft_putstr_fd(ft_itoa(max_actions), 2);
			elem = elem->next;
		}
		ft_putstr_fd("\n", 2);
	}
	return ;
}

int							main(int argc, char **argv)
{
	t_input_data			*input;
	t_list					*result_array;
	t_list					**sort_function_list;
	t_validation_result		result;
	t_opt_attr				opt_attr;

	input = (t_input_data *)ft_memalloc(sizeof(*input));
	result = read_input_data(input, &argc, &argv, &opt_attr);
	if (result != ok)
		print_result(result);
	else
	{
		sort_function_list =
						(t_list **)ft_memalloc(sizeof(*sort_function_list));
		add_sort_algorithms(sort_function_list);
		result_array = NULL;
		execute_algorithms(sort_function_list, input, &result_array, opt_attr);
		print_action_list(&result_array);
		releasse_memory(sort_function_list, input, result_array);
	}
	if (opt_attr.attr_flags & leaks_pause)
		system("leaks push_swap");
	return (0);
}
