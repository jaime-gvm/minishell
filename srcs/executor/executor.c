/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimega2 <jaimega2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:12:57 by rnuno-im          #+#    #+#             */
/*   Updated: 2026/01/20 15:01:54 by jaimega2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*find_cmd(char *cmd, char **envp)
{
	t_path	all;
	int		i;
	char	*res;

	i = 0;
	res = NULL;
	all.path = NULL;
	all.cmd = cmd;
	all.full = NULL;
	all.paths = NULL;
	all.tmp = NULL;
	all.i = 0;
	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (check_access(cmd), ft_strdup(cmd));
	while (envp && envp[i] && !all.path)
		if (!ft_strncmp(envp[i++], "PATH=", 5))
			all.path = envp[i - 1] + 5;
	if (all.path)
		res = check_envp_path(&all);
	return (res);
}

void	exec_in_child(char *cmd_path, char **args, char **envp)
{
	check_access(cmd_path);
	execve(cmd_path, args, envp);
	perror("execve");
	exit(127);
}

void	exec_child(char *cmd_path, char **args, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return ;
	}
	if (pid == 0)
	{
		check_access(cmd_path);
		execve(cmd_path, args, envp);
		perror("execve");
		exit(127);
	}
	waitpid(pid, &status, 0);
}

void	executor(t_cmd *cmds, char ***envp)
{
	int	saved_stdin;
	int	saved_stdout;

	if (!cmds || !cmds->args || !cmds->args[0])
		return ;
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (handle_redirections(cmds, *envp) < 0)
	{
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
		return ;
	}
	execute_command(cmds, envp, 0);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	if (cmds->fd_in != -1)
		close(cmds->fd_in);
	if (cmds->fd_out != -1)
		close(cmds->fd_out);
}
