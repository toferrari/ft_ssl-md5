/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrari <tferrari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 13:59:57 by tferrari          #+#    #+#             */
/*   Updated: 2019/02/26 19:21:23 by tferrari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int	error(char *str)
{
	ft_putstr(str);
	return (0);
}

int	main(int ac, char **av)
{
	t_option	option;
	t_md5		md5;

	if (ac == 1)
		return error(("usage: ft_ssl command [command opts] [command args]"));
	ft_bzero(&md5, sizeof(md5));
	md5.fd = open(av[1], O_RDONLY);
	if (md5.fd == -1)
		error("error md5.fd");
	while ((md5.ret = read(md5.fd, md5.buf, BUFSIZE)) > 0)
	{
		md5.data_to_h = ft_realloc_md5(md5.data_to_h, md5.len_octet_h + md5.ret, md5.len_octet_h);
		md5.data_to_h = ft_memccat(md5.data_to_h, md5.buf, md5.len_octet_h, md5.ret);
		md5.len_octet_h += md5.ret;
	}
	// md5(md5.data_to_h, md5.len_octet_h);
	return (0);
}
