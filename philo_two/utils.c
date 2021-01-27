/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yapark <yapark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 20:54:48 by yapark            #+#    #+#             */
/*   Updated: 2021/01/28 05:58:26 by yapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>

void		ft_sleep(long time)
{
	long start;
	long now;

	start = get_time();
	while (1)
	{
		now = get_time();
		if (now - start > time)
			return ;
		usleep(100);
	}
}

static void	ft_putnbr(int n)
{
	unsigned int	n2;
	char			c;

	if (n < 0)
		write(1, "-", 1);
	n2 = n < 0 ? (unsigned int)(n * (-1)) : (unsigned int)n;
	if (n2 >= 10)
		ft_putnbr(n2 / 10);
	c = n2 % 10 + '0';
	write(1, &c, 1);
}

void	put_msg(long time, t_philo *philo, const char *act)
{
	sem_wait(philo->state->dead_sem);
	if (philo->state->dead)
	{
		sem_post(philo->state->dead_sem);
		return ;
	}
	sem_post(philo->state->dead_sem);
	sem_wait(philo->state->write_sem);
	ft_putnbr((int)time);
	write(1, " ", 1);
	ft_putnbr(philo->idx + 1);
	write(1, act, ft_strlen(act));
	sem_post(philo->state->write_sem);
}

long	get_time(void)
{
	struct timeval now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000L + now.tv_usec / 1000L);
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
