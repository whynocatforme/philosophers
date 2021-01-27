/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yapark <yapark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 20:47:45 by yapark            #+#    #+#             */
/*   Updated: 2021/01/27 21:36:21 by yapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <pthread.h>
# define E 0
# define S 1
# define T 2

typedef struct	s_philo
{
	int			doing;
}				t_philo;

typedef struct	s_state
{
	t_philo		**philos;
	int			*forks;
	int			num;
	int			die;
	int			eat;
	int			sleep;
	int			times;
}				t_state;

//utils.c
int				ft_strlen(const char *str);
int				ft_exit(t_state *s, const char *msg);
int				ft_atoi(char *str);

#endif
