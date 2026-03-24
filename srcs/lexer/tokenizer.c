/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimega2 <jaimega2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 00:00:00 by jimmy             #+#    #+#             */
/*   Updated: 2026/01/20 15:01:55 by jaimega2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_tokens(char *input)
{
	t_quote_state	state;
	int				i;
	int				count;
	int				has_content;

	i = -1;
	count = 0;
	has_content = 0;
	state.simple_quote = 0;
	state.double_quote = 0;
	while (input[++i])
	{
		update_quote_state(input[i], &state);
		if (is_space_outside_quotes(input[i], &state) && has_content++)
		{
			count++;
			has_content = 0;
		}
		else if (input[i] != '\'' && input[i] != '\"')
			has_content = 1;
	}
	return (count + (has_content > 0));
}

void	free_tokens(char **tokens, int count)
{
	int	i;

	i = 0;
	while (i < count)
		free(tokens[i++]);
	free(tokens);
}

int	handle_quote_error(char **tokens, char *processed)
{
	int	i;

	write(2, "syntax error: unexpected end of file\n", 37);
	g_exit_status = 2;
	i = 0;
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
	free(processed);
	return (0);
}

int	extract_all_tokens(char **tokens, char *processed, t_quote_state *state)
{
	int	i;
	int	pos;

	pos = 0;
	i = 0;
	while (processed[pos])
	{
		while (ft_isspace_shell(processed[pos]))
			pos++;
		if (!processed[pos])
			break ;
		tokens[i] = extract_one_token(processed, &pos, state);
		if (!tokens[i])
		{
			free_tokens(tokens, i);
			return (0);
		}
		i++;
	}
	tokens[i] = NULL;
	return (1);
}

char	**tokenizer(char *input)
{
	char			*processed;
	char			**tokens;
	t_quote_state	state;

	processed = preprocess_input(input);
	if (!processed)
		return (NULL);
	tokens = malloc(sizeof(char *) * (count_tokens(processed) + 1));
	if (!tokens)
	{
		free(processed);
		return (NULL);
	}
	state.simple_quote = 0;
	state.double_quote = 0;
	if (!extract_all_tokens(tokens, processed, &state))
	{
		free(processed);
		return (NULL);
	}
	if (state.simple_quote || state.double_quote)
		if (!handle_quote_error(tokens, processed))
			return (NULL);
	free(processed);
	return (tokens);
}
