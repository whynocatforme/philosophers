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

	if (s->philos)
	{
		i = -1;
		while (++i < s->num)
			free(s->philos[i]);
		free(s->philos);
	}
	free(s);
}

static void	close_sem(t_state *s)
{
	sem_close(s->forks_sem);
	sem_close(s->dead_sem);
	sem_close(s->write_sem);
	sem_close(s->taking_sem);
	sem_close(s->eat_sem);
	sem_close(s->full_sem);
	sem_unlink("/forks");
	sem_unlink("/write");
	sem_unlink("/dead");
	sem_unlink("/full");
	sem_unlink("/eat");
	sem_unlink("/taking");
}

int			ft_exit(t_state *s, const char *msg)
{
	int i;

	waitpid(-1, NULL, 0);
	if (s)
	{
		i = -1;
		while (++i < s->num)
			kill(s->philos[i]->pid, SIGINT);
		close_sem(s);
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
