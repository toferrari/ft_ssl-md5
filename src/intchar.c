/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intchar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbischof <dbischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 15:17:38 by dbischof          #+#    #+#             */
/*   Updated: 2019/03/13 18:42:10 by tferrari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	*inttochar(uint32_t *i)
{
	int j;
	int tmp;

	j = -1;
	tmp = 0;
	while (++j < 4)
	{
		tmp = tmp << 8;
		tmp |= (0xff & *i);
		*i = *i >> 8;
	}
	*i = tmp;
	return ((uint32_t *)i);
}

int		chartoint(unsigned char *t, int len)
{
	int i;
	int tmp;

	i = -1;
	tmp = 0;
	while (++i < len && i < 4)
		tmp |= t[i] << (((len - 1) * 8) - (i * 8));
	return (tmp);
}
