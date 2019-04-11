/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrari <tferrari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 18:41:55 by tferrari          #+#    #+#             */
/*   Updated: 2019/04/11 18:31:05 by tferrari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int	error(char *str, int err)
{
	if (err == 1)
		ft_printf("md5: %s: No such file or directory\n", str);
	else if (err == 2)
		ft_putendl("usage: ft_ssl command [command opts] [command args]");
	else
		ft_putendl(str);
	return (0);
}
