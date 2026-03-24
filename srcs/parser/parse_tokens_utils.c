/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimega2 <jaimega2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:00:00 by jaimega2          #+#    #+#             */
/*   Updated: 2026/01/20 15:06:21 by jaimega2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_token_type(t_parse_data *data, char **tokens)
{
	if (tokens[data->i][0] == '\x01')
		add_arg_to_list(&data->args_tmp, tokens[data->i] + 1,
			&data->arg_count);
	else if (ft_strncmp(tokens[data->i], ">>", 3) == 0)
		handle_append_token(data);
	else if (ft_strncmp(tokens[data->i], "<<", 3) == 0)
		handle_heredoc_token(data);
	else if (ft_strncmp(tokens[data->i], "|", 2) == 0)
		handle_pipe_token(data);
	else if (ft_strncmp(tokens[data->i], "<", 2) == 0)
		handle_input_redirect_token(data);
	else if (ft_strncmp(tokens[data->i], ">", 2) == 0)
		handle_output_redirect_token(data);
	else
		add_arg_to_list(&data->args_tmp, tokens[data->i], &data->arg_count);
}

void	process_token_loop(t_parse_data *data, char **tokens)
{
	while (tokens[data->i])
	{
		if (data->error)
			break ;
		handle_token_type(data, tokens);
		data->i++;
	}
}

static void	cleanup_on_error(t_parse_data *data)
{
	if (data->head)
		free_cmd_list(data->head);
	if (data->current)
		free(data->current);
}

t_cmd	*finalize_parse(t_parse_data *data)
{
	if (data->error)
	{
		cleanup_on_error(data);
		return (NULL);
	}
	finalize_cmd(data);
	if (data->current)
		free(data->current);
	return (data->head);
}
