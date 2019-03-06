/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrari <tferrari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 16:03:18 by tferrari          #+#    #+#             */
/*   Updated: 2019/03/06 17:10:41 by tferrari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		write_hash(t_hash hash)
{
	int i = -1;
	char *tmp;
	while (++i < 4)
	{
		tmp = ft_itoa_base(inttochar(hash.h_init[i]), 16);
		ft_printf("%s", tmp);
		ft_memdel((void**)&tmp);
	}
	write(1, "\n", 1);
	// char *test_p[16];
	// char *tmp;
	// tmp = inttochar(hash.h_init[0]);
	// test_p[0] = hash.h_init[0];
	// test_p[4] = hash.h_init[1];
	// test_p[8] = hash.h_init[2];
	// test_p[12] = hash.h_init[3];
	// ft_printf("%s%s%s%s\n", ft_itoa_base(hash.h_init[0], 16), ft_itoa_base(hash.h_init[1], 16), ft_itoa_base(hash.h_init[2], 16), ft_itoa_base(hash.h_init[3], 16));
	// ft_printf("%s\n", ft_itoa_base(test_p, 16));
	// ft_printf("%x%x%x%x\n",hash.h_init[0], hash.h_init[1], hash.h_init[2], hash.h_init[3]);

}
