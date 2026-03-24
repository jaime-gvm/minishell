/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimega2 <jaimega2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 16:17:15 by rnuno-im          #+#    #+#             */
/*   Updated: 2026/01/20 15:09:08 by jaimega2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	expand_tokens(char **tokens, char **envp)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		expand_single_token(&tokens[i], envp);
		i++;
	}
}

t_cmd	*process_input(char *input, char **envp)
{
	char	**tokens;
	char	*preprocesed;
	t_cmd	*cmds;

	if (!input || !*input)
		return (NULL);
	preprocesed = preprocess_input(input);
	if (!preprocesed)
		return (NULL);
	tokens = tokenizer(preprocesed);
	free(preprocesed);
	if (!tokens)
		return (NULL);
	expand_tokens(tokens, envp);
	cmds = parse_tokens(tokens);
	free_split(tokens);
	return (cmds);
}
