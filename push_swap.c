/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 17:56:31 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/03 10:59:47 by jkauppi          ###   ########.fr       */
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

static t_list			*ft_lstcpy(t_list *elem)
{
	t_list		*new_elem;

	new_elem = ft_lstnew(elem->content, elem->content_size);
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

	c = -1;
	s = NULL;
	while (++c < size)
	{
		if (s)
		{
			tmp = ft_strjoin(s, array[c]);
			ft_strdel(&s);
		}
		else
			tmp = ft_strdup(array[c]);
		s = tmp;
		tmp = ft_strjoin(s, " ");
		ft_strdel(&s);
		s = tmp;
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

	init_sort_result(&sort_result);
	sort_result.action_list =
			(t_move_action *)ft_memalloc(sizeof(*sort_result.action_list) * 200000);
	sort_result.stack_array = ft_intdup(input->int_array, input->int_array_size);
	sort_result.stack_a.int_lst_size = input->int_array_size;
	sort_result.stack_a.int_lst = ft_lstmap(input->int_list, ft_lstcpy);
	elem = sort_result.stack_a.int_lst;
	while (elem->next)
		elem = elem->next;
	sort_result.stack_a.int_lst->prev = elem;
	elem->next = sort_result.stack_a.int_lst;
	sort_result.median = input->median;
	sort_result.stack_a.min = input->min;
	sort_result.stack_a.max = input->max;
	sort_result.average = input->average;
	sort_result.stack_a.top = sort_result.stack_a.int_lst->prev;
	sort_result.stack_b.top = NULL;
	step_prt_down(&sort_result);
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
		// sort_function.sort_function = (void *)bubble_sort_v1;
		// ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
						// sort_function.sort_function = (void *)random_sort_v1;
						// ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
		// sort_function.sort_function = (void *)bubble_sort_v2;
		// ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
		// sort_function.sort_function = (void *)bubble_sort_v3;
		// ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
		// sort_function.sort_function = (void *)insertion_sort_v1;
		// ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
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
		// sort_function.sort_function = (void *)less_moves_sort_v1_1;
		// ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
		// sort_function.sort_function = (void *)less_moves_sort_v1_2;
		// ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
		// sort_function.sort_function = (void *)less_moves_sort_v1_3;
		// ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
		// sort_function.sort_function = (void *)less_moves_sort_v1_4;
		// ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
		sort_function.sort_function = (void *)less_moves_sort_v2_1;
		ft_lstadd_e(sort_function_list, ft_lstnew(&sort_function, sizeof(sort_function)));
		result_array = (t_list **)ft_memalloc(sizeof(*result_array));
		*result_array = NULL;
		input = prepare_input_data(argc, argv);
		elem = *sort_function_list;
		while (elem)
		{
			stack_sort(input, elem, result_array, &max_actions);
			dprintf(2, "MAX: %5lu\n", max_actions);
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
