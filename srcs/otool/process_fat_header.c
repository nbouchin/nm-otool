/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_fat_header.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 09:22:50 by nbouchin          #+#    #+#             */
/*   Updated: 2018/11/08 12:42:59 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft_nm.h"

int		find_64(t_fat_header const *fat_header, t_fmetadata *fmetadata)
{
	uint32_t			i;
	int					ret;
	t_fat_arch			*fat_arch;
	t_mach_header_64	*mach_header_64;

	i = -1;
	ret = 0;
	fmetadata->to_print = 0;
	fat_arch = (t_fat_arch*)(fat_header + 1);
	while (++i < swi(fat_header->nfat_arch))
	{
		mach_header_64 = (t_mach_header_64*)((char *)fat_header
				+ swi(fat_arch->offset));
		if (is_64bits(mach_header_64->magic))
			ret = 1;
		if (is_32bits(mach_header_64->magic))
			fmetadata->alone += 1;
		fat_arch++;
	}
	return (ret);
}

int		fat_have_64(t_fat_header const *fat_header, t_fmetadata *fmetadata)
{
	uint32_t			i;
	t_fat_arch			*fat_arch;
	t_mach_header_64	*mach_header_64;

	i = 0;
	fmetadata->to_print = 0;
	fat_arch = (t_fat_arch*)(fat_header + 1);
	while (i++ < swi(fat_header->nfat_arch))
	{
		mach_header_64 = (t_mach_header_64*)((char *)fat_header
				+ swi(fat_arch->offset));
		if (is_64bits(mach_header_64->magic))
		{
			if (!ft_strncmp((char *)mach_header_64, ARMAG, SARMAG))
			{
				archive_files(mach_header_64, fmetadata);
				return (1);
			}
			process_header(mach_header_64,
					swi(mach_header_64->magic), fmetadata);
			return (1);
		}
		fat_arch++;
	}
	return (1);
}

int		dont_have_64(t_fat_header const *fat_header, t_fmetadata *fmetadata)
{
	uint32_t			i;
	t_fat_arch			*fat_arch;
	t_mach_header_64	*mach_header_64;

	i = 0;
	fmetadata->to_print = 0;
	fat_arch = (t_fat_arch*)(fat_header + 1);
	while (i++ < swi(fat_header->nfat_arch))
	{
		mach_header_64 = (t_mach_header_64*)((char *)fat_header
				+ swi(fat_arch->offset));
		fmetadata->to_print = 1;
		fmetadata->argc += 1;
		if (!ft_strncmp((char *)mach_header_64, ARMAG, SARMAG))
		{
			archive_files(mach_header_64, fmetadata);
			return (1);
		}
		process_header(mach_header_64,
				swi(mach_header_64->magic), fmetadata);
		fat_arch++;
	}
	return (1);
}

int		process_fat_header(t_fat_header const *fat_header,
		t_fmetadata *fmetadata)
{
	int					have_64;

	fmetadata->to_print = 0;
	have_64 = find_64(fat_header, fmetadata);
	if (have_64)
		return (fat_have_64(fat_header, fmetadata));
	return (dont_have_64(fat_header, fmetadata));
}
