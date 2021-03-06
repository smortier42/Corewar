/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lld.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spliesei <spliesei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 13:07:00 by spliesei          #+#    #+#             */
/*   Updated: 2018/06/21 16:21:20 by spliesei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	check_nbr_arg_lld(char **split)
{
	int		i;

	i = -1;
	while (split[++i])
		;
	if (i != 2)
	{
		ft_printf("Error: Wrong number of arguments!\n");
		exit(0);
	}
}

void	check_lld_errors(t_params *params, char *arg1, char *arg2)
{
	if (check_type(params, arg1) != DIR_CODE &&
		check_type(params, arg1) != IND_CODE)
	{
		ft_printf("Error: Wrong type of arg1 for (lld)!\n");
		exit(0);
	}
	if (check_type(params, arg2) != REG_CODE)
	{
		ft_printf("Error: Wrong type of arg2 for (lld)!\n");
		exit(0);
	}
}

int		check_lld_par(t_params *params, char *line, int index_line)
{
	char	**split;
	char	*arg1;
	char	*arg2;
	int		index;

	(void)index_line;
	split = ft_strsplit(line, SEPARATOR_CHAR);
	check_nbr_arg_lld(split);
	arg1 = ft_strtrim(split[0]);
	arg2 = ft_strtrim(split[1]);
	index = -1;
	while (split[++index])
		ft_strdel(&split[index]);
	ft_memdel((void *)&split);
	check_lld_errors(params, arg1, arg2);
	ft_strdel(&arg1);
	ft_strdel(&arg2);
	return (1);
}
