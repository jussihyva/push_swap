/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 17:56:31 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/26 15:44:43 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
	string_to_array(s, input);
	ft_strdel(&s);
	sorted_array = ft_intsort(input->int_array, input->int_array_size);
	input->median = sorted_array[(input->int_array_size + 1) / 2 - 1];
	free(sorted_array);
	sorted_array = NULL;
	return (input);
}

static void				stack_sort(t_input_data *input,
		void *sort_function(t_sort_result *sort_result, t_list **result_array,
							size_t *max_actions),
							t_list **result_array, size_t *max_actions)
{
	t_sort_result	sort_result;
	size_t			i;

	init_sort_result(&sort_result);
	sort_result.action_list =
			(t_move_action *)ft_memalloc(sizeof(*sort_result.action_list) * 200000);
	sort_result.stack = ft_intdup(input->int_array, input->int_array_size);
	sort_result.stack_size = input->int_array_size;
	sort_result.median = input->median;
	sort_result.min = input->min;
	sort_result.max = input->max;
	sort_result.average = input->average;
	sort_result.stack_ptr.top = sort_result.stack + sort_result.stack_size;
	i = -1;
	while (++i < sort_result.stack_size)
	{
		if (*(sort_result.stack + i) == input->min)
		{
			sort_result.stack_ptr.smallest_int = sort_result.stack + i;
			break ;
		}
	}
	step_prt_down(&sort_result);
	sort_function(&sort_result, result_array, max_actions);
	return ;
}

int						main(int argc, char **argv)
{
	t_input_data	*input;
	size_t			i;
	t_list			**result_array;
	static void		*sort_function_array[7];
	size_t			max_actions;

	if (argc > 1)
	{
		max_actions = -1;
		sort_function_array[0] = bubble_sort_v1;
		sort_function_array[1] = random_sort_v1;
		sort_function_array[2] = bubble_sort_v2;
		sort_function_array[3] = bubble_sort_v3;
		sort_function_array[4] = insertion_sort_v1;
		sort_function_array[5] = random_sort_v2;
		sort_function_array[6] = 0;
		result_array = (t_list **)ft_memalloc(sizeof(*result_array));
		*result_array = NULL;
		input = prepare_input_data(argc, argv);
		i = -1;
		while (sort_function_array[++i])
		{
			stack_sort(input, sort_function_array[i],
													result_array, &max_actions);
//			ft_printf("MAX: %5d\n", max_actions);
			max_actions *= 10;
		}
		print_action_list(result_array);
	}
	return (0);
}
