/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimega2 <jaimega2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:30:00 by jaimega2          #+#    #+#             */
/*   Updated: 2026/01/20 15:09:09 by jaimega2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	has_quotes(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i] == '\'' || token[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

int	is_pure_operator(char *token)
{
	if (!token || has_quotes(token))
		return (0);
	if (ft_strncmp(token, "|", 2) == 0)
		return (1);
	if (ft_strncmp(token, ">", 2) == 0)
		return (1);
	if (ft_strncmp(token, "<", 2) == 0)
		return (1);
	if (ft_strncmp(token, ">>", 3) == 0)
		return (1);
	if (ft_strncmp(token, "<<", 3) == 0)
		return (1);
	return (0);
}

static void	expand_with_quotes(char **token, char **envp)
{
	char	*expanded;
	char	*no_quotes;
	char	*marked;

	expanded = expand_vars(*token, envp);
	if (expanded)
	{
		no_quotes = remove_quotes(expanded);
		marked = ft_strjoin("\x01", no_quotes);
		free(*token);
		free(expanded);
		free(no_quotes);
		if (marked)
			*token = marked;
	}
}

void	expand_single_token(char **token, char **envp)
{
	char	*expanded;

	if (is_pure_operator(*token))
		return ;
	if (has_quotes(*token))
		expand_with_quotes(token, envp);
	else
	{
		expanded = expand_vars(*token, envp);
		if (expanded)
		{
			free(*token);
			*token = expanded;
		}
	}
}
