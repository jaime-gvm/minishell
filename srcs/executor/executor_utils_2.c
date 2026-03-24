/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimega2 <jaimega2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:24:07 by rnuno-im          #+#    #+#             */
/*   Updated: 2026/01/20 13:47:44 by jaimega2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	helper_2(t_cmd *cmds, char ***envp, char *cmd_path)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		g_exit_status = 1;
		return ;
	}
	if (pid == 0)
		exec_in_child(cmd_path, cmds->args, *envp);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit_status = 128 + WTERMSIG(status);
}

void	execute_helper(t_cmd *cmds, char ***envp, int should_exit)
{
	char	*cmd_path;

	if (cmds->full_path)
		cmd_path = cmds->full_path;
	else
		cmd_path = find_cmd(cmds->cmd, *envp);
	if (!cmd_path)
	{
		perror_multi(cmds->args[0], ": command not found\n", NULL, NULL);
		g_exit_status = 127;
		if (should_exit)
			exit(127);
		return ;
	}
	if (should_exit)
		exec_in_child(cmd_path, cmds->args, *envp);
	else
		helper_2(cmds, envp, cmd_path);
	if (!cmds->full_path)
		free(cmd_path);
}
