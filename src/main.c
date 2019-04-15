/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrari <tferrari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 13:59:57 by tferrari          #+#    #+#             */
/*   Updated: 2019/04/13 14:16:42 by tferrari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

extern t_algo			g_tab[];

t_hash		check_hash(char *algo, t_hash hash)
{
	int				i;

	i = 0;
	while (g_tab[i].algo)
	{
		if (!ft_strcmp(algo, g_tab[i].algo))
		{
			hash.index_algo = i;
			hash.len = g_tab[i].octet;
			return (hash);
		}
		i++;
	}
	hash.index_algo = -1;
	return (hash);
}

t_hash		read_file(char *path, t_hash hash)
{
	t_read		parsing;

	hash.len_octet_h = 0;
	hash.len_bytes_h = 0;
	ft_memdel((void**)&hash.data_to_h);
	parsing.fd = open(path, O_RDONLY);
	if (parsing.fd == -1)
	{
		error(path, 1);
		return (hash);
	}
	while ((parsing.ret = read(parsing.fd, parsing.buf, BUFSIZE)) > 0)
	{
		hash.data_to_h = ft_realloc_md5(hash.data_to_h, hash.len_octet_h +
												parsing.ret, hash.len_octet_h);
		hash.data_to_h = ft_memccat(hash.data_to_h, parsing.buf,
												hash.len_octet_h, parsing.ret);
		hash.len_octet_h += parsing.ret;
	}
	hash.file = path;
	g_tab[hash.index_algo].lst_hash_fonction(hash);
	return (hash);
}

t_hash		std_in(t_hash hash)
{
	uint32_t	ret;
	char		buf[BUFSIZE];

	while ((ret = read(0, buf, BUFSIZE)) > 0)
	{
		hash.data_to_h = ft_realloc_md5(hash.data_to_h, hash.len_octet_h +
														ret, hash.len_octet_h);
		hash.data_to_h = ft_memccat(hash.data_to_h, buf, hash.len_octet_h, ret);
		hash.len_octet_h += ret;
	}
	hash.option.option_std = 1;
	if (hash.option.option_p == 1)
		ft_printf("%s", (char *)hash.data_to_h);
	hash = g_tab[hash.index_algo].lst_hash_fonction(hash);
	return (hash);
}

int			main(int ac, char **av)
{
	t_hash		hash;
	int			index;

	if (ac == 1)
		return (error(NULL, 2));
	ft_bzero(&hash, sizeof(hash));
	hash = check_hash(av[1], hash);
	if (hash.index_algo == -1)
		return (error("wrong hasher", 2));
	index = 2;
	while (hash.option.close != 1)
	{
		hash = check_option(av[index], hash, &index, av);
	}
	if (ac == 2)
		hash = std_in(hash);
	while (index < ac)
	{
		hash = read_file(av[index], hash);
		index++;
	}
	return (0);
}
