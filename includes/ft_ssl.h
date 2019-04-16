/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrari <tferrari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 13:50:32 by tferrari          #+#    #+#             */
/*   Updated: 2019/04/16 15:46:48 by tferrari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>

# define BUFSIZE 1024
# define L_ROT(X, C) ((X << C) | (X >> (32 - C)))
# define R_ROT(X, C) ((X >> C) | (X << (32 - C)))
# define L_SFT(X, C) (X << C)
# define R_SFT(X, C) (X >> C)

typedef struct		s_read
{
	int				fd;
	int				ret;
	char			buf[BUFSIZE];
}					t_read;

typedef struct		s_option
{
	int				option_p;
	int				option_q;
	int				option_r;
	int				option_s;
	int				error_s;
	int				option_std;
	int				close;
}					t_option;

typedef struct		s_hash
{
	int				index_algo;
	size_t			len;
	char			*file;
	void			*data_to_h;
	size_t			len_octet_h;
	size_t			len_bytes_h;
	uint32_t		h_init[8];
	uint32_t		h_update[8];
	t_option		option;

}					t_hash;

typedef struct		s_algo
{
	char			*algo;
	t_hash			(*lst_hash_fonction)(t_hash);
	size_t			octet;
	char			*upper;
}					t_algo;

t_hash				md5(t_hash md5);
t_hash				sha256(t_hash hash);
t_hash				sha224(t_hash hash);
int					error(char *str, int err);
t_hash				check_option(char *str, t_hash hash, int *index, char **av);
t_hash				write_hash(t_hash hash);
void				*inttochar(uint32_t *i);
void				*inttochar_64(uint64_t *i);
t_hash				std_in(t_hash hash);
t_hash				update_h(t_hash hash, size_t len);

static t_algo	g_tab[] = {
	{"md5", md5, 4, "MD5"},
	{"sha256", sha256, 8, "SHA256"},
	{"sha224", sha224, 7, "SHA224"},
	{NULL, NULL, 0, NULL}
};

#endif
