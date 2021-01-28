/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yapark <yapark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 22:12:14 by yapark            #+#    #+#             */
/*   Updated: 2021/01/28 06:56:35 by yapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	eating(t_philo *philo)
{
	t_state *state;

	state = philo->state;
	
	sem_wait(state->forks_sem);
	put_msg(get_time() - state->start, philo, F);
	sem_wait(state->forks_sem);
	put_msg(get_time() - state->start, philo, F);
	
	philo->last_meal = get_time();
	put_msg(philo->last_meal - state->start, philo, E);
	ft_sleep(state->eat);
	sem_post(state->forks_sem);
	sem_post(state->forks_sem);
}

/*static void		*check(void *arg)
{
	t_state *state;
	int		i;
	int		is_full;

	state = (t_state*)arg;
	sem_wait(state->dead_sem);
	while (!state->dead)
	{
		is_full = state->times == -1 ? 0 : 1;
		sem_post(state->dead_sem);
		i = -1;
		while (++i < state->num)
		{
			if (state->philos[i]->eat_times < state->times)
				is_full = 0;
			if (get_time() - state->philos[i]->last_meal > state->die)
			{
				put_msg(get_time() - state->start, state->philos[i], D);
				sem_wait(state->dead_sem);
				state->dead++;
				sem_post(state->dead_sem);
				exit(1);
				return NULL;
			}
		}
		sem_wait(state->dead_sem);
		if (is_full)
			state->dead++;
	}
	sem_post(state->dead_sem);
	return NULL;
}*/

static void	*listen_dead(void *arg)
{
	t_philo *p;

	p = (t_philo*)arg;
	sem_wait(p->state->dead_sem);
	exit(1);
	return (NULL);
}

static void	*write_dead(void *arg)
{
	t_philo *p;

	p = (t_philo*)arg;
	while (get_time() - p->last_meal < p->state->die)
		continue;
	sem_post(p->state->dead_sem);
	put_msg(get_time() - p->state->start, p, D);
	p->state->dead++;
	exit(1);
	return (NULL);
}

void		*routine(void *arg)
{
	t_philo *philo;
	t_state *state;
	pthread_t dead_listen_pid;
	pthread_t dead_write_pid;

	philo = (t_philo*)arg;
	if (philo->idx % 2)
		ft_sleep(100);
	state = philo->state;
	philo->last_meal = get_time();
	pthread_create(&dead_listen_pid, NULL, &listen_dead, philo);
	pthread_create(&dead_write_pid, NULL, &write_dead, philo);
	//sem_wait(state->dead_sem);
	while (1)
	{
		//sem_post(state->dead_sem);
		eating(philo);
		//sem_wait(state->dead_sem);
		philo->eat_times++;
		//sem_post(state->dead_sem);
		put_msg(get_time() - philo->state->start, philo, S);
		ft_sleep(philo->state->sleep);
		put_msg(get_time() - philo->state->start, philo, T);
		//sem_wait(state->dead_sem);
	}
	//sem_post(state->dead_sem);
	pthread_detach(dead_listen_pid);
	pthread_detach(dead_write_pid);
	return (NULL);
}
