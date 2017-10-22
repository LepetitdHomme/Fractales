/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchri.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/21 19:37:22 by csellier          #+#    #+#             */
/*   Updated: 2017/04/12 13:44:25 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strchri(const char *s, int c)
{
	int i;

	i = -1;
	if (s == NULL)
		return (-1);
	if ((char)c == '\0')
		return (ft_strlen((const char *)s));
	while (s[++i] != '\0')
	{
		if ((char)c == s[i])
			return (i);
	}
	return (-1);
}
