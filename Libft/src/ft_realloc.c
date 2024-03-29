/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrari <tferrari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 13:10:51 by tferrari          #+#    #+#             */
/*   Updated: 2019/02/25 10:39:58 by tferrari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void *new_ptr;

	if (!ptr)
		return (ft_memalloc(size));
	if (!(new_ptr = ft_memalloc(size)))
		return (NULL);
	new_ptr = memcpy(new_ptr, ptr, size);
	return (new_ptr);
}
