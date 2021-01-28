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

long			get_time(void)
{
	struct timeval now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000L + now.tv_usec / 1000L);
}

static void		*check(void *arg)
{
	t_state *s;
	int		i;

	s = (t_state*)arg;
	sem_wait(s->dead_sem);
	while (!s->dead)
	{
		sem_post(s->dead_sem);
		i = -1;
		s->full = 1;
		while (++i < s->num)
		{
			sem_wait(s->eat_sem);
			if (s->times == -1 || s->philos[i]->eat_times < s->times)
				s->full = 0;
			if (get_time() - s->philos[i]->last_meal > s->die)
				put_msg(get_time() - s->start, s->philos[i], D);
			sem_post(s->eat_sem);
		}
		sem_wait(s->dead_sem);
		if (s->full)
			s->dead++;
	}
	sem_post(s->dead_sem);
	return (NULL);
}

static void		create_threads(t_state *state)
{
	int			i;
	pthread_t	dead_pid;

	state->start = get_time();
	i = -1;
	while (++i < state->num)
		pthread_create(&state->philos[i]->pid, NULL, \
			&routine, state->philos[i]);
	pthread_create(&dead_pid, NULL, &check, state);
	pthread_join(dead_pid, NULL);
	i = -1;
	while (++i < state->num)
		pthread_join(state->philos[i]->pid, NULL);
}

int				main(int argc, char **argv)
{
	t_state *state;

	state = NULL;
	if ((argc != 5 && argc != 6) || !(state = init_state(argc, argv)))
		return (ft_exit(state, "errer: invalid arguments\n"));
	create_threads(state);
	return (ft_exit(state, NULL));
}
