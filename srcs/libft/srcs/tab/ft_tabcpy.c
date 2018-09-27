/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tabcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <nbouchin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 16:11:07 by nbouchin          #+#    #+#             */
/*   Updated: 2017/05/23 16:48:38 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		tab_count(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char			**ft_tabcpy(char **tab)
{
	char		**ret;
	int			i;
	int			y;
	int			size;

	i = 0;
	y = 0;
	size = tab_count(tab);
	ret = (char**)ft_memalloc(sizeof(char*) * (size + 1));
	while (tab[i])
		ret[i++] = ft_strdup(tab[y++]);
	return (ret);
}
