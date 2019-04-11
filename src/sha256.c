/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrari <tferrari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 10:59:01 by tferrari          #+#    #+#             */
/*   Updated: 2019/04/10 17:16:23 by tferrari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static uint32_t g_k[64] = {0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01,
	0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa,
	0x5cb0a9dc, 0x76f988da, 0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138,
	0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624,
	0xf40e3585, 0x106aa070, 0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f,
	0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

t_hash	init_variable_h_sha256(t_hash hash)
{
	hash.h_init[0] = 0x6a09e667;
	hash.h_init[1] = 0xbb67ae85;
	hash.h_init[2] = 0x3c6ef372;
	hash.h_init[3] = 0xa54ff53a;
	hash.h_init[4] = 0x510e527f;
	hash.h_init[5] = 0x9b05688c;
	hash.h_init[6] = 0x1f83d9ab;
	hash.h_init[7] = 0x5be0cd19;
	return (hash);
}

t_hash	compute_sha256(t_hash hash, size_t i, uint32_t *w)
{
	uint32_t s1;
	uint32_t ch;
	uint32_t tmp;
	uint32_t s0;
	uint32_t maj;

	s1 = R_ROT(hash.h_update[4], 6) ^ R_ROT(hash.h_update[4], 11) ^ \
													R_ROT(hash.h_update[4], 25);
	ch = (hash.h_update[4] & hash.h_update[5]) ^ (~hash.h_update[4] & \
															hash.h_update[6]);
	tmp = hash.h_update[7] + s1 + ch + g_k[i] + w[i];
	s0 = R_ROT(hash.h_update[0], 2) ^ R_ROT(hash.h_update[0], 13) ^ \
													R_ROT(hash.h_update[0], 22);
	maj = (hash.h_update[0] & hash.h_update[1]) ^ (hash.h_update[0] & \
					hash.h_update[2]) ^ (hash.h_update[1] & hash.h_update[2]);
	hash.h_update[7] = hash.h_update[6];
	hash.h_update[6] = hash.h_update[5];
	hash.h_update[5] = hash.h_update[4];
	hash.h_update[4] = hash.h_update[3] + tmp;
	hash.h_update[3] = hash.h_update[2];
	hash.h_update[2] = hash.h_update[1];
	hash.h_update[1] = hash.h_update[0];
	hash.h_update[0] = tmp + s0 + maj;
	return (hash);
}

t_hash	calculate_h_sha256(t_hash hash, uint8_t *m)
{
	int			i;
	size_t		j;
	uint32_t	w[64];

	i = -1;
	j = 0;
	ft_bzero(&w, sizeof(w));
	while (++i < 16)
	{
		w[i] = ((m[j]) << 24) | ((m[j + 1]) << 16) |\
			((m[j + 2]) << 8) | ((m[j + 3]));
		j += 4;
	}
	i = 15;
	while (++i < 64)
		w[i] = w[i - 16] + ((R_ROT(w[i - 15], 7)) ^ (R_ROT(w[i - 15], 18)) ^ \
		(R_SFT(w[i - 15], 3))) + w[i - 7] + ((R_ROT(w[i - 2], 17)) ^ \
		(R_ROT(w[i - 2], 19)) ^ (R_SFT(w[i - 2], 10)));
	i = -1;
	while (++i < 64)
		hash = compute_sha256(hash, i, w);
	hash = update_h(hash, 8);
	return (hash);
}

t_hash	create_padding_sha256(t_hash hash)
{
	size_t		mod_h;
	uint64_t	size_hash;

	mod_h = hash.len_octet_h % 64;
	size_hash = hash.len_octet_h * 8;
	if (mod_h < 56)
		hash.data_to_h = ft_realloc_md5(hash.data_to_h,
							hash.len_octet_h - mod_h + 64, hash.len_octet_h);
	else
		hash.data_to_h = ft_realloc_md5(hash.data_to_h,
							hash.len_octet_h - mod_h + 128, hash.len_octet_h);
	((char *)hash.data_to_h)[hash.len_octet_h] = 0x80;
	hash.len_octet_h += (mod_h < 56) ? (64 - mod_h) : (128 - mod_h);
	inttochar_64(&size_hash);
	hash.data_to_h = ft_memccat(hash.data_to_h, (void *)&size_hash,
													(hash.len_octet_h - 8), 8);
	return (hash);
}

t_hash	sha256(t_hash hash)
{
	void		*ptr_save;
	uint8_t		*hashing;

	hash = create_padding_sha256(hash);
	hash = init_variable_h_sha256(hash);
	hashing = (uint8_t*)hash.data_to_h;
	ptr_save = hash.data_to_h;
	while (0 < hash.len_octet_h)
	{
		ft_memcpy(hash.h_update, hash.h_init, sizeof(hash.h_init));
		hash = calculate_h_sha256(hash, hashing);
		hash.len_octet_h -= 64;
		hashing = hashing + 64;
	}
	if (ptr_save)
		ft_memdel((void **)&ptr_save);
	return (write_hash(hash));
}
