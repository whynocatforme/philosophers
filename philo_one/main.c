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

static void		*check_dead(void *arg)
{
	t_state *s;
	int		i;

	s = (t_state*)arg;
	pthread_mutex_lock(&s->dead_mtx);
	while (!s->dead)
	{
		pthread_mutex_unlock(&s->dead_mtx);
		i = -1;
		s->full = 1;
		while (++i < s->num)
		{
			pthread_mutex_lock(&s->eat_mtx);
			if (s->times == -1 || s->philos[i]->eat_times < s->times)
				s->full = 0;
			if (get_time() - s->philos[i]->last_meal > s->die)
				put_msg(get_time() - s->start, s->philos[i], D);
			pthread_mutex_unlock(&s->eat_mtx);
		}
		pthread_mutex_lock(&s->dead_mtx);
		if (s->full)
			s->dead++;
	}
	pthread_mutex_unlock(&s->dead_mtx);
	return (NULL);
}

static void		create_threads(t_state *state)
{
	int			i;
	pthread_t	dead_pid;

	state->start = get_time();
	i = -1;
	pthread_mutex_init(&state->write_mtx, NULL);
	pthread_mutex_init(&state->dead_mtx, NULL);
	pthread_mutex_init(&state->eat_mtx, NULL);
	pthread_mutex_init(&state->taking_forks, NULL);
	while (++i < state->num)
		pthread_create(&state->philos[i]->pid, NULL, \
		&routine, state->philos[i]);
	pthread_create(&dead_pid, NULL, &check_dead, state);
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
