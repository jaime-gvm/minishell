/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimega2 <jaimega2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 17:20:07 by rnuno-im          #+#    #+#             */
/*   Updated: 2026/01/20 13:47:42 by jaimega2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_split(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	check_access(char *cmd)
{
	if (access(cmd, F_OK) != 0)
	{
		perror_multi("minishell: ", cmd,
			": No such file or directory\n", NULL);
		exit(127);
	}
	if (access(cmd, X_OK) != 0)
	{
		perror_multi("minishell: ", cmd, ": Permission denied\n", NULL);
		exit(126);
	}
}

char	*check_envp_path(t_path *all)
{
	char	*found;

	found = NULL;
	all->paths = ft_split(all->path, ':');
	if (!all->paths)
		return (NULL);
	all->i = 0;
	while (all->paths[all->i])
	{
		all->full = build_path(all->paths[all->i], all->cmd);
		if (!all->full)
			break ;
		if (access(all->full, X_OK) == 0)
		{
			found = ft_strdup(all->full);
			free(all->full);
			break ;
		}
		free(all->full);
		all->i++;
	}
	free_split(all->paths);
	return (found);
}

char	*build_path(char *dir, char *cmd)
{
	char	*full;
	int		len;

	len = ft_strlen(dir) + ft_strlen(cmd) + 2;
	full = malloc(len);
	if (!full)
		return (NULL);
	ft_strlcpy(full, dir, len);
	ft_strlcat(full, "/", len);
	ft_strlcat(full, cmd, len);
	return (full);
}

void	execute_command(t_cmd *cmds, char ***envp, int should_exit)
{
	char	**args;

	args = cmds->args;
	if (is_builtin(args[0]))
	{
		exec_builtin(args, envp);
		if (should_exit)
			exit (0);
		return ;
	}
	execute_helper(cmds, envp, should_exit);
}
