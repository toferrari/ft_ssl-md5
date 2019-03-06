/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrari <tferrari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 13:59:57 by tferrari          #+#    #+#             */
/*   Updated: 2019/03/06 15:49:13 by tferrari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

extern t_algo			g_tab[];

t_hash	check_hash(char *algo, t_hash hash)
{
	int				i;

	i = 0;
	while (g_tab[i].algo)
	{
		if (!ft_strcmp(algo, g_tab[i].algo))
		{
			hash.index_algo = i;
			return (hash);
		}
		i++;
	}
	hash.index_algo = 0;
	return (hash);
}

void	read_file(char *path, t_hash hash)
{
	t_read		parsing;

	parsing.fd = open(path, O_RDONLY);
	if (parsing.fd == -1)
		error("md5: -s: No such file or directory");
	while ((parsing.ret = read(parsing.fd, parsing.buf, BUFSIZE)) > 0)
	{
		hash.data_to_h = ft_realloc_md5(hash.data_to_h, hash.len_octet_h + parsing.ret, hash.len_octet_h);
		hash.data_to_h = ft_memccat(hash.data_to_h, parsing.buf, hash.len_octet_h, parsing.ret);
		hash.len_octet_h += parsing.ret;
	}
	g_tab[hash.index_algo].lst_hash_fonction(hash);
	// ecriture
}

int		std_in(char *algo, t_hash hash)
{
	uint32_t	ret;
	char		buf[BUFSIZE];

	ft_bzero(&hash, sizeof(hash));
	while ((ret = read(0, buf, BUFSIZE)) > 0)
	{
		hash.data_to_h = ft_realloc_md5(hash.data_to_h, hash.len_octet_h + ret, hash.len_octet_h);
		hash.data_to_h = ft_memccat(hash.data_to_h, buf, hash.len_octet_h, ret);
		hash.len_octet_h += ret;
	}
	g_tab[hash.index_algo].lst_hash_fonction(hash);
	return(0);
	//ecrire
}

int		main(int ac, char **av)
{
	t_hash		hash;
	int			index;

	if (ac == 1)
		return error(("usage: ft_ssl command [command opts] [command args]"));
	ft_bzero(&hash, sizeof(hash));
	hash = check_hash(av[1], hash);
	if (hash.index_algo == -1)
		return (error("wrong hasher"));
	if (ac == 9)
		return (std_in(av[ac - 1], hash));
	index = 2;
	while (hash.option.close != 1)
	{
		hash = check_option(av[index], hash, &index);
	}
	while (index < ac)
	{
		read_file(av[index], hash);
		index++;
	}
	return (0);
}
