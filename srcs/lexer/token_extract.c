/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_extract.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimega2 <jaimega2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 00:00:00 by jimmy             #+#    #+#             */
/*   Updated: 2026/01/20 15:01:55 by jaimega2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_quote_state(char c, t_quote_state *state)
{
	if (c == '\'' && !state->double_quote)
		state->simple_quote = !state->simple_quote;
	else if (c == '\"' && !state->simple_quote)
		state->double_quote = !state->double_quote;
}

int	is_space_outside_quotes(char c, t_quote_state *state)
{
	return (ft_isspace_shell(c) && !state->double_quote
		&& !state->simple_quote);
}

int	calculate_token_length(char *input, int *pos, t_quote_state *state)
{
	int	len;

	len = 0;
	while (input[*pos] && (input[*pos] != ' '
			|| state->double_quote || state->simple_quote))
	{
		if (input[*pos] == '\'' && !state->double_quote)
			state->simple_quote = !state->simple_quote;
		else if (input[*pos] == '\"' && !state->simple_quote)
			state->double_quote = !state->double_quote;
		len++;
		(*pos)++;
	}
	return (len);
}

void	copy_token_content(char *input, char *token, int start, int end)
{
	int	j;

	j = 0;
	while (start < end)
	{
		token[j++] = input[start];
		start++;
	}
	token[j] = '\0';
}

char	*extract_one_token(char *input, int *pos, t_quote_state *state)
{
	int		start;
	int		len;
	int		end;
	char	*token;

	start = *pos;
	state->simple_quote = 0;
	state->double_quote = 0;
	len = calculate_token_length(input, pos, state);
	end = *pos;
	token = malloc(sizeof(char) * (len + 1));
	if (!token)
		return (NULL);
	copy_token_content(input, token, start, end);
	return (token);
}
