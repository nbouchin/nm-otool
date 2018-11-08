/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 13:23:33 by nbouchin          #+#    #+#             */
/*   Updated: 2018/11/08 13:24:02 by nbouchin         ###   ########.fr       */
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

uint32_t	swi(uint32_t x)
{
	return ((((((x) & 0xff000000) >> 24) |
					(((x) & 0x00ff0000) >> 8) |
					(((x) & 0x0000ff00) << 8) |
					(((x) & 0x000000ff) << 24))));
}
