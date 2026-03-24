/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnuno-im <rnuno-im@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 13:11:53 by rnuno-im          #+#    #+#             */
/*   Updated: 2025/12/17 15:13:17 by rnuno-im         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	count_cmds(t_cmd *cmds)
{
	int	count;

	count = 0;
	while (cmds)
	{
		count++;
		cmds = cmds->next;
	}
	return (count);
}

void	close_pipes(int **pipes, int count)
{
	int	i;

	i = 0;
	while (i < count - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

int	**create_pipes(int count)
{
	int	**pipes;
	int	i;

	pipes = malloc(sizeof(int *) * (count - 1));
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < count - 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i] || pipe(pipes[i]) < 0)
		{
			perror("pipe");
			while (--i >= 0)
				free(pipes[i]);
			free(pipes);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

void	set_fds(int **pipes, int i, int count)
{
	if (i > 0)
	{
		dup2(pipes[i - 1][0], STDIN_FILENO);
		close(pipes[i - 1][0]);
	}
	if (i < count - 1)
	{
		dup2(pipes[i][1], STDOUT_FILENO);
		close(pipes[i][1]);
	}
}

void	free_pipes(int **pipes, int count)
{
	int	i;

	i = 0;
	while (i < count - 1)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}
