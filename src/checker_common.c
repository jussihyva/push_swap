/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_common.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 14:43:05 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/11 09:25:31 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int			read_optional_attributes(int valid_opt_flags, int *argc,
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

int			read_integer_values(t_checker_input *input_data, int argc,
																	char **argv)
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
	input_data->stack_b.int_lst = NULL;
	free(input->int_array);
	free(input);
	return (result);
}