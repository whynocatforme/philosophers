/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yapark <yapark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 20:47:30 by yapark            #+#    #+#             */
/*   Updated: 2021/01/27 21:47:13 by yapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_state*	init_state(int argc, char **argv)
{
	t_state	*ret;
	int		i;

	ret = (t_state*)malloc(sizeof(t_state));
	ret->num = ft_atoi(argv[1]);
	ret->die = ft_atoi(argv[2]);
	ret->eat = ft_atoi(argv[3]);
	ret->sleep = ft_atoi(argv[4]);
	ret->forks = (int*)malloc(sizeof(int) * ret->num);
	ret->philos = (t_philo**)malloc(sizeof(t_philo*) * (ret->num + 1));
	i = -1;
	while (++i < ret->num)
		ret->philos[i] = (t_philo*)malloc(sizeof(t_philo));
	ret->philos[i] = NULL;
	if (argc == 6)
		ret->times = ft_atoi(argv[4]);
	else
		ret->times = 0;
	printf("before return\n");
	return (ret);
}

int				main(int argc, char **argv)
{
	t_state *state;

	state = NULL;
	if (argc != 5 && argc != 6)
		return (ft_exit(state, "errer: invalid arguments\n"));
	state = init_state(argc, argv);
	return (ft_exit(state, NULL));
}
