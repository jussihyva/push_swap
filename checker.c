/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 16:22:03 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/11 17:31:01 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static t_validation_result		validate_result(t_sort_result *input_data)
{
	t_list		*ptr;
	t_list		*top;

	if (input_data->stack_b.top)
		return (ko);
	else if (!input_data->stack_a.top)
		return (ok);
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

static t_validation_result		read_instructions(t_sort_result *input_data,
																		int fd)
{
	int						chars;
	char					*line;
	t_validation_result		result;
	t_move_action			action;

	line = NULL;
	while ((chars = ft_get_next_line(fd, &line)) > 0)
	{
		result = str_to_move_action(line, &action);
		if (result != ok)
			break ;
		ft_strdel(&line);
		execute_action(input_data, action);
	}
	ft_strdel(&line);
	if (result == ok)
		result = validate_result(input_data);
	return (result);
}

static t_validation_result		read_input_data(t_sort_result *input_data,
														int argc, char **argv)
{
	int						valid_opt_flags;
	t_opt_attr				opt_attr;
	t_validation_result		result;
	int						fd;

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
	activate_linked_list_loop(input_data->stack_a.int_lst);
	input_data->stack_a.top = input_data->stack_a.int_lst;
	input_data->stack_b.top = NULL;
	if (result == ok && validate_result(input_data) != ok)
	{
		fd = 0;
		if (opt_attr.attr_flags & instruction_file)
		{
			fd = open(opt_attr.instruction_file, O_RDONLY);
		}
		result = read_instructions(input_data, fd);
	}
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
	t_sort_result			input_data;
	t_validation_result		result;
	int						return_code;

	init_sort_result(&input_data);
	result = read_input_data(&input_data, --argc, ++argv);
	if (result == ok)
		result = validate_result(&input_data);
	return_code = print_result(result);
	if (input_data.stack_a.int_lst_size)
	{
		input_data.stack_a.top->prev->next = NULL;
		ft_lstdel(&input_data.stack_a.int_lst, *del_int_list);
	}
	return (return_code);
}
