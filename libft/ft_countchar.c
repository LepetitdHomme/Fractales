/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/15 16:36:50 by csellier          #+#    #+#             */
/*   Updated: 2017/04/12 13:40:22 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_countchar(char *s, char c)
{
	int i;
	int k;

	i = 0;
	k = 0;
	while (s && s[i])
	{
		if (s[i] == c)
			k++;
		i++;
	}
	return (k);
}
