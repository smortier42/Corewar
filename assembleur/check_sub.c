/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spliesei <spliesei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 13:01:13 by spliesei          #+#    #+#             */
/*   Updated: 2018/06/21 16:17:49 by spliesei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	check_nbr_arg_sub(char **split)
{
	int		i;

	i = -1;
	while (split[++i])
		;
	if (i != 3)
	{
		ft_printf("Error: Wrong number of arguments!\n");
		exit(0);
	}
}

void	check_sub_errors(t_params *params, char *arg1, char *arg2, char *arg3)
{
	if (check_type(params, arg1) != REG_CODE)
	{
		ft_printf("Error: Wrong type of arg1 for (sub)!\n");
		exit(0);
	}
	if (check_type(params, arg2) != REG_CODE)
	{
		ft_printf("Error: Wrong type of arg2 for (sub)!\n");
		exit(0);
	}
	if (check_type(params, arg3) != REG_CODE)
	{
		ft_printf("Error: Wrong type of arg3 for (sub)!\n");
		exit(0);
	}
}

int		check_sub_par(t_params *params, char *line, int index_line)
{
	char	**split;
	char	*arg1;
	char	*arg2;
	char	*arg3;
	int		index;

	split = ft_strsplit(line, SEPARATOR_CHAR);
	check_nbr_arg_sub(split);
	arg1 = ft_strtrim(split[0]);
	arg2 = ft_strtrim(split[1]);
	arg3 = ft_strtrim(split[2]);
	index = -1;
	while (split[++index])
		ft_strdel(&split[index]);
	ft_memdel((void *)&split);
	check_sub_errors(params, arg1, arg2, arg3);
	(void)index_line;
	ft_strdel(&arg1);
	ft_strdel(&arg2);
	ft_strdel(&arg3);
	return (1);
}
