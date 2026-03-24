/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimega2 <jaimega2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 13:10:04 by rnuno-im          #+#    #+#             */
/*   Updated: 2026/01/20 15:01:50 by jaimega2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	execute_child(t_cmd *cmd, t_pipeline *data, int i)
{
	set_fds(data->pipes, i, data->count);
	close_pipes(data->pipes, data->count);
	if (handle_redirections(cmd, *data->envp) < 0)
		exit (1);
	execute_command(cmd, data->envp, 1);
}

void	fork_and_execute(t_pipeline *data)
{
	pid_t	pid;
	t_cmd	*current;
	int		i;

	current = data->cmds;
	i = 0;
	while (current)
	{
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			close_pipes(data->pipes, data->count);
			return ;
		}
		if (pid == 0)
			execute_child(current, data, i);
		if (i == data->count - 1)
			data->last_pid = pid;
		current = current->next;
		i++;
	}
}

void	wait_processes(int count, pid_t last_pid)
{
	int		i;
	int		status;
	pid_t	pid;

	waitpid(last_pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit_status = 128 + WTERMSIG(status);
	i = 0;
	while (i < count - 1)
	{
		pid = wait(NULL);
		if (pid < 0)
			break ;
		i++;
	}
}

void	process_all_heredocs(t_cmd *cmds, char **envp)
{
	t_cmd	*current;

	current = cmds;
	while (current)
	{
		if (current->heredoc)
			exec_heredoc(current, envp);
		current = current->next;
	}
}

void	execute_pipeline(t_cmd *cmds, char ***envp)
{
	t_pipeline	data;

	data.count = count_cmds(cmds);
	process_all_heredocs(cmds, *envp);
	if (!cmds || !cmds->cmd)
	{
		if (cmds && cmds->fd_in >= 0)
			close(cmds->fd_in);
		return ;
	}
	if (data.count == 1)
	{
		executor(cmds, envp);
		return ;
	}
	data.cmds = cmds;
	data.envp = envp;
	data.pipes = create_pipes(data.count);
	if (!data.pipes)
		return ;
	fork_and_execute(&data);
	close_pipes(data.pipes, data.count);
	wait_processes(data.count, data.last_pid);
	free_pipes(data.pipes, data.count);
}
