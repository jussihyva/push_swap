/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_common.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 14:43:05 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/11 16:59:09 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static int				str_to_rx_move_action(char *str, t_move_action *action)
{
	int						result;

	result = 1;
	if (ft_strequ(str, "ra"))
		*action = ra;
	else if (ft_strequ(str, "rb"))
		*action = rb;
	else if (ft_strequ(str, "rr"))
		*action = rr;
	else
		result = 0;
	return (result);
}

t_validation_result		str_to_move_action(char *str, t_move_action *action)
{
	t_validation_result		result;

	result = ok;
	if (str_to_rx_move_action(str, action))
		;
	else if (ft_strequ(str, "rra"))
		*action = rra;
	else if (ft_strequ(str, "rrb"))
		*action = rrb;
	else if (ft_strequ(str, "rrr"))
		*action = rrr;
	else if (ft_strequ(str, "sa"))
		*action = sa;
	else if (ft_strequ(str, "sb"))
		*action = sb;
	else if (ft_strequ(str, "ss"))
		*action = ss;
	else if (ft_strequ(str, "pa"))
		*action = pa;
	else if (ft_strequ(str, "pb"))
		*action = pb;
	else
		result = error;
	return (result);
}

t_sort_result			*initialize_checker(void)
{
	t_sort_result			*input_data;

	input_data = (t_sort_result *)ft_memalloc(sizeof(*input_data));
	// input_data->instrution_list = NULL;
	// input_data->integer_list = NULL;
	return (input_data);
}

int						read_optional_attributes(int valid_opt_flags, int *argc,
									char ***argv, t_opt_attr *opt_attr)
{
	int			result;

	(void)valid_opt_flags;
	opt_attr->attr_flags = 0;
	opt_attr->instruction_file = NULL;
	result = 1;
	if (*argc && ft_strequ(*argv[0], "-f"))
	{
		(*argc)--;
		(*argv)++;
		if (*argc > 0)
		{
			opt_attr->instruction_file = ft_strdup(*argv[0]);
			opt_attr->attr_flags |= instruction_file;
			(*argc)--;
			(*argv)++;
		}
		else
			result = 0;
	}
	return (result);
}

int						read_integer_values(t_sort_result *input_data,
														int argc, char **argv)
{
	t_validation_result		result;
	char					*integer_string;
	t_input_data			*input;

	input = (t_input_data *)ft_memalloc(sizeof(*input));
	input->int_array_size = 0;
	input->int_list = NULL;
	(void)input_data;
	integer_string = merge_args(argv, argc);
	result = ok;
	if (string_to_array(integer_string, input))
		result = error;
	ft_strdel(&integer_string);
	input_data->stack_a.int_lst = input->int_list;
	input_data->stack_a.int_lst_size = input->int_array_size;
	input_data->stack_b.int_lst = NULL;
	input_data->stack_b.int_lst_size = 0;
	free(input->int_array);
	free(input);
	return (result);
}
