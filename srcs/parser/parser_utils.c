/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimega2 <jaimega2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 00:00:00 by jimmy             #+#    #+#             */
/*   Updated: 2026/01/20 14:45:24 by jaimega2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	finalize_cmd(t_parse_data *data)
{
	if (data->current)
	{
		data->current->args = data->args_tmp;
		if (data->args_tmp && data->args_tmp[0])
		{
			data->current->cmd = ft_strdup(data->args_tmp[0]);
			if (ft_strchr(data->args_tmp[0], '/'))
				data->current->full_path = ft_strdup(data->args_tmp[0]);
			add_cmd_to_list(&data->head, data->current);
		}
		else if (data->head)
		{
			print_error("syntax error: unexpected end of file\n");
			g_exit_status = 2;
			free_cmd_list(data->head);
			data->head = NULL;
		}
		data->current = create_cmd_node();
		data->args_tmp = NULL;
		data->arg_count = 0;
	}
}

void	init_parse_data(t_parse_data *data, char **tokens)
{
	data->tokens = tokens;
	data->head = NULL;
	data->current = create_cmd_node();
	data->args_tmp = NULL;
	data->arg_count = 0;
	data->i = 0;
	data->error = 0;
}
