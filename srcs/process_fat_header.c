/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_fat_header.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 09:22:50 by nbouchin          #+#    #+#             */
/*   Updated: 2018/10/30 12:15:14 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_nm.h"

int		process_fat_header(t_fat_header const *fat_header, t_fmetadata *fmetadata)
{
	uint32_t			i;
	t_fat_arch			*fat_arch;
	t_mach_header_64	*mach_header_64;

	i = -1;
	fmetadata->to_print = 0;
	fat_arch = (t_fat_arch*)(fat_header + 1);
	while (++i < OSSwapInt32(fat_header->nfat_arch))
	{
		mach_header_64 = (t_mach_header_64*)((char *)fat_header
				+ OSSwapInt32(fat_arch->offset));
		if (!ft_strncmp((char *)mach_header_64, ARMAG, SARMAG))
		{
			archive_files(mach_header_64, fmetadata);
			return (1);// TODO : print only computer architecture.
		}
		else
			process_header(mach_header_64,
					OSSwapInt32(mach_header_64->magic), fmetadata);
		fat_arch++;
	}
	return (1);
}
