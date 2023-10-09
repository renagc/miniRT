/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_dbl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:38:35 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/10/06 18:55:38 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	cond(const char **str, int *mn)
{
	while ((**str >= 9 && **str <= 13) || **str == 32)
		(*str)++;
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			*mn = -(*mn);
		(*str)++;
	}
}

static void	loop(const char **str, int *decimal, double *res, double *div)
{
	while (**str)
	{
		if (**str == '.')
		{
			*decimal = 1;
			(*str)++;
		}
		if (*decimal)
		{
			*res = *res + (**str - 48) / *div;
			*div *= 10.0;
		}
		else
			*res = *res * 10.0 + (**str - 48);
		(*str)++;
	}
}

double	ft_atoi_dbl(const char *str)
{
	double	res;
	int		decimal;
	double	div;
	int		mn;

	mn = 1;
	res = 0.0;
	div = 10.0;
	decimal = 0;
	cond(&str, &mn);
	loop(&str, &decimal, &res, &div);
	return (res * mn);
}
