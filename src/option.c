/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrari <tferrari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 18:38:28 by tferrari          #+#    #+#             */
/*   Updated: 2019/03/08 12:33:23 by tferrari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

extern t_algo			g_tab[];

t_hash	check_option(char *str, t_hash hash, int *index)
{

	int i;
	if (!str || str[0] != '-')
	{
		hash.option.close = 1;
		return (hash);
	}
	i = 1;
	while (str[i])
	{
		if (str[i] == 'q')
			hash.option.option_q = 1;
		if (str[i] == 'r')
			hash.option.option_r = 1;
		if (str[i] == 's')
		{
			hash.option.option_s = 1;
			g_tab[hash.index_algo].lst_hash_fonction(hash);
			return (hash);
		}
		i++;
	}
	(*index)++;
	if (hash.option.option_s != 1)
		hash.option.close = 1;
	return (hash);
}
