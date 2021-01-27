/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yapark <yapark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 20:47:45 by yapark            #+#    #+#             */
/*   Updated: 2021/01/28 02:22:35 by yapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# define E 0
# define S 1
# define T 2
# define L 0
# define R 1

struct s_state;

typedef struct		s_philo
{
	struct s_state	*state;
	int				idx;
	int				forks[2];
	int				doing;
	pthread_t		pid;
	pthread_t		chk_pid;
	struct timeval	last_meal;
}					t_philo;

typedef struct		s_state
{
	t_philo			**philos;
	int				*forks;
	pthread_mutex_t	*forks_mtx;
	pthread_mutex_t	mtx; //???
	pthread_mutex_t dead_mtx;
	int				dead;
	int				num;
	int				die;
	int				eat;
	int				sleep;
	int				times;
	struct timeval	start_time;
}					t_state;

void				*routine(void *arg);
int					ft_strlen(const char *str);
int					ft_exit(t_state *s, const char *msg);
int					ft_atoi(char *str);
int					get_time(0, struct timeval start);

#endif
