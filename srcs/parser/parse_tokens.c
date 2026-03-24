/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimega2 <jaimega2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:35:00 by jaimega2          #+#    #+#             */
/*   Updated: 2026/01/20 15:06:24 by jaimega2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*parse_commands(char *processed)
{
	t_parse_data	data;

	init_parse_commands(&data, processed);
	if (!data.tokens || !data.tokens[0])
	{
		if (data.tokens)
			free_split(data.tokens);
		return (NULL);
	}
	if (!validate_first_token(data.tokens))
	{
		free_split(data.tokens);
		return (NULL);
	}
	process_tokens(&data);
	data.current->args = data.args_tmp;
	if (data.args_tmp && data.args_tmp[0])
		data.current->cmd = ft_strdup(data.args_tmp[0]);
	add_cmd_to_list(&data.head, data.current);
	free_split(data.tokens);
	return (data.head);
}

t_cmd	*parse_tokens(char **tokens)
{
	t_parse_data	data;

	if (!tokens || !tokens[0])
		return (NULL);
	if (!validate_first_token(tokens))
		return (NULL);
	init_parse_data(&data, tokens);
	process_token_loop(&data, tokens);
	return (finalize_parse(&data));
}
