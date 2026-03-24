/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimega2 <jaimega2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 14:12:20 by jimmy             #+#    #+#             */
/*   Updated: 2026/01/20 13:47:43 by jaimega2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_error(char *msg)
{
	write(2, msg, ft_strlen(msg));
}

void	perror_multi(char *s1, char *s2, char *s3, char *s4)
{
	if (s1)
		write(2, s1, ft_strlen(s1));
	if (s2)
		write(2, s2, ft_strlen(s2));
	if (s3)
		write(2, s3, ft_strlen(s3));
	if (s4)
		write(2, s4, ft_strlen(s4));
}

int	ft_isspace_shell(char c)
{
	return (c == ' ' || c == '\t' || c == '\v'
		|| c == '\f' || c == '\r');
}
