/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnuno-im <rnuno-im@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 13:56:28 by rnuno-im          #+#    #+#             */
/*   Updated: 2026/01/13 13:38:23 by rnuno-im         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "cd", 3) == 0 && cmd[2] == '\0')
		return (1);
	if (ft_strncmp(cmd, "echo", 5) == 0 && cmd[4] == '\0')
		return (1);
	if (ft_strncmp(cmd, "env", 4) == 0 && cmd[3] == '\0')
		return (1);
	if (ft_strncmp(cmd, "exit", 5) == 0 && cmd[4] == '\0')
		return (1);
	if (ft_strncmp(cmd, "export", 7) == 0 && cmd[6] == '\0')
		return (1);
	if (ft_strncmp(cmd, "pwd", 4) == 0 && cmd[3] == '\0')
		return (1);
	if (ft_strncmp(cmd, "unset", 7) == 0 && cmd[5] == '\0')
		return (1);
	return (0);
}

int	exec_builtin(char **args, char ***envp)
{
	if (ft_strncmp(args[0], "cd", 3) == 0 && args[0][2] == '\0')
		return (ft_cd(args, envp));
	if (ft_strncmp(args[0], "echo", 5) == 0 && args[0][4] == '\0')
		return (ft_echo(args));
	if (ft_strncmp(args[0], "env", 4) == 0 && args[0][3] == '\0')
		return (ft_env(*envp));
	if (ft_strncmp(args[0], "exit", 5) == 0 && args[0][4] == '\0')
		return (ft_exit(args));
	if (ft_strncmp(args[0], "export", 7) == 0 && args[0][6] == '\0')
		return (ft_export(args, envp));
	if (ft_strncmp(args[0], "pwd", 4) == 0 && args[0][3] == '\0')
		return (ft_pwd());
	if (ft_strncmp(args[0], "unset", 6) == 0 && args[0][5] == '\0')
		return (ft_unset(args, envp));
	return (1);
}
