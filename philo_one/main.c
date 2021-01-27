/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yapark <yapark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 20:47:30 by yapark            #+#    #+#             */
/*   Updated: 2021/01/28 05:17:12 by yapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_philo* init_philo(t_state *state, int idx)
{
	t_philo *ret;

	ret = (t_philo*)malloc(sizeof(t_philo));
	ret->idx = idx;
	ret->state = state;
	ret->forks[L] = !idx? state->num - 1 : idx - 1;
	ret->forks[R] = idx;
	pthread_mutex_init(&state->forks_mtx[idx], NULL);
	state->forks[idx] = -1;
	ret->eat_times = 0;
	ret->last_meal = get_time();
	return (ret);
}

static t_state*	init_state(int argc, char **argv)
{
	t_state	*ret;
	int		i;

	ret = (t_state*)malloc(sizeof(t_state));
	pthread_mutex_init(&ret->mtx, NULL);
	ret->dead = 0;
	ret->num = ft_atoi(argv[1]);
	ret->die = ft_atoi(argv[2]);
	ret->eat = ft_atoi(argv[3]);
	ret->sleep = ft_atoi(argv[4]);
	ret->times = argc == 5 ? -1 : ft_atoi(argv[5]);
	ret->forks = (int*)malloc(sizeof(int) * ret->num);
	ret->forks_mtx = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) * ret->num);
	ret->philos = (t_philo**)malloc(sizeof(t_philo*) * (ret->num + 1));
	i = -1;
	while (++i < ret->num)
		ret->philos[i] = init_philo(ret, i);
	ret->philos[i] = NULL;
	return (ret);
}

static void		*check(void *arg)
{
	t_state *state;
	int		i;
	int		is_full;

	state = (t_state*)arg;
	pthread_mutex_lock(&state->dead_mtx);
	while (!state->dead)
	{
		is_full = state->times == -1 ? 0 : 1;
		pthread_mutex_unlock(&state->dead_mtx);
		i = -1;
		while (++i < state->num)
		{
			pthread_mutex_lock(&state->eat_mtx);
			if (state->philos[i]->eat_times < state->times)
				is_full = 0;
			pthread_mutex_unlock(&state->eat_mtx);
			if (get_time() - state->philos[i]->last_meal > state->die)
			{
				put_msg(get_time() - state->start, state->philos[i], D);
				pthread_mutex_lock(&state->dead_mtx);
				state->dead++;
				pthread_mutex_unlock(&state->dead_mtx);
			}
		}
		pthread_mutex_lock(&state->dead_mtx);
		if (is_full)
			state->dead++;
	}
	pthread_mutex_unlock(&state->dead_mtx);
	return NULL;
}

static void		create_threads(t_state *state)
{
	int i;
	pthread_t dead_pid;

	state->start = get_time();
	i = -1;
	pthread_mutex_init(&state->write_mtx, NULL);
	pthread_mutex_init(&state->dead_mtx, NULL);
	pthread_mutex_init(&state->eat_mtx, NULL);
	while (++i < state->num)
		pthread_create(&state->philos[i]->pid, NULL, &routine, state->philos[i]);
	i = -1;
	//pthread_create(&dead_pid, NULL, &check, state);
	//pthread_join(dead_pid, NULL);
	while (++i < state->num)
		pthread_join(state->philos[i]->pid, NULL);
}

int				main(int argc, char **argv)
{
	t_state *state;

	state = NULL;
	if (argc != 5 && argc != 6)
		return (ft_exit(state, "errer: invalid arguments\n"));
	state = init_state(argc, argv);
	create_threads(state);
	return (ft_exit(state, NULL));
}
