/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yapark <yapark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 20:47:30 by yapark            #+#    #+#             */
/*   Updated: 2021/01/28 06:56:51 by yapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_philo* init_philo(t_state *state, int idx)
{
	t_philo *ret;

	ret = (t_philo*)malloc(sizeof(t_philo));
	ret->idx = idx;
	ret->state = state;
	ret->eat_times = 0;
	ret->last_meal = get_time();
	return (ret);
}

static t_state*	init_state(int argc, char **argv)
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
	ret->philos = (t_philo**)malloc(sizeof(t_philo*) * (ret->num + 1));
	i = -1;
	while (++i < ret->num)
		ret->philos[i] = init_philo(ret, i);
	ret->philos[i] = NULL;
	return (ret);
}

static void		create_process(t_state *state)
{
	int i;

	state->start = get_time();
	i = -1;
	sem_unlink("/forks");
	sem_unlink("/write");
	sem_unlink("/dead");
	state->forks_sem = sem_open("/forks", O_CREAT | O_EXCL, S_IRWXU, state->num);
	state->write_sem = sem_open("/write", O_CREAT | O_EXCL, S_IRWXU, 1);
	state->dead_sem = sem_open("/dead", O_CREAT | O_EXCL, S_IRWXU, 0);
	while (++i < state->num)
	{
		state->philos[i]->pid = fork();
		if (state->philos[i]->pid == 0) {
			routine(state->philos[i]);
			printf("not supposed to print this!!!\n");
			exit(1);
		}
	}
	i = -1;
	
}

int				main(int argc, char **argv)
{
	t_state *state;

	state = NULL;
	if (argc != 5 && argc != 6)
		return (ft_exit(state, "errer: invalid arguments\n"));
	state = init_state(argc, argv);
	create_process(state);
	return (ft_exit(state, NULL));
}
