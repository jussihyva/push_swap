/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 16:22:03 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/11 12:43:04 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static t_checker_input			*initialize_checker(void)
{
	t_checker_input			*input_data;

	input_data = (t_checker_input *)ft_memalloc(sizeof(*input_data));
	input_data->instrution_list = NULL;
	input_data->integer_list = NULL;
	return (input_data);
}

static t_validation_result		validate_result(t_checker_input *input_data)
{
	t_list		*ptr;
	t_list		*top;

	top = input_data->stack_a.top;
	ptr = top;
	while (ptr->next != top &&
							*(int *)ptr->content < *(int *)ptr->next->content)
		ptr = ptr->next;
	ptr = ptr->next;
	if (ptr == top)
		return (ok);
	else
		return (ko);
}

static t_validation_result		read_instructions(t_checker_input *input_data)
{
	int						chars;
	char					*line;
	t_validation_result		result;
	t_sort_result			sort_result;

	line = NULL;
	sort_result.stack_a.int_lst = input_data->stack_a.int_lst;
	sort_result.stack_b.int_lst = input_data->stack_b.int_lst;
	sort_result.stack_a.top = input_data->stack_a.top;
	while ((chars = ft_get_next_line(0, &line)) > 0)
	{
		ft_printf("%-5d: %s\n", chars, line);
		ft_strdel(&line);
		execute_action(&sort_result, ra);
	}
	ft_strdel(&line);
	input_data->stack_a.int_lst = sort_result.stack_a.int_lst;
	input_data->stack_b.int_lst = sort_result.stack_b.int_lst;
	input_data->stack_a.top = sort_result.stack_a.top;
	result = validate_result(input_data);
	return (result);
}

static t_validation_result		read_input_data(t_checker_input *input_data,
														int argc, char **argv)
{
	int						valid_opt_flags;
	t_opt_attr				opt_attr;
	t_validation_result		result;
	t_list					*elem;

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
	elem = input_data->stack_a.int_lst;
	while (elem->next)
		elem = elem->next;
	input_data->stack_a.int_lst->prev = elem;
	elem->next = input_data->stack_a.int_lst;
	input_data->stack_a.top = input_data->stack_a.int_lst;
	if (result == ok && validate_result(input_data) != ok)
		result = read_instructions(input_data);
	if (opt_attr.attr_flags & instruction_file)
		free(opt_attr.instruction_file);
	return (result);
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
		result = validate_result(input_data);
	return_code = print_result(result);
	input_data->stack_a.top->prev->next = NULL;
	ft_lstdel(&input_data->stack_a.int_lst, *del_int_list);
	return (return_code);
}
