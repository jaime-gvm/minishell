/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parse_handlers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimega2 <jaimega2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:37:04 by jaimega2          #+#    #+#             */
/*   Updated: 2026/01/20 14:45:25 by jaimega2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_append_token(t_parse_data *data)
{
	if (!data->tokens[data->i + 1])
	{
		print_error("syntax error near unexpected token `newline'\n");
		g_exit_status = 2;
		data->error = 1;
		return ;
	}
	data->current->outfile = ft_strdup(data->tokens[data->i + 1]);
	data->current->type = 1;
	data->i++;
}

void	handle_heredoc_token(t_parse_data *data)
{
	if (!data->tokens[data->i + 1])
	{
		print_error("syntax error near unexpected token `newline'\n");
		g_exit_status = 2;
		data->error = 1;
		return ;
	}
	data->current->heredoc = ft_strdup(data->tokens[data->i + 1]);
	data->current->type = 2;
	data->i++;
}

void	handle_pipe_token(t_parse_data *data)
{
	if (!data->args_tmp || !data->args_tmp[0])
	{
		print_error("syntax error near unexpected token `|'\n");
		g_exit_status = 2;
		data->error = 1;
		return ;
	}
	data->current->args = data->args_tmp;
	if (data->args_tmp && data->args_tmp[0])
		data->current->cmd = ft_strdup(data->args_tmp[0]);
	add_cmd_to_list(&data->head, data->current);
	data->current = create_cmd_node();
	data->args_tmp = NULL;
	data->arg_count = 0;
}

void	handle_input_redirect_token(t_parse_data *data)
{
	if (!data->tokens[data->i + 1])
	{
		print_error("syntax error near unexpected token `newline'\n");
		g_exit_status = 2;
		data->error = 1;
		return ;
	}
	data->current->infile = ft_strdup(data->tokens[data->i + 1]);
	data->current->type = 3;
	data->i++;
}

void	handle_output_redirect_token(t_parse_data *data)
{
	if (!data->tokens[data->i + 1])
	{
		print_error("syntax error near unexpected token `newline'\n");
		g_exit_status = 2;
		data->error = 1;
		return ;
	}
	data->current->outfile = ft_strdup(data->tokens[data->i + 1]);
	data->current->type = 0;
	data->i++;
}
