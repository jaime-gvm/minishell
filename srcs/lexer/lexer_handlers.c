/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimega2 <jaimega2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 13:14:12 by jaimega2          #+#    #+#             */
/*   Updated: 2026/01/19 13:05:31 by jaimega2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*handle_heredoc(char *input, char *result, int *i, int *j)
{
	if (*i > 0 && !ft_isspace_shell(input[*i - 1]))
		result[(*j)++] = ' ';
	result[(*j)++] = '<';
	result[(*j)++] = '<';
	if (input[*i + 2] && !ft_isspace_shell(input[*i + 2]))
		result[(*j)++] = ' ';
	*i += 2;
	return (result);
}

char	*handle_append(char *input, char *result, int *i, int *j)
{
	if (*i > 0 && !ft_isspace_shell(input[*i - 1]))
		result[(*j)++] = ' ';
	result[(*j)++] = '>';
	result[(*j)++] = '>';
	if (input[*i + 2] && !ft_isspace_shell(input[*i + 2]))
		result[(*j)++] = ' ';
	*i += 2;
	return (result);
}

char	*handle_pipe(char *input, char *result, int *i, int *j)
{
	if (*i > 0 && !ft_isspace_shell(input[*i - 1]))
		result[(*j)++] = ' ';
	result[(*j)++] = '|';
	if (input[*i + 1] && !ft_isspace_shell(input[*i + 1]))
		result[(*j)++] = ' ';
	(*i)++;
	return (result);
}

char	*handle_redirect_out(char *input, char *result, int *i, int *j)
{
	if (*i > 0 && !ft_isspace_shell(input[*i - 1]))
		result[(*j)++] = ' ';
	result[(*j)++] = '>';
	if (input[*i + 1] && !ft_isspace_shell(input[*i + 1]))
		result[(*j)++] = ' ';
	(*i)++;
	return (result);
}

char	*handle_redirect_in(char *input, char *result, int *i, int *j)
{
	if (*i > 0 && !ft_isspace_shell(input[*i - 1]))
		result[(*j)++] = ' ';
	result[(*j)++] = '<';
	if (input[*i + 1] && !ft_isspace_shell(input[*i + 1]))
		result[(*j)++] = ' ';
	(*i)++;
	return (result);
}
