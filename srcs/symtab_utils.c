/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 16:55:50 by nbouchin          #+#    #+#             */
/*   Updated: 2018/10/23 16:55:47 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_nm.h"

char	*ret_buff(const int addr)
{
	const char	*digits;
	size_t		nb;
	char		*buffer;
	size_t		len;

	digits = "0123456789abcdef";
	len = 0;
	nb = (size_t)addr;
	buffer = malloc(sizeof(char) * 8);
	if (nb == 0)
		ft_putchar('0');
	while (nb > 0)
	{
		buffer[len++] = digits[(size_t)nb % 16];
		nb /= 16;
	}
	ft_strrev(buffer);
	return buffer;
}

void		print_symbol(uint64_t n_value, char letter, char *symbol_name, int arch_type)
{
	char	*str;
	char	*to_print;
	int		len;
	int		i;

	i = 7;
	len = 7;
	to_print = ft_strnew(16);
	if (arch_type == 64)
	{
		if (letter == 'U')
		{
			ft_putstr("\t\t");
			ft_putchar(' ');
			ft_putchar(letter);
			ft_putchar(' ');
			ft_putendl(symbol_name);
		}
		else
		{
			str = ret_buff(n_value);
			to_print = ft_strcpy(to_print, "0000001");
			len += 8 - ft_strlen(str);
			while (i < len)
				to_print[i++] = '0';
			to_print = ft_strcat(to_print, str);
			ft_putstr(to_print);
			ft_putchar(' ');
			ft_putchar(letter);
			ft_putchar(' ');
			ft_putendl(symbol_name);
		}
	}
	else if (arch_type == 32)
	{
		(letter == 'U') ? ft_printf("%-6c %c %s\n", ' ', letter, symbol_name)
			: ft_printf("%06llx %c %s\n", n_value, letter, symbol_name);
	}
}

char		get_type_char(t_metadata *metadata, int i)
{
	char	to_ret;

	to_ret = 'U';
	if (!ft_strcmp(metadata->sectab[metadata->symtab[i].n_sect - 1].sectname, SECT_TEXT))
		to_ret = 'T';
	else if (!ft_strcmp(metadata->sectab[metadata->symtab[i].n_sect - 1].sectname, SECT_DATA))
		to_ret = 'D';
	else if (!ft_strcmp(metadata->sectab[metadata->symtab[i].n_sect - 1].sectname, SECT_BSS))
		to_ret = 'B';
	else if (!ft_strcmp(metadata->sectab[metadata->symtab[i].n_sect - 1].sectname, SECT_COMMON))
		to_ret = 'C';
	return (to_ret);
}

void		get_symbol(uint64_t n_value, char *symbol_name, t_metadata *metadata, int i)
{
	if ((metadata->symtab[i].n_type & N_STAB))
		;//	print_symbol(n_value, 'S', symbol_name, 64);
	else if ((metadata->symtab[i].n_type & N_TYPE) == N_UNDF)
		print_symbol(n_value, 'U', symbol_name, 64);
	else if ((metadata->symtab[i].n_type & N_TYPE) == N_ABS)
		print_symbol(n_value, 'A', symbol_name, 64);
	else if ((metadata->symtab[i].n_type & N_TYPE) == N_SECT)
		print_symbol(n_value, get_type_char(metadata, i), symbol_name, 64);
	else if ((metadata->symtab[i].n_type & N_TYPE) == N_INDR)
		print_symbol(n_value, 'I', symbol_name, 64);
	else if ((metadata->symtab[i].n_type & N_EXT))
		print_symbol(n_value, 'E', symbol_name, 64);
}

void		print_symtab(t_load_command *load_command, t_mach_header_64 *mach_header_64, t_metadata *metadata)
{
	uint32_t		i;
	t_nlist_64		*nlist_64;
	char			*string_table;

	i = -1;
	nlist_64 = (t_nlist_64 *)((char *)mach_header_64 + ((t_symtab_command*)load_command)->symoff);
	string_table = (char *)((char *)mach_header_64 + ((t_symtab_command*)load_command)->stroff);
	while (++i < ((t_symtab_command*)load_command)->nsyms)
	{
		if (mach_header_64->magic != MH_MAGIC)
		{
			get_symbol(metadata->symtab[i].n_value, (char *)string_table + metadata->symtab[i].n_un.n_strx, metadata, i);
			nlist_64 += 1;
		}
		else
		{
			get_symbol(((t_nlist*)metadata->symtab)[i].n_value, (char *)string_table + ((t_nlist*)metadata->symtab)[i].n_un.n_strx, metadata, i);
			nlist_64 = (t_nlist_64*)((t_nlist*)nlist_64 + 1);
		}
	}
}

t_nlist_64		*get_symtab(t_load_command *load_command, t_mach_header_64 *mach_header_64)
{
	uint32_t			i;
	t_nlist_64			*nlist_64;
	t_nlist_64			*symtab;

	i = -1;
	nlist_64 = (t_nlist_64 *)((char *)mach_header_64 + ((t_symtab_command*)load_command)->symoff);
	symtab = malloc(((t_symtab_command*)load_command)->nsyms * sizeof(t_nlist_64));
	while (++i < ((t_symtab_command*)load_command)->nsyms)
	{
		symtab[i] = *nlist_64;
		nlist_64 += 1;
	}
	return (symtab);
}
