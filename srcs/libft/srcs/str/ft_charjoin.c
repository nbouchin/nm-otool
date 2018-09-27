/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <nbouchin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/30 15:25:32 by nbouchin          #+#    #+#             */
/*   Updated: 2017/05/30 15:28:03 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_charjoin(char const *str, char c)
{
	char	*result;

	if (!str || !c)
		return (NULL);
	if (!(result = ft_strnew(ft_strlen(str) + 1)))
		return (NULL);
	ft_strcpy(result, str);
	result[ft_strlen(str)] = c;
	return (result);
}
