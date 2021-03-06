/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spliesei <spliesei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 17:16:46 by spliesei          #+#    #+#             */
/*   Updated: 2018/06/28 11:47:46 by jjauzion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*get_all_name_line(int fd, char *line)
{
	char	*ret;
	char	*line2;

	if (!(ret = (char *)ft_memalloc(sizeof(char) * PROG_NAME_LENGTH +
		ft_strlen(line) + 2)))
		exit(0);
	ft_strcat(ret, line);
	ft_strcat(ret, "\n");
	while (get_next_line(fd, &line2) == 1 && !ft_strchr(line2, '"'))
	{
		ft_strcat(ret, line2);
		ft_strcat(ret, "\n");
		ft_strdel(&line2);
	}
	ft_strcat(ret, line2);
	if (ft_strchr(line2, '"') && (ft_strchr(line2, '"')[1] != '\0'))
	{
		ft_printf("Error: Syntax error after name !\n");
		exit(0);
	}
	ft_strdel(&line2);
	return (ret);
}

char	*get_all_comment_line(int fd, char *line)
{
	char	*ret;
	char	*line2;

	if (!(ret = (char *)ft_memalloc(sizeof(char) *
					(COMMENT_LENGTH + ft_strlen(line) + 2))))
		exit(0);
	ft_strcat(ret, line);
	ft_strcat(ret, "\n");
	while (get_next_line(fd, &line2) == 1 && !ft_strchr(line2, '"'))
	{
		ft_strcat(ret, line2);
		ft_strcat(ret, "\n");
		ft_strdel(&line2);
	}
	ft_strcat(ret, line2);
	if (ft_strchr(line2, '"') && (ft_strchr(line2, '"')[1] != '\0'))
	{
		ft_printf("Error: Syntax error after comment !\n");
		exit(0);
	}
	ft_strdel(&line2);
	return (ret);
}

char	*pass_ws(char *str)
{
	int	index;

	if (!str)
		exit(0);
	index = -1;
	while (str[++index] && (str[index] == ' ' || str[index] == '\t'))
		;
	return (str + index);
}
