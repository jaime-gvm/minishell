/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimega2 <jaimega2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 11:30:00 by jaimega2          #+#    #+#             */
/*   Updated: 2026/01/20 15:01:57 by jaimega2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	append_var_value(char *result, char *var_value)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (var_value[i])
	{
		result[count] = var_value[i];
		count++;
		i++;
	}
	return (count);
}

int	expand_exit_status(int *i, char *result)
{
	char	*var_value;
	int		added;

	(*i)++;
	var_value = ft_itoa(g_exit_status);
	if (!var_value)
		return (0);
	added = append_var_value(result, var_value);
	free(var_value);
	return (added);
}

int	get_exit_status_len(int *i)
{
	char	*var_value;
	int		len;

	(*i)++;
	var_value = ft_itoa(g_exit_status);
	if (!var_value)
		return (1);
	len = ft_strlen(var_value);
	free(var_value);
	return (len);
}

int	get_var_name_and_value(char *input, int *i, char **envp)
{
	char	*var_name;
	char	*var_value;
	int		k;
	int		len;

	(*i)++;
	if (input[*i] == '?')
		return (get_exit_status_len(i));
	var_name = malloc(sizeof(char) * 256);
	if (!var_name)
		return (0);
	k = 0;
	while (ft_isalnum(input[*i]) || input[*i] == '_')
		var_name[k++] = input[(*i)++];
	var_name[k] = '\0';
	var_value = get_env_value(var_name, envp);
	free(var_name);
	if (!var_value)
		return (0);
	len = ft_strlen(var_value);
	return (len);
}

int	calculate_expanded_size(char *input, char **envp)
{
	t_quote_state	state;
	int				i;
	int				size;

	state.simple_quote = 0;
	state.double_quote = 0;
	i = 0;
	size = 0;
	while (input[i])
	{
		update_quote_state(input[i], &state);
		if (input[i] == '$' && (ft_isalpha(input[i + 1])
				|| input[i + 1] == '_' || input[i + 1] == '?')
			&& !state.simple_quote)
			size += get_var_name_and_value(input, &i, envp);
		else
		{
			size++;
			i++;
		}
	}
	return (size);
}
