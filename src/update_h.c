/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_h.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrari <tferrari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 18:39:45 by tferrari          #+#    #+#             */
/*   Updated: 2019/03/07 18:41:34 by tferrari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

t_hash		update_h(t_hash hash, size_t len)
{
	size_t i;

	i = 0;
	while (i < len)
	{
		hash.h_init[i] += hash.h_update[i];
		i++;
	}
	return (hash);
}
