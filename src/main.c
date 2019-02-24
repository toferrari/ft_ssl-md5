/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrari <tferrari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 13:59:57 by tferrari          #+#    #+#             */
/*   Updated: 2019/02/24 17:47:48 by tferrari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int error(char *str)
{
	ft_putstr(str);
	return (0);
}

int	main(int ac, char **av)
{
	if (ac == 1)
		return error(("usage: ft_ssl command [command opts] [command args]"));

	// md5("salut")
	return (0);
}
