/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 17:00:08 by nbouchin          #+#    #+#             */
/*   Updated: 2018/11/08 15:45:38 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft_nm.h"

void			print_error_fd(char const *file_name,
		char const *error, int fd)
{
	ft_putstr_fd(file_name, fd);
	ft_putendl_fd(error, fd);
}

void			print_section(t_mach_header_64 const *mach_header_64,
		t_section_64 *section)
{
	uint64_t	i;
	char		*section_string;
	char		*address;

	i = 0;
	address = (char*)section->addr;
	section_string = (char *)mach_header_64 + section->offset;
	while (i < section->size)
	{
		if (i == 0)
			ft_putendl("");
		if (i % 16 == 0)
		{
			if (i > 0)
				ft_putendl("");
			ft_printf("%016lx\t", address);
		}
		ft_printf("%02x ", (uint8_t)(*section_string));
		address++;
		section_string++;
		i++;
	}
	ft_putendl("");
}

void			print_section_32(t_mach_header_64 const *mach_header_64,
		t_section_64 *section)
{
	uint32_t	i;
	char		*section_string;
	uint32_t	address;

	i = 0;
	address = ((t_section*)section)->addr;
	section_string = (char *)mach_header_64 + ((t_section*)section)->offset;
	while (i < ((t_section*)section)->size)
	{
		if (i == 0)
			ft_putendl("");
		if (i % 16 == 0)
		{
			if (i > 0)
				ft_putendl("");
			ft_printf("%08lx\t", address);
		}
		ft_printf("%02x ", (uint8_t)(*section_string));
		address++;
		section_string++;
		i++;
	}
	ft_putendl("");
}

void			print_big_section_32(t_mach_header_64 const *mach_header_64,
		t_section_64 *section)
{
	uint32_t	i;
	char		*st;
	uint32_t	address;

	i = 0;
	address = swi(((t_section*)section)->addr);
	st = (char *)mach_header_64 + swi(((t_section*)section)->offset);
	while (i < swi(((t_section*)section)->size))
	{
		if (i == 0)
			ft_putendl("");
		if (i % 4 == 0 && i > 0)
			ft_putchar(' ');
		if (i % 16 == 0)
		{
			if (i > 0)
				ft_putendl("");
			ft_printf("%08lx\t", address);
		}
		ft_printf("%02x", (uint8_t)(*st));
		address++;
		st++;
		i++;
	}
	ft_putendl(" ");
}
