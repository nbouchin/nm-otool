/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 09:22:50 by nbouchin          #+#    #+#             */
/*   Updated: 2018/10/18 12:31:26 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_nm.h"

int		fat_header(t_fat_header *fat_header)
{
	uint32_t			i;
	t_fat_arch			*fat_arch;
	t_mach_header_64	*mach_header_64;

	i = -1;
	fat_arch = (t_fat_arch*)(fat_header + 1);
//	ft_printf("fat_header->magic : %x\nfat_header->nfat_arch : %u\n", OSSwapInt32(fat_header->magic), OSSwapInt32(fat_header->nfat_arch));
	while (++i < OSSwapInt32(fat_header->nfat_arch))
	{
//		ft_printf("Offset : %lu\n", OSSwapInt32(fat_arch->offset));
		mach_header_64 = (t_mach_header_64*)((char *)fat_header + OSSwapInt32(fat_arch->offset));
//		ft_printf("mach_header_64->magic : %x\n", mach_header_64->magic);
		regular_header(mach_header_64);
		fat_arch++;
	}
	return (1);
}
