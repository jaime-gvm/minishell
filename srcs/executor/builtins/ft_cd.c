/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimega2 <jaimega2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:56:18 by rnuno-im          #+#    #+#             */
/*   Updated: 2026/01/20 13:51:14 by jaimega2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*get_home_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "HOME=", 5) == 0)
			return (ft_strdup(envp[i] + 5));
		i++;
	}
	return (NULL);
}

static int	many_arguments(char **args)
{
	if (args[2])
	{
		print_error("minishell: cd: too many arguments\n");
		g_exit_status = 1;
		return (1);
	}
	return (0);
}

static int	change_directory(char *path, int should_free)
{
	if (chdir(path) == -1)
	{
		perror_multi("minishell: cd: ", path,
			": No such file or directory\n", NULL);
		if (should_free)
			free(path);
		return (g_exit_status = 1, 1);
	}
	if (should_free)
		free(path);
	return (0);
}

int	ft_cd(char **args, char ***envp)
{
	char	*path;
	int		should_free;

	should_free = 0;
	if (many_arguments(args))
		return (1);
	if (!args[1] || ft_strncmp(args[1], "~", 2) == 0)
	{
		path = get_home_path(*envp);
		if (!path)
			return (print_error("cd: HOME not set\n"), 1);
		should_free = 1;
	}
	else
		path = args[1];
	return (change_directory(path, should_free));
}
