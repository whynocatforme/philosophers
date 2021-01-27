/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yapark <yapark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 20:47:30 by yapark            #+#    #+#             */
/*   Updated: 2021/01/28 02:25:01 by yapark           ###   ########.fr       */
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
	ret->forks = (int*)malloc(sizeof(int) * ret->num);
	ret->forks_mtx = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) * ret->num);
	ret->philos = (t_philo**)malloc(sizeof(t_philo*) * (ret->num + 1));
	i = -1;
	while (++i < ret->num)
		ret->philos[i] = init_philo(ret, i);
	ret->philos[i] = NULL;
	if (argc == 6)
		ret->times = ft_atoi(argv[4]);
	else
		ret->times = 0;
	return (ret);
}

static void		*check(void *arg)
{
	t_state *state;
	int		i;

	state = (t_state*)arg;
	pthread_mutex_lock(&state->dead_mtx);
	while (!state->dead)
	{
		pthread_mutex_unlock(&state->dead_mtx);
		i = -1;
		while (++i < state->num)
		{
			if (get_time(state->philos[i]->last_meal) > state->die)
			{
				printf("%-5d %d died\n", get_time(state->start_time), i);
				pthread_mutex_lock(&state->dead_mtx);
				state->dead++;
				pthread_mutex_unlock(&state->dead_mtx);
			}
		}
		pthread_mutex_lock(&state->dead_mtx);
	}
	pthread_mutex_unlock(&state->dead_mtx);
	return NULL;
}

static void		create_threads(t_state *state)
{
	int i;
	pthread_t dead_pid;

	gettimeofday(&state->start_time, NULL);
	i = -1;
	while (++i < state->num)
		pthread_create(&state->philos[i]->pid, NULL, &routine, state->philos[i]);
	i = -1;
	pthread_mutex_init(&state->dead_mtx, NULL);
	pthread_create(&dead_pid[i], NULL, &check, state);
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
