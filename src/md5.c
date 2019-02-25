/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrari <tferrari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 16:08:06 by tferrari          #+#    #+#             */
/*   Updated: 2019/02/25 17:40:40 by tferrari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	md5(void* input_to_h, size_t len_h)
{
	int		mod_h;
	void	*input_to_h_mod;

	mod_h = len_h % 512;
	if (mod_h != 0)
	{
		input_to_h_mod = ft_realloc_md5(input_to_h, len_h - mod_h + 512, len_h);
		ft_memdel(&input_to_h);
	}
	
}
