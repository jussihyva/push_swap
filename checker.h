/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 16:22:53 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/09 19:19:54 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H
# include <stdlib.h>
# include "libft.h"
# include "push_swap.h"

typedef enum	e_attr_flags
{
	instruction_file = 1,
	result
}				t_attr_flags;

typedef struct	s_opt_attr
{
	t_attr_flags	attr_flags;
	char			*instruction_file;
}				t_opt_attr;

typedef enum	e_validation_result
{
	no_param,
	ok,
	ko,
	error
}				t_validation_result;

typedef struct	s_checker_input
{
	t_list		*integer_list;
	t_list		**instrution_list;
}				t_checker_input;

int			read_optional_attributes(int valid_opt_flags, int *argc,
									char ***argv, t_opt_attr *opt_attr);
int			read_integer_values(t_checker_input *input_data, int argc,
																char **argv);
char		*merge_args(char **array, int size);
int			string_to_array(char *s, t_input_data *input);

#endif
