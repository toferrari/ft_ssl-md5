/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrari <tferrari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 13:50:32 by tferrari          #+#    #+#             */
/*   Updated: 2019/02/26 18:20:33 by tferrari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <math.h>

# define BUFSIZE 500

typedef struct		s_option
{
	int				option_p;
	int				option_q;
	int				option_r;
	int				option_s;
}					t_option;

typedef struct		s_md5
{
	int				fd;
	int				ret;
	char			buf[BUFSIZE];
	void			*data_to_h;
	size_t			len_octet_h;
	size_t			nb_block;
	uint32_t		h_init[4];
	uint32_t		h_update[4];
	uint32_t		*r;
	uint32_t		*k;
	uint32_t		f;
	uint32_t		g;
}					t_md5;

void				ft_md5(t_md5 md5);

#endif
