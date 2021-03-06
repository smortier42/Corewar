/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spliesei <spliesei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 17:42:20 by spliesei          #+#    #+#             */
/*   Updated: 2018/06/28 12:01:11 by jjauzion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	store_name(t_params *params, char *line)
{
	int	index_name;
	int	index_line;

	index_name = -1;
	index_line = -1;
	while (line[++index_line] && line[index_line] != '"')
		;
	while (line[++index_line] && line[index_line] != '"' && index_name <
		PROG_NAME_LENGTH + 1)
		params->header.prog_name[++index_name] = line[index_line];
	if (index_name >= PROG_NAME_LENGTH)
	{
		ft_printf("Error: Name is too long !\n");
		exit(0);
	}
	while (++index_name <= PROG_NAME_LENGTH)
		params->header.prog_name[index_name] = 0;
}

void	store_comment(t_params *params, char *line)
{
	int	index_comment;
	int	index_line;

	index_comment = -1;
	index_line = -1;
	while (line[++index_line] && line[index_line] != '"')
		;
	while (line[++index_line] && line[index_line] != '"' && index_comment <
		COMMENT_LENGTH + 1)
		params->header.comment[++index_comment] = line[index_line];
	if (index_comment >= COMMENT_LENGTH)
	{
		ft_printf("Error: Comment is too long !\n");
		exit(0);
	}
	while (++index_comment < COMMENT_LENGTH + 1)
		params->header.comment[index_comment] = 0;
}

void	get_header(t_params *params)
{
	int	index;
	int	i2;

	index = -1;
	while (params->file[++index] && index < 2)
	{
		i2 = -1;
		while (params->file[index][++i2] && (params->file[index][i2] == ' '
			|| params->file[index][i2] == '\t'))
			;
		if (ft_strncmp(NAME_CMD_STRING, params->file[index] + i2,
				ft_strlen(NAME_CMD_STRING)) == 0)
			store_name(params, params->file[index]);
		if (ft_strncmp(COMMENT_CMD_STRING, params->file[index] + i2,
				ft_strlen(COMMENT_CMD_STRING)) == 0)
			store_comment(params, params->file[index]);
	}
}

int		get_program_size(t_params *params)
{
	t_instr	*tmp;

	tmp = params->instr;
	if (!tmp)
	{
		ft_printf("Wrong file, please check instructions ...\n");
		exit(0);
	}
	while (tmp->next)
		tmp = tmp->next;
	params->header.prog_size = tmp->address + tmp->nbr_bytes;
	return (params->header.prog_size);
}

void	print_header(int file, t_params *params)
{
	printbits_int(COREWAR_EXEC_MAGIC, file);
	write(file, params->header.prog_name, PROG_NAME_LENGTH);
	write(file, "\0\0\0\0", 4);
	printbits_int(get_program_size(params), file);
	write(file, params->header.comment, COMMENT_LENGTH);
	write(file, "\0\0\0\0", 4);
}
