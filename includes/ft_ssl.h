/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrari <tferrari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 13:50:32 by tferrari          #+#    #+#             */
/*   Updated: 2019/02/25 17:19:51 by tferrari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include <fcntl.h>

# define BUFSIZE 500

void	md5(void* input_to_h, size_t len_h);

typedef struct		s_option
{
	int				option_p;
	int				option_q;
	int				option_r;
	int				option_s;
}					t_option;

#endif
