/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 09:41:22 by nbouchin          #+#    #+#             */
/*   Updated: 2018/10/24 14:03:10 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_nm.h"

int		is_magic(uint32_t magic)
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

int		is_fat(uint32_t magic)
{
	if (magic == FAT_MAGIC || magic == FAT_CIGAM)
		return (1);
	return (0);
}

int		is_mach(uint32_t magic)
{
	if (magic == MH_MAGIC || magic == MH_CIGAM
			|| magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
		return (1);
	return (0);
}

int		is_64bits(uint32_t magic)
{
	if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
		return (1);
	return (0);
}

int		is_32bits(uint32_t magic)
{
	if (magic == MH_MAGIC || magic == MH_CIGAM)
		return (1);
	return (0);
}
