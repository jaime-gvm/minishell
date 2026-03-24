/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnuno-im <rnuno-im@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 14:48:07 by rnuno-im          #+#    #+#             */
/*   Updated: 2026/01/15 12:27:04 by rnuno-im         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	g_exit_status = 0;

int	main(int ac, char **av, char **envp)
{
	char	**my_envp;

	(void)ac;
	(void)av;
	my_envp = dup_envp(envp);
	if (!my_envp)
	{
		printf("Error: can't duplicate envp\n");
		return (1);
	}
	shell_loop(my_envp);
	free_envp(my_envp);
	return (g_exit_status);
}
