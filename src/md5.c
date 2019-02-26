/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrari <tferrari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 16:08:06 by tferrari          #+#    #+#             */
/*   Updated: 2019/02/26 19:07:07 by tferrari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static uint32_t	g_r[64] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12,
	17, 22, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 4, 11, 16,
	23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6, 10, 15, 21, 6, 10, 15,
	21, 6, 10, 15, 21, 6, 10, 15, 21};

static uint32_t g_k[64] = {	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501, 0x698098d8, 0x8b44f7af,
	0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453,
	0xd8a1e681, 0xe7d3fbc8, 0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a, 0xfffa3942, 0x8771f681,
	0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5,
	0x1fa27cf8, 0xc4ac5665, 0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0,
	0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391,};

t_md5	init_variable_h(t_md5 md5)
{
	md5.h_init[0] = 0x67452301;
	md5.h_init[1] = 0xEFCDAB89;
	md5.h_init[2] = 0x98BADCFE;
	md5.h_init[3] = 0x10325476;
	md5.r = g_r;
	md5.k = g_k;
	return (md5);
}

t_md5	init_update_h(t_md5 md5)
{
	md5.h_update[0] = md5.h_init[0];
	md5.h_update[1] = md5.h_init[1];
	md5.h_update[2] = md5.h_init[2];
	md5.h_update[3] = md5.h_init[3];
	return (md5);
}

t_md5	update_h_update(size_t i, t_md5 md5)
{
	size_t tmp;
	int *w;

	tmp = md5.h_update[3];
	md5.h_update[2] = md5.h_update[2];
	md5.h_update[1] = ((md5.h_update[0] + md5.f + md5.k[i] + w[md5.g]) <<
													md5.r[i]) + md5.h_update[2];
	md5.h_update[0] = tmp;
	return (md5);
}

t_md5	update_h(t_md5 md5)
{
	md5.h_init[0] += md5.h_update[0];
	md5.h_init[1] += md5.h_update[1];
	md5.h_init[2] += md5.h_update[2];
	md5.h_init[3] += md5.h_update[3];
	return (md5);
}

t_md5	calculate_h(t_md5 md5)
{
	size_t	i;
	size_t	f;
	size_t	g;

	i = 0;
	while (i < 64)
	{
		if (i <= 15)
		{
			md5.f = (md5.h_update[1] & md5.h_update[2]) |
											((~md5.h_update[1]) & md5.h_update[3]);
			md5.g = i;
		}
		else if (i > 15 && i <= 31)
		{
			md5.f = (md5.h_update[3] & md5.h_update[1]) |
											((~md5.h_update[3]) & md5.h_update[2]);
			md5.g = (5 * i + 1) % 16;
		}
		else if (i > 31 && i <= 47)
		{
			md5.f = md5.h_update[1] ^ md5.h_update[2] ^ md5.h_update[3];
			md5.g = (3 * i + 5) % 16;
		}
		else if (i > 47 && i <= 63)
		{
			md5.f = md5.h_update[2] ^ (md5.h_update[1] | ~md5.h_update[3]);
			md5.g = (7 * i) % 16;
		}
		md5 = update_h_update(i, md5);
		i++;
	}
	return (md5);
}

void	ft_md5(t_md5 md5)
{
	size_t		mod_h;
	size_t		loop;

	mod_h = md5.len_octet_h % 64;
	md5 = init_variable_h(md5);
	if (mod_h != 0)
	{
		md5.data_to_h = ft_realloc_md5(md5.data_to_h,
								md5.len_octet_h - mod_h + 64, md5.len_octet_h);
		((char *)md5.data_to_h)[md5.len_octet_h] = 1;
		md5.len_octet_h += (64 - mod_h);
		// write(1, md5.data_to_h, md5.len_octet_h);
	}
	md5.nb_block = md5.len_octet_h / 64;
	loop = 0;
	while (loop < md5.nb_block)
	{
		md5 = init_update_h(md5);
		md5 = calculate_h(md5);
		md5 = update_h(md5);
		loop++;
	}
}
