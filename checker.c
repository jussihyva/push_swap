/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 16:22:03 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/11 09:37:06 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static t_checker_input			*initialize_checker(void)
{
	t_checker_input			*input_data;

	input_data = (t_checker_input *)ft_memalloc(sizeof(*input_data));
	return (input_data);
}

static t_validation_result		read_input_data(t_checker_input *input_data,
														int argc, char **argv)
{
	int						valid_opt_flags;
	t_opt_attr				opt_attr;
	t_validation_result		result;

	input_data->instrution_list = NULL;
	input_data->integer_list = NULL;
	result = ok;
	valid_opt_flags = instruction_file;
	if (read_optional_attributes(valid_opt_flags, &argc, &argv, &opt_attr))
	{
		if (argc)
			result = read_integer_values(input_data, argc, argv);
		else
			result = no_param;
	}
	else
		result = error;
	if (opt_attr.attr_flags & instruction_file)
		free(opt_attr.instruction_file);
	return (result);
}

static t_validation_result		validate_instructions(
													t_checker_input *input_data)
{
	t_move_action		instruction;
	t_list				*elem;

	(void)instruction;
	ft_printf("%d\n", *(int *)input_data->stack_a.int_lst->content);
	ft_printf("%d\n", input_data->stack_b.int_lst);
	if (input_data->instrution_list)
	{
		elem = *input_data->instrution_list;
		while (elem)
		{
			elem = elem->next;
		}
	}
	return (ok);
}

static int						print_result(t_validation_result result)
{
	int			return_code;

	return_code = 0;
	if (result == no_param)
		;
	else if (result == ok)
		ft_dprintf(1, "OK\n");
	else if (result == ko)
		ft_dprintf(1, "KO\n");
	else if (result == error)
	{
		ft_dprintf(2, "Error\n");
		return_code = 1;
	}
	return (0);
}

int								main(int argc, char **argv)
{
	t_checker_input			*input_data;
	t_validation_result		result;
	int						return_code;

	input_data = initialize_checker();
	result = read_input_data(input_data, --argc, ++argv);
	if (result == ok)
		result = validate_instructions(input_data);
	return_code = print_result(result);
	ft_lstdel(&input_data->stack_a.int_lst, *del_int_list);
	return (return_code);
}
