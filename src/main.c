/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrari <tferrari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 13:59:57 by tferrari          #+#    #+#             */
/*   Updated: 2019/02/25 16:35:25 by tferrari         ###   ########.fr       */
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
	t_option	option;
	char		buf[BUFSIZE];
	void		*ret_buf;
	int			fd;
	int			ret;

	if (ac == 1)
		return error(("usage: ft_ssl command [command opts] [command args]"));

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		error("error fd");
	int total_ret = 0;
	while ((ret = read(fd, buf, BUFSIZE)) > 0)
	{
		ret_buf = ft_realloc_md5(ret_buf, total_ret + ret, total_ret);
		ret_buf = ft_memccat(ret_buf, buf, total_ret, ret);
		total_ret += ret;
	}
	md5(ret_buf, total_ret);
	return (0);
}
