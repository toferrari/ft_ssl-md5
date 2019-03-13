/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrari <tferrari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 16:08:06 by tferrari          #+#    #+#             */
/*   Updated: 2019/03/13 18:18:32 by tferrari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static uint32_t	g_r[64] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12,
	17, 22, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 4, 11, 16,
	23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6, 10, 15, 21, 6, 10, 15,
	21, 6, 10, 15, 21, 6, 10, 15, 21};

static uint32_t g_k[64] = { 0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501, 0x698098d8, 0x8b44f7af,
	0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453,
	0xd8a1e681, 0xe7d3fbc8, 0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a, 0xfffa3942, 0x8771f681,
	0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5,
	0x1fa27cf8, 0xc4ac5665, 0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0,
	0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

t_hash	init_variable_h_md5(t_hash hash)
{
	hash.h_init[0] = 0x67452301;
	hash.h_init[1] = 0xEFCDAB89;
	hash.h_init[2] = 0x98BADCFE;
	hash.h_init[3] = 0x10325476;
	return (hash);
}

t_hash	compute(t_hash hash, size_t i, uint32_t *f, uint32_t *g)
{
	if (i <= 15)
	{
		*f = (hash.h_update[1] & hash.h_update[2]) |
									((~hash.h_update[1]) & hash.h_update[3]);
		*g = i;
	}
	else if (i <= 31)
	{
		*f = (hash.h_update[3] & hash.h_update[1]) |
									((~hash.h_update[3]) & hash.h_update[2]);
		*g = (5 * i + 1) % 16;
	}
	else if (i <= 47)
	{
		*f = hash.h_update[1] ^ hash.h_update[2] ^ hash.h_update[3];
		*g = (3 * i + 5) % 16;
	}
	else
	{
		*f = hash.h_update[2] ^ (hash.h_update[1] | ~hash.h_update[3]);
		*g = (7 * i) % 16;
	}
	return (hash);
}

t_hash	calculate_h(t_hash hash, uint32_t *w)
{
	size_t		i;
	uint32_t	f;
	uint32_t	g;

	i = 0;
	f = 0;
	g = 0;
	while (i < 64)
	{
		hash = compute(hash, i, &f, &g);
		f = f + hash.h_update[0] + g_k[i] + w[g];
		hash.h_update[0] = hash.h_update[3];
		hash.h_update[3] = hash.h_update[2];
		hash.h_update[2] = hash.h_update[1];
		hash.h_update[1] = hash.h_update[1] + L_ROT(f, g_r[i]);
		i++;
	}
	hash = update_h(hash, 4);
	return (hash);
}

t_hash	create_padding_md5(t_hash hash)
{
	size_t		mod_h;
	uint32_t	size_hash;

	mod_h = hash.len_octet_h % 64;
	size_hash = hash.len_octet_h * 8;
	// printf("mod =% zu\n", mod_h);
	if (mod_h < 56)
		hash.data_to_h = ft_realloc_md5(hash.data_to_h,
							hash.len_octet_h - mod_h + 64, hash.len_octet_h);
	else
		hash.data_to_h = ft_realloc_md5(hash.data_to_h,
							hash.len_octet_h - mod_h + 128, hash.len_octet_h);
	((char *)hash.data_to_h)[hash.len_octet_h] = 0x80;
	hash.len_octet_h += (mod_h < 56) ? (64 - mod_h) : (128 - mod_h);
	hash.data_to_h = ft_memccat(hash.data_to_h, (void *)&size_hash,
													(hash.len_octet_h - 8), 4);
	// printf("len =% zu\n", hash.len_octet_h);
	return (hash);
}

void	md5(t_hash hash)
{
	void		*ptr_save;
	uint32_t	*hashing;

	hash = create_padding_md5(hash);
	hash = init_variable_h_md5(hash);
	hashing = (uint32_t*)hash.data_to_h;
	ptr_save = hash.data_to_h;
	while (0 < hash.len_octet_h)
	{
		ft_memcpy(hash.h_update, hash.h_init, sizeof(hash.h_init));
		hash = calculate_h(hash, hashing);
		hash.len_octet_h -= 64;
		hashing = hashing + 16;
	}
	ft_memdel((void **)&ptr_save);
	write_hash(hash);
}
