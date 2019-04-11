/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrari <tferrari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 18:38:28 by tferrari          #+#    #+#             */
/*   Updated: 2019/04/11 18:37:45 by tferrari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

extern t_algo			g_tab[];

t_hash	parse_s(char *str, t_hash hash, int *index, char **av)
{
	if (*str != '\0')
	{
		hash.data_to_h = str;
		hash.file = str;
		hash.len_octet_h = ft_strlen(hash.data_to_h);
		(*index)++;
		return (g_tab[hash.index_algo].lst_hash_fonction(hash));
	}
	else
	{
		hash.data_to_h = av[*index + 1];
		if (hash.data_to_h == NULL)
		{
			(*index) += 2;
			hash.option.error_s = 1;
			hash.option.close = 1;
			return (hash);
		}
		hash.file = hash.data_to_h;
		hash.len_octet_h = ft_strlen(hash.data_to_h);
		(*index) += 2;
		return (g_tab[hash.index_algo].lst_hash_fonction(hash));
	}
	return (hash);
}

t_hash	split_check_option(t_hash hash)
{
	hash.option.close = 1;
	return (hash);
}

t_hash	check_option(char *str, t_hash hash, int *index, char **av)
{
	int i;

	if (!str || str[0] != '-')
		return (split_check_option(hash));
	i = 1;
	while (str[i])
	{
		if (str[i] == 'p')
		{
			hash.option.option_p = 1;
			hash = std_in(hash);
		}
		else if (str[i] == 'q')
			hash.option.option_q = 1;
		else if (str[i] == 'r')
			hash.option.option_r = 1;
		else if (str[i] == 's')
		{
			hash.option.option_s = 1;
			hash = parse_s(&str[i + 1], hash, index, av);
			return (hash);
		}
		i++;
	}
	(*index)++;
	return (hash);
}
