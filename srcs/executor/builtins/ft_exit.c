/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimega2 <jaimega2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:51:29 by rnuno-im          #+#    #+#             */
/*   Updated: 2026/01/20 13:47:44 by jaimega2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	close_all_fds(void)
{
	int	fd;

	fd = 3;
	while (fd < 1024)
	{
		close(fd);
		fd++;
	}
}

static int	is_valid_exit_arg(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(char **args)
{
	int	exit_code;

	printf("exit\n");
	if (!args[1])
	{
		close_all_fds();
		exit(0);
	}
	if (!is_valid_exit_arg(args[1]))
	{
		perror_multi("minishell: exit: ", args[1],
			": numeric argument required\n", NULL);
		close_all_fds();
		exit (2);
	}
	if (args[2])
	{
		print_error("minishell: exit: too many arguments\n");
		close_all_fds();
		exit (1);
	}
	exit_code = ft_atoi(args[1]);
	close_all_fds();
	exit(exit_code);
}
