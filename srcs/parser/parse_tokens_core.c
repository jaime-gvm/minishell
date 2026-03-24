/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens_core.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimega2 <jaimega2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:10:00 by jaimega2          #+#    #+#             */
/*   Updated: 2026/01/20 15:06:22 by jaimega2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*create_cmd_node(void)
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->cmd = NULL;
	node->args = NULL;
	node->infile = NULL;
	node->outfile = NULL;
	node->heredoc = NULL;
	node->type = 0;
	node->full_path = NULL;
	node->fd_in = -1;
	node->fd_out = -1;
	node->next = NULL;
	return (node);
}

void	process_tokens(t_parse_data *data)
{
	while (data->tokens[data->i])
	{
		if (ft_strncmp(data->tokens[data->i], "|", 2) == 0)
			handle_pipe_token(data);
		else if (ft_strncmp(data->tokens[data->i], "<<", 3) == 0)
			handle_heredoc_token(data);
		else if (ft_strncmp(data->tokens[data->i], ">>", 3) == 0)
			handle_append_token(data);
		else if (ft_strncmp(data->tokens[data->i], "<", 2) == 0)
			handle_input_redirect_token(data);
		else if (ft_strncmp(data->tokens[data->i], ">", 2) == 0)
			handle_output_redirect_token(data);
		else
			add_arg_to_list(&data->args_tmp, data->tokens[data->i],
				&data->arg_count);
		data->i++;
	}
}

int	validate_first_token(char **tokens)
{
	if (ft_strncmp(tokens[0], "|", 2) == 0)
	{
		print_error("syntax error near unexpected token `|'\n");
		g_exit_status = 2;
		return (0);
	}
	return (1);
}

void	init_parse_commands(t_parse_data *data, char *processed)
{
	data->tokens = ft_split(processed, ' ');
	data->head = NULL;
	data->current = create_cmd_node();
	data->args_tmp = NULL;
	data->arg_count = 0;
	data->i = 0;
}
