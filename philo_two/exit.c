/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yapark <yapark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 20:51:44 by yapark            #+#    #+#             */
/*   Updated: 2021/01/28 00:56:18 by yapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	free_state(t_state *s)
{
	int i;

	if (s->forks)
		free(s->forks);
	if (s->forks_mtx)
		free(s->forks_mtx);
	if (s->philos)
	{
		i = -1;
		while (++i < s->num)
			free(s->philos[i]);
		free(s->philos);
	}
	free(s);
}

static void	destroy_mutex(t_state *s)
{
	int i;

	pthread_mutex_destroy(&s->mtx);
	pthread_mutex_destroy(&s->dead_mtx);
	pthread_mutex_destroy(&s->write_mtx);
	i = -1;
	while (++i < s->num)
		pthread_mutex_destroy(&s->forks_mtx[i]);
}

int			ft_exit(t_state *s, const char *msg)
{
	if (s)
	{
		destroy_mutex(s);
		free_state(s);
	}
	if (msg)
	{
		write(1, msg, ft_strlen(msg));
		return (1);
	}
	else
		return (0);
}
