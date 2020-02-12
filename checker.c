/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 16:22:03 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/12 12:38:43 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static t_validation_result		validate_result(t_sort_result *sort_result)
{
	t_list		*ptr;
	t_list		*top;

	if (sort_result->stack_b.top)
		return (ko);
	else if (!sort_result->stack_a.top)
		return (ok);
	top = sort_result->stack_a.top;
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

static t_validation_result		read_instructions(t_sort_result *sort_result,
															t_opt_attr opt_attr)
{
	int						chars;
	char					*line;
	t_validation_result		result;
	t_move_action			action;
	int						fd;

	fd = 0;
	if (opt_attr.attr_flags & instruction_file)
	{
		fd = open(opt_attr.instruction_file, O_RDONLY);
	}
	line = NULL;
	while ((chars = ft_get_next_line(fd, &line)) > 0)
	{
		result = str_to_move_action(line, &action);
		if (result != ok)
			break ;
		ft_strdel(&line);
		execute_action(sort_result, action);
	}
	ft_strdel(&line);
	if (result == ok)
		result = validate_result(sort_result);
	return (result);
}

static void						save_to_sort_result(t_input_data *input,
													t_sort_result *sort_result)
{
	sort_result->stack_a.int_lst = input->int_list;
	sort_result->stack_a.int_lst_size = input->int_array_size;
	sort_result->stack_a.top = sort_result->stack_a.int_lst;
	free(input->int_array);
	free(input);
	return ;
}

static t_validation_result		read_input_data(t_sort_result *sort_result,
														int argc, char **argv)
{
	int						valid_opt_flags;
	t_opt_attr				opt_attr;
	t_validation_result		result;
	t_input_data			*input;

	valid_opt_flags = instruction_file;
	if (read_optional_attributes(valid_opt_flags, &argc, &argv, &opt_attr))
	{
		if (argc)
		{
			input = (t_input_data *)ft_memalloc(sizeof(*input));
			result = read_integer_values(input, argc, argv);
			save_to_sort_result(input, sort_result);
		}
		else
			result = no_param;
	}
	else
		result = error;
	activate_linked_list_loop(sort_result->stack_a.int_lst);
	if (result == ok && validate_result(sort_result) != ok)
		result = read_instructions(sort_result, opt_attr);
	if (opt_attr.attr_flags & instruction_file)
		free(opt_attr.instruction_file);
	return (result);
}

int								main(int argc, char **argv)
{
	t_sort_result			sort_result;
	t_validation_result		result;
	int						return_code;

	init_sort_result(&sort_result);
	result = read_input_data(&sort_result, --argc, ++argv);
	if (result == ok)
		result = validate_result(&sort_result);
	return_code = print_result(result);
	if (sort_result.stack_a.int_lst_size)
	{
		if (sort_result.stack_a.top)
			sort_result.stack_a.top->prev->next = NULL;
		ft_lstdel(&sort_result.stack_a.int_lst, *del_int_list);
	}
	return (return_code);
}
