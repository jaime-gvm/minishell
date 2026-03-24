/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocess_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimega2 <jaimega2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 11:10:00 by jaimega2          #+#    #+#             */
/*   Updated: 2026/01/20 15:01:56 by jaimega2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	process_heredoc(t_preprocess *data, t_quote_state *state)
{
	if (!state->simple_quote && !state->double_quote)
		handle_heredoc(data->input, data->result, data->i, data->j);
	else
	{
		data->result[(*data->j)++] = data->input[(*data->i)++];
		update_quote_state(data->input[*data->i - 1], state);
	}
}

void	process_append(t_preprocess *data, t_quote_state *state)
{
	if (!state->simple_quote && !state->double_quote)
		handle_append(data->input, data->result, data->i, data->j);
	else
	{
		data->result[(*data->j)++] = data->input[(*data->i)++];
		update_quote_state(data->input[*data->i - 1], state);
	}
}

void	process_pipe(t_preprocess *data, t_quote_state *state)
{
	if (!state->simple_quote && !state->double_quote)
		handle_pipe(data->input, data->result, data->i, data->j);
	else
	{
		data->result[(*data->j)++] = data->input[(*data->i)++];
		update_quote_state(data->input[*data->i - 1], state);
	}
}

void	process_redirect_out(t_preprocess *data, t_quote_state *state)
{
	if (!state->simple_quote && !state->double_quote)
		handle_redirect_out(data->input, data->result, data->i, data->j);
	else
	{
		data->result[(*data->j)++] = data->input[(*data->i)++];
		update_quote_state(data->input[*data->i - 1], state);
	}
}

void	process_redirect_in(t_preprocess *data, t_quote_state *state)
{
	if (!state->simple_quote && !state->double_quote)
		handle_redirect_in(data->input, data->result, data->i, data->j);
	else
	{
		data->result[(*data->j)++] = data->input[(*data->i)++];
		update_quote_state(data->input[*data->i - 1], state);
	}
}
