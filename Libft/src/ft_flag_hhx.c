/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag_hhx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrari <tferrari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 14:18:50 by tferrari          #+#    #+#             */
/*   Updated: 2017/03/24 17:59:44 by tferrari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static void	ft_moin_on(char **str, t_print ptf, int nb, int len)
{
	unsigned int unb;

	unb = (nb < 0) ? (unsigned int)-nb : nb;
	*str = (nb < 0) ? ft_strcat(*str, "-") : *str;
	if (ptf.accuracy > 0)
		*str = ft_strnccat(*str, '0', ptf.accuracy - ft_intlen_base(unb, 16));
	*str = (ptf.c == 'X') ? ft_strcat(*str, ft_strupper(ptf.tmp)) :
	ft_strcat(*str, ptf.tmp);
	if (ptf.accuracy == 0)
		*str = ft_strnccat(*str, ' ', ptf.zero - ft_intlen_base(unb, 16) - len);
	else
		*str = ft_strnccat(*str, ' ', ptf.zero - ptf.accuracy - len);
}

static void	ft_moin_off(char **str, t_print ptf, int nb, int len)
{
	unsigned int unb;

	unb = (nb < 0) ? (unsigned int)-nb : nb;
	if (ptf.accuracy == 0)
		*str = ft_strnccat(*str, ' ', ptf.zero - ft_intlen_base(unb, 16) - len);
	else
		*str = ft_strnccat(*str, ' ', ptf.zero - ptf.accuracy - len);
	*str = (nb < 0) ? ft_strcat(*str, "-") : *str;
	*str = ft_strnccat(*str, '0', ptf.accuracy - ft_intlen_base(unb, 16) - len);
	*str = (ptf.c == 'X') ? ft_strcat(*str, ft_strupper(ptf.tmp)) :
	ft_strcat(*str, ptf.tmp);
}

static int	ft_convert_len_acc(t_print ptf, int nb, int len_nb)
{
	int len;

	len = len_nb;
	if (ptf.zero > len_nb || ptf.accuracy > len_nb)
		len = (ptf.zero > ptf.accuracy) ? ptf.zero : ptf.accuracy;
	else if ((ptf.space == 1 || ptf.plus == 1) && nb >= 0)
		len++;
	return (len);
}

int			ft_flag_hhx(t_print ptf, unsigned char nb, char **str)
{
	int				len;
	int				i;
	int				len_nb;
	unsigned int	unb;

	unb = (nb < 0) ? (unsigned int)-nb : nb;
	len_nb = ft_intlen_base(nb, 16);
	len = ft_convert_len_acc(ptf, nb, len_nb);
	if (ft_realloc_adr_p(str, len, ptf.ret) == 0 ||
	!(ptf.tmp = ft_itoa_base(nb, 16)))
		return (0);
	i = ft_convert_signe(str, ptf, nb);
	i += (nb < 0) ? 1 : 0;
	if (ptf.moins == 1)
		ft_moin_on(str, ptf, nb, i);
	else
		ft_moin_off(str, ptf, nb, i);
	ft_memdel((void **)&ptf.tmp);
	return (len);
}
