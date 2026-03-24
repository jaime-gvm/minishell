/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimega2 <jaimega2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 16:18:27 by rnuno-im          #+#    #+#             */
/*   Updated: 2026/01/20 14:39:21 by jaimega2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	process_execute(char *prompt, char ***envp)
{
	t_cmd	*cmds;
	char	*input;

	while (1)
	{
		input = readline(prompt);
		if (!input)
			handle_eof();
		if (!*input)
		{
			free(input);
			continue ;
		}
		add_history(input);
		cmds = process_input(input, *envp);
		if (!cmds)
		{
			free(input);
			continue ;
		}
		execute_pipeline(cmds, envp);
		free_cmd_list(cmds);
		free(input);
	}
}

void	shell_loop(char **envp)
{
	char	*prompt;

	setup_signals();
	if (isatty(STDOUT_FILENO))
		prompt = "\033[1;36mminishell$ \033[0m";
	else
		prompt = "minishell$ ";
	process_execute(prompt, &envp);
}
