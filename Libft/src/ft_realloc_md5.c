/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_md5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrari <tferrari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 16:27:52 by tferrari          #+#    #+#             */
/*   Updated: 2019/04/11 17:38:53 by tferrari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc_md5(void *ptr, size_t size, size_t size_ptr)
{
	void *new_ptr;

	if (!ptr)
		return (ft_memalloc(size));
	if (!(new_ptr = ft_memalloc(size)))
		return (NULL);
	new_ptr = ft_memcpy(new_ptr, ptr, size_ptr);
	return (new_ptr);
}
