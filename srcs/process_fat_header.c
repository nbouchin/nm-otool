/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_fat_header.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 09:22:50 by nbouchin          #+#    #+#             */
/*   Updated: 2018/10/25 17:11:44 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_nm.h"

int		process_fat_header(t_fat_header const *fat_header)
{
	uint32_t			i;
	t_fat_arch			*fat_arch;
	t_mach_header_64	*mach_header_64;

	i = -1;
	fat_arch = (t_fat_arch*)(fat_header + 1);
	while (++i < OSSwapInt32(fat_header->nfat_arch))
	{
		mach_header_64 = (t_mach_header_64*)((char *)fat_header
		+ OSSwapInt32(fat_arch->offset));
		process_header(mach_header_64, OSSwapInt32(mach_header_64->magic));
		fat_arch++;
	}
	return (1);
}
