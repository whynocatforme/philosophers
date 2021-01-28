/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yapark <yapark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 20:47:30 by yapark            #+#    #+#             */
/*   Updated: 2021/01/28 10:02:47 by yapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long			get_time(void)
{
	struct timeval now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000L + now.tv_usec / 1000L);
}

static void		*full_check(void *arg)
{
	t_state	*s;
	int		i;

	s = (t_state*)arg;
	i = -1;
	while (++i < s->num)
		sem_wait(s->full_sem);
	i = -1;
	while (++i < s->num)
		kill(s->philos[i]->pid, SIGINT);
	return (NULL);
}

static void		create_process(t_state *state)
{
	int			i;
	int			is_parent;
	pthread_t	full_pid;

	state->start = get_time();
	i = -1;
	is_parent = 1;
	pthread_create(&full_pid, NULL, &full_check, state);
	while (++i < state->num)
	{
		state->philos[i]->pid = fork();
		if (state->philos[i]->pid == 0)
		{
			is_parent = 0;
			routine(state->philos[i]);
			exit(1);
		}
	}
	if (is_parent)
		pthread_join(full_pid, NULL);
}

int				main(int argc, char **argv)
{
	t_state *state;

	state = NULL;
	if ((argc != 5 && argc != 6) || !(state = init_state(argc, argv)))
		return (ft_exit(state, "errer: invalid arguments\n"));
	create_process(state);
	return (ft_exit(state, NULL));
}
