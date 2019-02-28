/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrari <tferrari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 13:59:57 by tferrari          #+#    #+#             */
/*   Updated: 2019/02/28 18:49:41 by tferrari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	check_bonus(t_option *option)
{

}

int		main(int ac, char **av)
{
	t_option	*option;
	t_md5		md5;

	if (ac == 1)
		return error(("usage: ft_gssl command [command opts] [command args]"));
	else if (ac == 2)
		check_hash(option, argv[1]);
	else
		check_bonus();
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
	md5.len_bytes_h = md5.len_octet_h * 8;
	// printf("%d\n", md5.len_octet_h);
	ft_md5(md5);
	return (0);
}
