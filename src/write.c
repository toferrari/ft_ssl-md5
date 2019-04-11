/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrari <tferrari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 16:03:18 by tferrari          #+#    #+#             */
/*   Updated: 2019/04/11 17:43:18 by tferrari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#define OPTION_P hash.option.option_p
#define OPTION_Q hash.option.option_q
#define OPTION_R hash.option.option_r
#define OPTION_S hash.option.option_s
#define OPTION_STD hash.option.option_std

extern t_algo			g_tab[];

void		reverse_write(t_hash hash, size_t i)
{
	char	*tmp;

	tmp = NULL;
	if (hash.index_algo == 0)
		inttochar(&hash.h_init[i]);
	tmp = ft_itoa_base64_md5(hash.h_init[i], 16);
	ft_printf("%s", tmp);
	ft_memdel((void**)&tmp);
}

t_hash		write_hash(t_hash hash)
{
	size_t		i;

	i = -1;
	if (OPTION_P == 0 && OPTION_Q == 0 && OPTION_R == 0 && OPTION_STD != 1)
		ft_printf("%s (%s) = ", (g_tab[hash.index_algo].upper), hash.file);
	while (++i < hash.len)
		reverse_write(hash, i);
	if (OPTION_R == 1 && OPTION_Q == 0 && OPTION_P == 0)
		ft_printf(" %s", hash.file);
	write(1, "\n", 1);
	OPTION_P = 0;
	OPTION_STD = 0;
	return (hash);
}
