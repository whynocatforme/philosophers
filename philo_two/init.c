/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yapark <yapark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 12:54:31 by yapark            #+#    #+#             */
/*   Updated: 2021/01/28 12:54:33 by yapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_philo	*init_philo(t_state *state, int idx)
{
	t_philo *ret;

	ret = (t_philo*)malloc(sizeof(t_philo));
	ret->idx = idx;
	ret->state = state;
	ret->eat_times = 0;
	ret->last_meal = get_time();
	return (ret);
}

static void		init_sem(t_state *state)
{
	sem_unlink("/forks");
	sem_unlink("/write");
	sem_unlink("/dead");
	sem_unlink("/taking");
	sem_unlink("/eat");
	state->forks_sem = sem_open("/forks", O_CREAT | O_EXCL, S_IRWXU, \
		state->num);
	state->write_sem = sem_open("/write", O_CREAT | O_EXCL, S_IRWXU, 1);
	state->dead_sem = sem_open("/dead", O_CREAT | O_EXCL, S_IRWXU, 1);
	state->taking_sem = sem_open("/taking", O_CREAT | O_EXCL, S_IRWXU, 1);
	state->eat_sem = sem_open("/eat", O_CREAT | O_EXCL, S_IRWXU, 1);
}

t_state			*init_state(int argc, char **argv)
{
	t_state	*ret;
	int		i;

	ret = (t_state*)malloc(sizeof(t_state));
	ret->dead = 0;
	ret->num = ft_atoi(argv[1]);
	ret->die = ft_atoi(argv[2]);
	ret->eat = ft_atoi(argv[3]);
	ret->sleep = ft_atoi(argv[4]);
	ret->times = argc == 5 ? -1 : ft_atoi(argv[5]);
	if (!ret->num || !ret->die || !ret->eat || !ret->sleep || !ret->times)
	{
		free(ret);
		return (NULL);
	}
	ret->philos = \
		(t_philo**)malloc(sizeof(t_philo*) * (ret->num + 1));
	i = -1;
	while (++i < ret->num)
		ret->philos[i] = init_philo(ret, i);
	ret->philos[i] = NULL;
	init_sem(ret);
	return (ret);
}
