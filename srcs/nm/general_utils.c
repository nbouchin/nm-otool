/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 09:41:22 by nbouchin          #+#    #+#             */
/*   Updated: 2018/11/08 11:41:36 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft_nm.h"

int			is_out(char *offset)
{
	static char *fsize = 0;

	if (fsize == 0)
		fsize = offset;
	else
	{
		if (offset > fsize)
		{
			ft_putendl("File bad formated");
			return (1);
		}
	}
	return (0);
}

int			is_magic(uint32_t magic)
{
	if (magic != MH_MAGIC
			&& magic != MH_CIGAM
			&& magic != MH_MAGIC_64
			&& magic != MH_CIGAM_64
			&& magic != FAT_MAGIC
			&& magic != FAT_CIGAM
			&& magic != FAT_MAGIC_64
			&& magic != FAT_CIGAM_64)
		return (0);
	else
		return (1);
}

int			is_fat(uint32_t magic)
{
	if (magic == FAT_MAGIC || magic == FAT_CIGAM)
		return (1);
	return (0);
}

int			is_mach(uint32_t magic)
{
	if (magic == MH_MAGIC || magic == MH_CIGAM
			|| magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
		return (1);
	return (0);
}

int			is_64bits(uint32_t magic)
{
	if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
		return (1);
	return (0);
}

int			is_32bits(uint32_t magic)
{
	if (magic == MH_MAGIC || magic == MH_CIGAM)
		return (1);
	return (0);
}

uint32_t	swi(uint32_t x)
{
	return ((((((x) & 0xff000000) >> 24) |
					(((x) & 0x00ff0000) >> 8) |
					(((x) & 0x0000ff00) << 8) |
					(((x) & 0x000000ff) << 24))));
}
