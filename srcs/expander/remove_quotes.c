/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimega2 <jaimega2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 12:00:00 by jaimega2          #+#    #+#             */
/*   Updated: 2026/01/20 15:01:58 by jaimega2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*remove_quotes(char *input)
{
	t_quote_state	state;
	char			*result;
	int				i;
	int				j;

	state.simple_quote = 0;
	state.double_quote = 0;
	result = malloc(sizeof(char) * (ft_strlen(input) + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] == '\'' && !state.double_quote)
			state.simple_quote = !state.simple_quote;
		else if (input[i] == '\"' && !state.simple_quote)
			state.double_quote = !state.double_quote;
		else
			result[j++] = input[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}
