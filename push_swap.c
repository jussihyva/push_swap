/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 17:56:31 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/20 18:50:44 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int				*ft_intcpy(int const *array, size_t size)
{
	int			*new_array;

	new_array = (int *)ft_memalloc(sizeof(*new_array) * size);
	while (size--)
		new_array[size] = array[size];
	return (new_array);
}

static int				*sort_int(int *array, size_t size)
{
	int			is_sorted;
	size_t		c;
	int			*sorted_array;

	sorted_array = ft_intcpy(array, size);
	is_sorted = 0;
	while (!is_sorted)
	{
		is_sorted = 1;
		c = -1;
		while (++c < size - 1)
		{
			if (sorted_array[c] > sorted_array[c + 1])
			{
				ft_int_swap(sorted_array + c, sorted_array + c + 1);
				is_sorted = 0;
			}
		}
	}
	return (sorted_array);
}

static int				save_min(int *ptr, int min, int **min_ptr)
{
	if (min > *ptr)
	{
		min = *ptr;
		*min_ptr = ptr;
	}
	return (min);
}

static int				save_max(int *ptr, int max, int **max_ptr)
{
	if (max > *ptr)
	{
		max = *ptr;
		*max_ptr = ptr;
	}
	return (max);
}

static void				string_to_array(char *s, t_input_data *input_data)
{
	int			*stack;
	size_t		i;
	char		**str_array;
	int			min;
	int			max;

	input_data->min_ptr = NULL;
	input_data->max_ptr = NULL;
	stack = NULL;
	min = INT_MAX;
	max = INT_MIN;
	if ((str_array = ft_strsplit(s, ' ')))
	{
		while (*(str_array + input_data->int_array_size))
			input_data->int_array_size++;
		i = input_data->int_array_size;
		stack = (int *)ft_memalloc(sizeof(*stack) * input_data->int_array_size);
		while (i--)
		{
			stack[i] = ft_atoi(str_array[input_data->int_array_size - i - 1]);
			min = save_min(stack + i, min, &input_data->min_ptr);
			max = save_max(stack + i, max, &input_data->max_ptr);
		}
		input_data->average = (max - min) / 2;
	}
	input_data->int_array = stack;
	return ;
}

static t_sort_result	*init_sort_result(void)
{
	t_sort_result	*sort_result;

	sort_result = (t_sort_result *)ft_memalloc(sizeof(*sort_result));
	sort_result->seq_action_counter = 0;
	sort_result->stack_size = 0;
	sort_result->average = 0;
	sort_result->action_list_size = 0;
	sort_result->action_list =
			(char **)ft_strnew(sizeof(*sort_result->action_list) * 100000);
	sort_result->last_action = ft_strdup("");
	return (sort_result);
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
	t_input_data	*input_data;
	char			*s;
	int				*sorted_array;

	input_data = (t_input_data *)ft_memalloc(sizeof(*input_data));
	s = merge_args(argv + 1, argc - 1);
	input_data->int_array_size = 0;
	string_to_array(s, input_data);
	sorted_array = sort_int(input_data->int_array, input_data->int_array_size);
	input_data->median =
				sorted_array[(input_data->int_array_size + 1) / 2 - 1];
	free(sorted_array);
	sorted_array = NULL;
	return (input_data);
}

static t_sort_result	*stack_sort(t_input_data *input_data,
							void *sort_function(t_sort_result *sort_result))
{
	t_sort_result	*sort_result;

	sort_result = init_sort_result();
	sort_result->stack = ft_intcpy(input_data->int_array,
													input_data->int_array_size);
	sort_result->stack_size = input_data->int_array_size;
	sort_result->median = input_data->median;
	sort_result->min_ptr = input_data->min_ptr;
	sort_result->max_ptr = input_data->max_ptr;
	sort_result->average = input_data->average;
	sort_result->stack_ptr.top = sort_result->stack + sort_result->stack_size;
	sort_result->stack_ptr.smallest_int = input_data->min_ptr;
	step_prt_down(sort_result);
	sort_function(sort_result);
	return (sort_result);
}

int						main(int argc, char **argv)
{
	t_input_data	*input_data;
	t_sort_result	*sort_result;
	size_t			i;
	t_list			**result_array;
	static void		*sort_function_array[6];

	if (argc > 1)
	{
//		sort_function_array[0] = bubble_sort_v1;
//		sort_function_array[1] = bubble_sort_v2;
//		sort_function_array[2] = bubble_sort_v3;
//		sort_function_array[0] = insertion_sort_v1;
		sort_function_array[0] = random_sort_v1;
		sort_function_array[1] = 0;
		result_array = (t_list **)ft_memalloc(sizeof(*result_array));
		input_data = prepare_input_data(argc, argv);
		i = -1;
		while (sort_function_array[++i])
		{
			sort_result = stack_sort(input_data, sort_function_array[i]);
			ft_lstadd_e(result_array,
								ft_lstnew(sort_result, sizeof(*sort_result)));
		}
		print_action_list(result_array);
		print_stack(sort_result->stack, sort_result->stack_size);
	}
	return (0);
}
