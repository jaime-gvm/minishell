/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocess.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimega2 <jaimega2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 00:00:00 by jimmy             #+#    #+#             */
/*   Updated: 2026/01/20 15:01:56 by jaimega2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_operator(t_preprocess *data, t_quote_state *state)
{
	char	c;

	if (ft_strncmp(&data->input[*data->i], "<<", 2) == 0)
		process_heredoc(data, state);
	else if (ft_strncmp(&data->input[*data->i], ">>", 2) == 0)
		process_append(data, state);
	else if (data->input[*data->i] == '|')
		process_pipe(data, state);
	else if (data->input[*data->i] == '>')
		process_redirect_out(data, state);
	else if (data->input[*data->i] == '<')
		process_redirect_in(data, state);
	else
	{
		c = data->input[*data->i];
		if (ft_isspace_shell(c) && !state->simple_quote && !state->double_quote)
			data->result[(*data->j)++] = ' ';
		else
			data->result[(*data->j)++] = c;
		update_quote_state(c, state);
		(*data->i)++;
	}
}

void	process_operators(char *input, char *result, int *i, int *j)
{
	t_quote_state	state;
	t_preprocess	data;

	state.simple_quote = 0;
	state.double_quote = 0;
	data.input = input;
	data.result = result;
	data.i = i;
	data.j = j;
	while (input[*i])
		handle_operator(&data, &state);
}

char	*preprocess_input(char *input)
{
	char	*result;
	int		i;
	int		j;
	int		len;

	len = ft_strlen(input);
	result = malloc(sizeof(char) * (len * 2 + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	process_operators(input, result, &i, &j);
	result[j] = '\0';
	return (result);
}
