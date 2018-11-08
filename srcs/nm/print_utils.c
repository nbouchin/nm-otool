/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 13:33:50 by nbouchin          #+#    #+#             */
/*   Updated: 2018/11/08 13:35:07 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft_nm.h"

void			ft_putnendl(const char *str, size_t length)
{
	size_t		i;

	i = 0;
	while (i < length && str[i])
		ft_putchar(str[i++]);
	ft_putendl("");
}

void			print_symbol_32(uint64_t const n_value, char const letter,
		char const *symname, t_metadata const *metadata)
{
	if (letter == 'U' || letter == 'u')
	{
		ft_printf("%-8c %c ", ' ', letter);
		ft_putnendl((char*)symname, metadata->end - symname);
	}
	else
	{
		ft_printf("%08llx %c ", (uint32_t)n_value, letter);
		ft_putnendl((char*)symname, metadata->end - symname);
	}
}

void			print_symbol_64(uint64_t const n_value, char const letter,
		char const *symname, t_metadata const *metadata)
{
	if (letter == 'U' || letter == 'u')
	{
		ft_printf("%-16c %c ", ' ', letter);
		ft_putnendl((char*)symname, metadata->end - symname);
	}
	else
	{
		ft_printf("%016llx %c ", n_value, letter);
		ft_putnendl((char*)symname, metadata->end - symname);
	}
}

char			get_type_char(t_metadata const *mdata, int const i)
{
	char	to_ret;

	to_ret = 's';
	if (!ft_strcmp(mdata->sectab[mdata->symtab[i].n_sect - 1].sectname,
				SECT_TEXT))
		to_ret = 't';
	else if (!ft_strcmp(mdata->sectab[mdata->symtab[i].n_sect - 1].sectname,
				SECT_DATA))
		to_ret = 'd';
	else if (!ft_strcmp(mdata->sectab[mdata->symtab[i].n_sect - 1].sectname,
				SECT_BSS))
		to_ret = 'b';
	return (to_ret);
}
