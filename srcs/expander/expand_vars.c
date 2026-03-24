/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimega2 <jaimega2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:33:03 by codespace         #+#    #+#             */
/*   Updated: 2026/01/20 15:01:57 by jaimega2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	expand_single_var(char *input, int *i, char *result, char **envp)
{
	char	*var_name;
	char	*var_value;
	int		k;
	int		added;

	(*i)++;
	if (input[*i] == '?')
		return (expand_exit_status(i, result));
	var_name = malloc(sizeof(char) * 256);
	if (!var_name)
		return (-1);
	k = 0;
	while (ft_isalnum(input[*i]) || input[*i] == '_')
		var_name[k++] = input[(*i)++];
	var_name[k] = '\0';
	var_value = get_env_value(var_name, envp);
	free(var_name);
	if (!var_value)
		return (0);
	added = append_var_value(result, var_value);
	return (added);
}

static int	handle_dollar(t_expand_data *data, t_quote_state *state,
		char **envp)
{
	int	r;

	if (state->simple_quote)
		data->result[(*data->j)++] = data->input[(*data->i)++];
	else
	{
		r = expand_single_var(data->input, data->i, &data->result[*data->j],
				envp);
		if (r == -1)
			return (-1);
		*data->j += r;
	}
	return (0);
}

static void	expand_input_loop(t_expand_data *data, t_quote_state *state,
		char **envp)
{
	while (data->input[*data->i])
	{
		update_quote_state(data->input[*data->i], state);
		if (data->input[*data->i] == '$' && (ft_isalpha(data->input[*data->i
						+ 1]) || data->input[*data->i + 1] == '_'
				|| data->input[*data->i + 1] == '?'))
		{
			if (handle_dollar(data, state, envp) == -1)
			{
				free(data->result);
				data->result = NULL;
				return ;
			}
		}
		else
			data->result[(*data->j)++] = data->input[(*data->i)++];
	}
}

char	*expand_vars(char *input, char **envp)
{
	t_expand_data	data;
	int				i;
	int				j;
	int				size;
	t_quote_state	state;

	state.simple_quote = 0;
	state.double_quote = 0;
	size = calculate_expanded_size(input, envp);
	data.result = malloc(sizeof(char) * (size + 1));
	if (!data.result)
		return (NULL);
	i = 0;
	j = 0;
	data.input = input;
	data.i = &i;
	data.j = &j;
	expand_input_loop(&data, &state, envp);
	if (!data.result)
		return (NULL);
	data.result[j] = '\0';
	return (data.result);
}

char	*get_env_value(char *var_name, char **envp)
{
	int	i;
	int	name_len;

	name_len = ft_strlen(var_name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var_name, name_len) == 0
			&& envp[i][name_len] == '=')
			return (envp[i] + name_len + 1);
		i++;
	}
	return (NULL);
}
