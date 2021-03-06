/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spliesei <spliesei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 18:24:35 by spliesei          #+#    #+#             */
/*   Updated: 2018/06/21 16:42:55 by spliesei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	get_params(t_instr *tmp, char *line)
{
	char	**split;
	int		index;

	split = ft_strsplit(line, SEPARATOR_CHAR);
	if (!(tmp->arg = (char **)ft_memalloc(sizeof(char *) * (tmp->nbr_arg + 1))))
		exit(0);
	tmp->arg[tmp->nbr_arg] = NULL;
	index = -1;
	while (split[++index])
	{
		tmp->arg[index] = ft_strtrim(split[index]);
		ft_strdel(&split[index]);
	}
	ft_memdel((void **)&split);
}

void	calc_bytes(t_instr *tmp)
{
	int	index;

	tmp->nbr_bytes = 1;
	index = -1;
	while (++index < tmp->nbr_arg)
	{
		tmp->arg_type[index] == REG_CODE ? tmp->nbr_bytes += REG_BYTES : 0;
		tmp->arg_type[index] == DIR_CODE ? tmp->nbr_bytes += DIR_BYTES : 0;
		tmp->arg_type[index] == IND_CODE ? tmp->nbr_bytes += IND_BYTES : 0;
	}
	if (tmp->ocp != 0)
		tmp->nbr_bytes += 1;
}

void	calc_ocp(t_instr *tmp)
{
	int	index;

	tmp->ocp = 0;
	index = -1;
	while (++index < tmp->nbr_arg)
	{
		if (index == 0)
		{
			tmp->arg_type[index] == REG_CODE ? tmp->ocp += 64 : 0;
			tmp->arg_type[index] == DIR_CODE ? tmp->ocp += 128 : 0;
			tmp->arg_type[index] == IND_CODE ? tmp->ocp += 192 : 0;
		}
		if (index == 1)
		{
			tmp->arg_type[index] == REG_CODE ? tmp->ocp += 16 : 0;
			tmp->arg_type[index] == DIR_CODE ? tmp->ocp += 32 : 0;
			tmp->arg_type[index] == IND_CODE ? tmp->ocp += 48 : 0;
		}
		if (index == 2)
		{
			tmp->arg_type[index] == REG_CODE ? tmp->ocp += 4 : 0;
			tmp->arg_type[index] == DIR_CODE ? tmp->ocp += 8 : 0;
			tmp->arg_type[index] == IND_CODE ? tmp->ocp += 12 : 0;
		}
	}
}

void	fill_arg_types(t_params *params, t_instr *tmp)
{
	int		index;

	index = -1;
	if (!(tmp->arg_type = (int *)ft_memalloc(sizeof(int) * tmp->nbr_arg)))
		exit(0);
	while (tmp->arg[++index])
		tmp->arg_type[index] = check_type(params, tmp->arg[index]);
}

void	check_name_label(char *str)
{
	int	index;

	index = -1;
	while (str[++index])
	{
		if (!ft_strchr(LABEL_CHARS, str[index]))
		{
			ft_putendl("Error");
			ft_printf("\e[31m%s\e[0m is a wrong name for label!\n", str);
			ft_printf("If you may only use those letters: ");
			ft_printf("\e[32m%s\e[0m it would be great thanks!\n", LABEL_CHARS);
			exit(1);
		}
	}
}
