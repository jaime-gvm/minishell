/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimega2 <jaimega2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 15:12:32 by rnuno-im          #+#    #+#             */
/*   Updated: 2026/01/20 15:01:58 by jaimega2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	handle_input(t_cmd *cmds, char **envp)
{
	if (cmds->heredoc)
	{
		if (cmds->fd_in < 0)
		{
			if (exec_heredoc(cmds, envp) < 0)
				return (-1);
		}
		if (dup2(cmds->fd_in, STDIN_FILENO) < 0)
			return (perror("dup2 heredoc"), close(cmds->fd_in), -1);
		close(cmds->fd_in);
		cmds->fd_in = -1;
	}
	else if (cmds->infile)
	{
		cmds->fd_in = open(cmds->infile, O_RDONLY);
		if (cmds->fd_in < 0)
		{
			perror(cmds->infile);
			g_exit_status = 1;
			return (-1);
		}
		if (dup2(cmds->fd_in, STDIN_FILENO) < 0)
			return (perror("dup2 infile"), close(cmds->fd_in), -1);
	}
	return (0);
}

static int	handle_output(t_cmd *cmds)
{
	int	flags;

	if (cmds->outfile)
	{
		flags = O_WRONLY | O_CREAT;
		if (cmds->type == 1)
			flags |= O_APPEND;
		else
			flags |= O_TRUNC;
		cmds->fd_out = open(cmds->outfile, flags, 0644);
		if (cmds->fd_out < 0)
		{
			perror(cmds->outfile);
			g_exit_status = 1;
			return (-1);
		}
		if (dup2(cmds->fd_out, STDOUT_FILENO) < 0)
			return (perror("dup2 outfile"), close(cmds->fd_out), -1);
		close(cmds->fd_out);
	}
	return (0);
}

int	handle_redirections(t_cmd *cmds, char **envp)
{
	if (handle_input(cmds, envp) < 0)
		return (-1);
	if (handle_output(cmds) < 0)
		return (-1);
	return (0);
}
