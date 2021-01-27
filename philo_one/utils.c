/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yapark <yapark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 20:54:48 by yapark            #+#    #+#             */
/*   Updated: 2021/01/28 01:57:46 by yapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		get_time(0, struct timeval start)
{
	struct timeval now;

	gettimeofday(&now, NULL);
	return ((int)(now.tv_sec * 1000L + now.tv_usec / 1000 -\
				start.tv_sec * 1000L - start.tv_usec / 1000));
}

int		ft_strlen(const char *str)
{
	int i;

	i = -1;
	if (!str)
		return (0);
	while (str[++i])
		continue ;
	return (i);
}

int		ft_atoi(char *str)
{
	int				i;
	int				op;
	long long int	ret;

	i = 0;
	op = 1;
	ret = 0;
	while ((str[i] > 8 && str[i] < 14) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			op = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (ret > 2147483647 && op == 1)
			return (-1);
		if (ret > 2147483648 && op == -1)
			return (0);
		ret = ret * 10 + (str[i] - '0');
		i++;
	}
	return ((int)(ret * op));
}
