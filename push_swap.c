/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 17:56:31 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/06 21:36:29 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// static void				del_stack(void *nbr, size_t size)
// {
// 	(void)size;
// 	free(nbr);
// 	nbr = NULL;
// 	return ;
// }

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
	int			dummy;

	dummy = 56;
	new_elem = ft_lstnew(&dummy, sizeof(dummy));
	new_elem->content = elem->content;
	return (new_elem);
}

static void				add_to_list(t_list **list, int *integer)
{
	t_list		*elem;

	elem = ft_lstnew(integer, sizeof(*integer));
	if (*list)
		ft_lstadd_e(list, elem);
	else
		*list = elem;
}

static void				string_to_array(char *s, t_input_data *input)
{
	int			*stack;
	size_t		i;
	char		**str_array;

	input->min = INT_MAX;
	input->max = INT_MIN;
	stack = NULL;
	if ((str_array = ft_strsplit(s, ' ')))
	{
		while (*(str_array + input->int_array_size))
			input->int_array_size++;
		i = input->int_array_size;
		stack = (int *)ft_memalloc(sizeof(*stack) * input->int_array_size);
		while (i--)
		{
			stack[i] = ft_atoi(str_array[input->int_array_size - i - 1]);
			add_to_list(&input->int_list, stack + i);
			input->min = input->min > stack[i] ? stack[i] : input->min;
			input->max = input->max < stack[i] ? stack[i] : input->max;
		}
		input->average = (input->max - input->min) / 2;
		ft_arraydel(str_array);
	}
	input->int_array = stack;
	return ;
}

static char				*merge_args(char **array, int size)
{
	char		*s;
	char		*tmp;
	int			c;

	c = 0;
	s = ft_strdup(array[c]);
	while (++c < size)
	{
		tmp = ft_strjoin(s, " ");
		ft_strdel(&s);
		s = ft_strjoin(tmp, array[c]);
		ft_strdel(&tmp);
	}
	return (s);
}

static t_input_data		*prepare_input_data(int argc, char **argv)
{
	t_input_data	*input;
	char			*s;
	int				*sorted_array;

	input = (t_input_data *)ft_memalloc(sizeof(*input));
	s = merge_args(argv + 1, argc - 1);
	input->int_array_size = 0;
	input->int_list = NULL;
	string_to_array(s, input);
	ft_strdel(&s);
	sorted_array = ft_intsort(input->int_array, input->int_array_size);
	input->int_list_sorted = ft_lstmap(input->int_list, ft_lstcpy);
	ft_lstsort(&input->int_list_sorted, cmp_elem);
	ft_lstiter(input->int_list_sorted, set_order);
	input->median = sorted_array[(input->int_array_size + 1) / 2 - 1];
	free(sorted_array);
	sorted_array = NULL;
	return (input);
}

static void				stack_sort(t_input_data *input,
		t_list *function_elem,
							t_list **result_array, size_t *max_actions)
{
	t_sort_result	sort_result;
	t_list			*elem;
	size_t			nbr;

	init_sort_result(&sort_result);
	sort_result.action_list =
			(t_move_action *)ft_memalloc(sizeof(*sort_result.action_list) *
																		200000);
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
//	free(sort_result.action_list);
//	ft_lstdel(&sort_result.stack_a, *del_stack);
//	free(sort_result.stack_array);
	sort_result.stack_array = NULL;
	return ;
}

int						main(int argc, char **argv)
{
	t_input_data		*input;
	t_list				**result_array;
	t_list				**sort_function_list;
	t_list				*elem;
	size_t				max_actions;
	t_sort_function		sort_function;

	if (argc > 1)
	{
		max_actions = 20000;
		sort_function_list = (t_list **)ft_memalloc(sizeof(*sort_function_list));
		sort_function.sort_function = (void *)bubble_sort_v1;
		ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
						// sort_function.sort_function = (void *)random_sort_v1;
						// ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
		// sort_function.sort_function = (void *)bubble_sort_v2;
		// ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
		// sort_function.sort_function = (void *)bubble_sort_v3;
		// ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
		// sort_function.sort_function = (void *)insertion_sort_v1;
		// ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
				//		sort_function.sort_function = (void *)random_sort_v2;
				//		ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
						// sort_function.sort_function = (void *)random_sort_v3;
						// ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
				//		sort_function.sort_function = (void *)bubble_sort_v2_1;
				//		ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
				//		sort_function.sort_function = (void *)bubble_sort_v2_2;
				//		ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
				//		sort_function.sort_function = (void *)bubble_sort_v2_3;
				//		ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
				//		sort_function.sort_function = (void *)bubble_sort_v2_4;
				//		ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
				//		sort_function.sort_function = (void *)bubble_sort_v2_5;
				//		ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
				//		sort_function.sort_function = (void *)bubble_sort_v3_1;
				//		ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
		// sort_function.sort_function = (void *)less_moves_sort_v1_1;
		// ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
		// sort_function.sort_function = (void *)less_moves_sort_v1_2;
		// ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
		// sort_function.sort_function = (void *)less_moves_sort_v1_3;
		// ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
		// sort_function.sort_function = (void *)less_moves_sort_v1_4;
		// ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
		// sort_function.sort_function = (void *)less_moves_sort_v2_1;
		// ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
		// sort_function.sort_function = (void *)less_moves_sort_v3_1;
		// ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
		// sort_function.sort_function = (void *)less_moves_sort_v3_2;
		// ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
		// sort_function.sort_function = (void *)less_moves_sort_v3_3;
		// ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
		// sort_function.sort_function = (void *)less_moves_sort_v3_4;
		// ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
		sort_function.sort_function = (void *)less_moves_sort_v4_1;
		ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
		sort_function.sort_function = (void *)less_moves_sort_v4_2;
		ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
		result_array = (t_list **)ft_memalloc(sizeof(*result_array));
		*result_array = NULL;
		input = prepare_input_data(argc, argv);
		elem = *sort_function_list;
		while (elem)
		{
			stack_sort(input, elem, result_array, &max_actions);
			ft_dprintf(2, "MAX: %5lu\n", max_actions);
			max_actions *= 10;
			elem = elem->next;
		}
		sleep(0);
		print_action_list(result_array);
		free(result_array);
		result_array = NULL;
	}
	return (0);
}
