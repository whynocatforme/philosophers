/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yapark <yapark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 12:13:52 by yapark            #+#    #+#             */
/*   Updated: 2021/01/28 12:13:55 by yapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_philo	*init_philo(t_state *state, int idx)
{
	t_philo *ret;

	ret = (t_philo*)malloc(sizeof(t_philo));
	ret->idx = idx;
	ret->state = state;
	ret->forks[L] = !idx ? state->num - 1 : idx - 1;
	ret->forks[R] = idx;
	pthread_mutex_init(&state->forks_mtx[idx], NULL);
	ret->eat_times = 0;
	ret->last_meal = get_time();
	return (ret);
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
	ret->forks_mtx = \
		(pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) * ret->num);
	ret->philos = (t_philo**)malloc(sizeof(t_philo*) * (ret->num + 1));
	i = -1;
	while (++i < ret->num)
		ret->philos[i] = init_philo(ret, i);
	ret->philos[i] = NULL;
	return (ret);
}
