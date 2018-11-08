/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 13:28:14 by nbouchin          #+#    #+#             */
/*   Updated: 2018/11/08 13:28:50 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft_nm.h"

t_section_64	*sectab_realloc(t_section_64 *sectab, size_t new_size,
		uint32_t old_size)
{
	t_section_64	*swap;

	swap = (t_section_64*)ft_memalloc(new_size);
	swap = ft_memcpy(swap, sectab, old_size * sizeof(t_section_64));
	free(sectab);
	return (swap);
}

t_section_64	*alloc_sectab_64(t_section_64 *sectab, t_metadata *metadata,
		t_segment_command_64 const *sc_64)
{
	int32_t	old_size;

	old_size = metadata->nsect;
	metadata->nsect += sc_64->nsects;
	sectab = (sectab == NULL)
	? ft_memalloc(sc_64->nsects * sizeof(t_section_64))
	: sectab_realloc(sectab, metadata->nsect * sizeof(t_section_64), old_size);
	return (sectab);
}

t_section_64	*alloc_sectab(t_mach_header_64 const *mach_header_64,
	t_section_64 *sectab, t_metadata *mdata, t_segment_command const *sc)
{
	int32_t	old_size;

	old_size = mdata->nsect;
	if (mach_header_64->magic == MH_CIGAM)
	{
		mdata->nsect += swi(sc->nsects);
		sectab = (sectab == NULL)
		? ft_memalloc(swi(sc->nsects) * sizeof(t_section_64))
		: sectab_realloc(sectab, mdata->nsect * sizeof(t_section_64), old_size);
	}
	else
	{
		mdata->nsect += sc->nsects;
		sectab = (sectab == NULL)
		? ft_memalloc(sc->nsects * sizeof(t_section_64))
		: sectab_realloc(sectab, mdata->nsect * sizeof(t_section_64), old_size);
	}
	return (sectab);
}
