/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 09:22:50 by nbouchin          #+#    #+#             */
/*   Updated: 2018/10/18 09:55:33 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_nm.h"

int		fat_header(t_fat_header *fat_header)
{
	t_fat_arch	*fat_arch;

	fat_arch = (t_fat_arch*)(fat_header + 1);
	return (1);
}
