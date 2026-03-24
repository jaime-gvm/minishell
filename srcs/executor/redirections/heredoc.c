/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimega2 <jaimega2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 15:13:12 by rnuno-im          #+#    #+#             */
/*   Updated: 2026/01/20 15:01:54 by jaimega2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	create_heredoc(int pipefd[2])
{
	if (pipe(pipefd) < 0)
	{
		perror("pipe");
		return (-1);
	}
	return (0);
}

static void	read_h_input(int write_fd, char *delim, char **envp)
{
	char	*line;
	char	*expanded;
	size_t	len;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			perror_multi("warning: here-document delimited by EOF (wanted `",
				delim, "')\n", NULL);
			break ;
		}
		len = ft_strlen(delim);
		if (ft_strncmp(line, delim, len) == 0 && line[len] == '\0')
		{
			free(line);
			break ;
		}
		expanded = expand_vars(line, envp);
		write(write_fd, expanded, ft_strlen(expanded));
		write(write_fd, "\n", 1);
		free(line);
		free(expanded);
	}
}

int	exec_heredoc(t_cmd *cmds, char **envp)
{
	int	pipefd[2];

	if (!cmds->heredoc)
		return (0);
	if (create_heredoc(pipefd) < 0)
		return (-1);
	read_h_input(pipefd[1], cmds->heredoc, envp);
	close(pipefd[1]);
	cmds->fd_in = pipefd[0];
	return (0);
}
