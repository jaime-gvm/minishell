/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnuno-im <rnuno-im@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:35:00 by jaimega2          #+#    #+#             */
/*   Updated: 2025/12/18 15:14:56 by rnuno-im         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_cmd_list(t_cmd *cmds)
{
	t_cmd	*tmp;

	while (cmds)
	{
		tmp = cmds->next;
		if (cmds->cmd)
			free(cmds->cmd);
		if (cmds->args)
			free_split(cmds->args);
		if (cmds->infile)
			free(cmds->infile);
		if (cmds->outfile)
			free(cmds->outfile);
		if (cmds->heredoc)
			free(cmds->heredoc);
		if (cmds->full_path)
			free(cmds->full_path);
		free(cmds);
		cmds = tmp;
	}
}

void	add_arg_to_list(char ***args, char *token, int *count)
{
	char	**new_args;
	int		i;

	new_args = malloc(sizeof(char *) * (*count + 2));
	if (!new_args)
		return ;
	i = 0;
	if (*args)
	{
		while (i < *count)
		{
			new_args[i] = (*args)[i];
			i++;
		}
		free(*args);
	}
	new_args[i] = ft_strdup(token);
	new_args[i + 1] = NULL;
	*args = new_args;
	(*count)++;
}

void	add_cmd_to_list(t_cmd **head, t_cmd *new_node)
{
	t_cmd	*tmp;

	if (!*head)
	{
		*head = new_node;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}
