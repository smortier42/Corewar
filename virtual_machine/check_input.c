/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjauzion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 14:05:19 by jjauzion          #+#    #+#             */
/*   Updated: 2018/06/28 15:35:24 by smortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void				*usage(char *prog_name)
{
	ft_printf("Usage : %s [-d N -coplkv] <champion1.cor> <...>\n", prog_name);
	ft_printf("\t -d N\t: Dumps memory after N cycles then exits\n");
	ft_printf("\t -c  \t: Show cycles\n");
	ft_printf("\t -o  \t: Show operations\n");
	ft_printf("\t -p  \t: Show pc movement (except for jumps)\n");
	ft_printf("\t -l  \t: Show lives\n");
	ft_printf("\t -k  \t: Show deaths\n");
	ft_printf("\t -v  \t: Visual output mode. Pipe output to love visu\n\t\t");
	ft_printf("Ex: ./corewar -v champ.cor | love visu\n");
	return (NULL);
}

static void			*free_champ(t_champion **champions, t_arena *arena, char *m)
{
	while (arena->nb_champion > 0)
	{
		free(champions[arena->nb_champion - 1]->code);
		free(champions[arena->nb_champion - 1]);
		(arena->nb_champion)--;
	}
	free(champions);
	if (m)
		ft_putstr(m);
	return (NULL);
}

static t_champion	**add_champ(t_champion **champions, t_arena *arena, char *c)
{
	if (arena->nb_champion >= MAX_PLAYERS)
		return (free_champ(champions, arena, "Error: too many champions\n"));
	if (!(champions = realloc(champions,
					sizeof(t_champion*) * (arena->nb_champion + 1))))
		return (error_ptr(NULL, "error realloc at champion creation"));
	if (!(champions[arena->nb_champion] = read_champ(c)))
		return (free_champ(champions, arena, NULL));
	(arena->nb_champion)++;
	return (champions);
}

t_champion			**check_input(int argc, char **argv, t_arena *arena)
{
	int			i;
	t_champion	**champions;
	int			ret;

	if (argc <= 1)
		return (usage(argv[0]));
	i = 0;
	champions = NULL;
	arena->nb_champion = 0;
	if (!(arena->option = (t_option*)ft_memalloc(sizeof(t_option))))
		return (NULL);
	arena->option->option = 0;
	while (++i < argc)
	{
		if ((ret = option(&i, argc, argv, arena->option)) == 1)
		{
			if (!(champions = add_champ(champions, arena, argv[i])))
				return (NULL);
		}
		else if (ret == ERROR)
			return (usage(argv[0]));
	}
	return (champions);
}
