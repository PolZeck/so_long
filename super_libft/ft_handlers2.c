/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handlers2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:10:02 by pledieu           #+#    #+#             */
/*   Updated: 2025/01/23 10:24:46 by pledieu          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "super_libft.h"

int	ft_handle_unsigned(unsigned int num)
{
	char	*str;
	int		len;

	str = ft_itoa_unsigned(num);
	if (!str)
		return (0);
	len = ft_putstr(str);
	free(str);
	return (len);
}
