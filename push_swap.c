/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 17:56:31 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/12 13:09:40 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void			set_order(t_list *elem)
{
	static int		order_num;

	*(int *)elem->content = order_num;
	order_num++;
}

static void			ft_lstswap(t_list *elem1, t_list *elem2)
{
	elem2->prev = elem1->prev;
	if (elem1->prev)
		elem1->prev->next = elem2;
	elem1->next = elem2->next;
	elem1->prev = elem2;
	if (elem2->next)
		elem2->next->prev = elem1;
	elem2->next = elem1;
	return ;
}

static int				cmp_elem(t_list *elem1, t_list *elem2)
{
	if (*(int *)elem1->content < *(int *)elem2->content)
		return (1);
	else
		return (0);
}

static void				ft_lstsort(t_list **list, int cmp(t_list *elem1, t_list *elem2))
{
	t_list		*elem;
	int			is_sorted;

	is_sorted = 0;
	while (!is_sorted)
	{
		elem = *list;
		is_sorted = 1;
		while (elem)
		{
			if (elem->next && !cmp(elem, elem->next))
			{
				if (*list == elem)
					*list = elem->next;
				ft_lstswap(elem, elem->next);
				is_sorted = 0;
			}
			else
				elem = elem->next;
		}
	}
	return ;
}

static t_list			*ft_lstcpy(t_list *elem)
{
	t_list		*new_elem;

	new_elem = ft_lstnew(elem->content, elem->content_size);
	free(new_elem->content);
	new_elem->content = elem->content;
	return (new_elem);
}

static t_validation_result		prepare_input_data(t_input_data *input, int argc,
																	char **argv)
{
	int						*sorted_array;
	t_validation_result		result;

//	s = merge_args(argv + 1, argc - 1);
	input->int_array_size = 0;
	input->int_list = NULL;

	result = read_integer_values(input, argc, argv);
	if (result == error)
		return (result);
//	string_to_array(s, input);
//	ft_strdel(&s);
	sorted_array = ft_intsort(input->int_array, input->int_array_size);
	input->int_list_sorted = ft_lstmap(input->int_list, ft_lstcpy);
	ft_lstsort(&input->int_list_sorted, cmp_elem);
	ft_lstiter(input->int_list_sorted, set_order);
	input->median = sorted_array[(input->int_array_size + 1) / 2 - 1];
	free(sorted_array);
	sorted_array = NULL;
	return (result);
}

static void				stack_sort(t_input_data *input,
		t_list *function_elem,
							t_list **result_array, size_t *max_actions)
{
	t_sort_result	sort_result;
	t_list			*elem;
	size_t			nbr;

	init_sort_result(&sort_result);
	sort_result.stack_array =
							ft_intdup(input->int_array, input->int_array_size);
	sort_result.stack_a.int_lst_size = input->int_array_size;
	sort_result.stack_b.int_lst_size = 0;
	sort_result.stack_a.int_lst = ft_lstmap(input->int_list, ft_lstcpy);
	sort_result.stack_b.int_lst = NULL;
	sort_result.move_cost =
			(t_move_cost *)ft_memalloc(sizeof(*sort_result.move_cost) *
											sort_result.stack_a.int_lst_size);
	sort_result.move_cost_size = sort_result.stack_a.int_lst_size;
	elem = sort_result.stack_a.int_lst;
	while (elem->next)
	{
		nbr = *(int *)elem->content;
		sort_result.move_cost[nbr].integer = elem;
		sort_result.move_cost[nbr].integer = elem;
		elem = elem->next;
	}
	nbr = *(int *)elem->content;
	sort_result.move_cost[nbr].integer = elem;
	sort_result.move_cost[nbr].integer = elem;
	sort_result.stack_a.int_lst->prev = elem;
	elem->next = sort_result.stack_a.int_lst;
	sort_result.stack_a.median = input->median;
	sort_result.stack_a.average = input->average;
	sort_result.stack_a.top = sort_result.stack_a.int_lst;
	sort_result.stack_b.top = NULL;
	sort_result.sort_group = group1;
	min_max(&sort_result);
	count_move_cost_v3_3(&sort_result);
	((t_sort_function *)function_elem->content)->sort_function(&sort_result,
													result_array, max_actions);
	sort_result.stack_a.int_lst->prev->next = NULL;
	ft_lstdel(&sort_result.stack_a.int_lst, *del_stack);
	ft_lstdel(&sort_result.stack_b.int_lst, *del_stack);
	free(sort_result.stack_array);
	sort_result.stack_array = NULL;
	free(sort_result.action_list);
	sort_result.action_list = NULL;
	free(sort_result.move_cost);
	sort_result.move_cost = NULL;
	return ;
}

int						main(int argc, char **argv)
{
	t_input_data			*input;
	t_list					*result_array;
	t_list					**sort_function_list;
	t_list					*elem;
	size_t					max_actions;
	t_sort_function			sort_function;
	t_validation_result		result;
	int						valid_opt_flags;
	t_opt_attr				opt_attr;

	if (argc > 1)
	{
		valid_opt_flags = verbose;
		--argc;
		++argv;
		if (read_optional_attributes(valid_opt_flags, &argc, &argv, &opt_attr))
		{
			if (argc)
			{
				input = (t_input_data *)ft_memalloc(sizeof(*input));
				result = prepare_input_data(input, argc, argv);
			}
			else
				result = no_param;
		}
		else
			result = error;
		if (result != ok)
		{
			print_result(result);
			return (1);
		}
		max_actions = MAX_ACTIONS / 10;
		sort_function_list = (t_list **)ft_memalloc(sizeof(*sort_function_list));
		sort_function.num_of_actions = 0;
		sort_function.sort_function = (void *)bubble_sort_v1;
		ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
		sort_function.sort_function = (void *)random_sort_v1;
		ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
		sort_function.sort_function = (void *)bubble_sort_v2;
		ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
		sort_function.sort_function = (void *)bubble_sort_v3;
		ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
		sort_function.sort_function = (void *)insertion_sort_v1;
		ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
						// sort_function.sort_function = (void *)random_sort_v2;
						// ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
						// sort_function.sort_function = (void *)random_sort_v3;
						// ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
				// sort_function.sort_function = (void *)bubble_sort_v2_1;
				// ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
				// sort_function.sort_function = (void *)bubble_sort_v2_2;
				// ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
				// sort_function.sort_function = (void *)bubble_sort_v2_3;
				// ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
				// sort_function.sort_function = (void *)bubble_sort_v2_4;
				// ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
				// sort_function.sort_function = (void *)bubble_sort_v2_5;
				// ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
				// sort_function.sort_function = (void *)bubble_sort_v3_1;
				// ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
		// 	sort_function.sort_function = (void *)less_moves_sort_v1_1;
		// 	ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
		// 	sort_function.sort_function = (void *)less_moves_sort_v1_2;
		// 	ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
		// 	sort_function.sort_function = (void *)less_moves_sort_v1_3;
		// 	ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
		// 	sort_function.sort_function = (void *)less_moves_sort_v1_4;
		// 	ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
		// 	sort_function.sort_function = (void *)less_moves_sort_v2_1;
		// 	ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
		// 	sort_function.sort_function = (void *)less_moves_sort_v3_1;
		// 	ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
		// 	sort_function.sort_function = (void *)less_moves_sort_v3_2;
		// 	ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
		// 	sort_function.sort_function = (void *)less_moves_sort_v3_3;
		// 	ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
		// 	sort_function.sort_function = (void *)less_moves_sort_v3_4;
		// 	ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
		sort_function.sort_function = (void *)less_moves_sort_v4_1;
		ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
		sort_function.sort_function = (void *)less_moves_sort_v4_2;
		ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
		sort_function.sort_function = (void *)less_moves_sort_v4_3;
		ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
		sort_function.sort_function = (void *)less_moves_sort_v4_4;
		ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
		result_array = NULL;
		elem = *sort_function_list;
		while (elem)
		{
			stack_sort(input, elem, &result_array, &max_actions);
			((t_sort_function *)elem->content)->num_of_actions = max_actions;
			max_actions = ft_min(MAX_ACTIONS / 2, max_actions * 2);
			elem = elem->next;
		}
		elem = *sort_function_list;
		if (opt_attr.attr_flags & verbose)
		{
			ft_dprintf(2, "Detailed sort result:  ");
			while (elem)
			{
				max_actions = ((t_sort_function *)elem->content)->num_of_actions;
				ft_dprintf(2, "%7lu", max_actions);
				elem = elem->next;
			}
			ft_dprintf(2, "\n");
		}
		print_action_list(&result_array);
		ft_lstdel(sort_function_list, *del_sort_function_list);
		ft_lstdel(&input->int_list, *del_int_list);
		ft_lstdel(&input->int_list_sorted, *del_int_list_sorted);
		ft_lstdel(&result_array, *del_result_array);
		free(input->int_array);
		free(input);
	}
	return (0);
}
