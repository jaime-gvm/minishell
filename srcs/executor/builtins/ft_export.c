/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimega2 <jaimega2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:56:11 by rnuno-im          #+#    #+#             */
/*   Updated: 2026/01/20 13:47:42 by jaimega2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	export_var(char ***envp, char *arg)
{
	char	*pos;
	int		len;
	int		i;

	if (!valid_name(arg))
	{
		perror_multi("minishell: export: '", arg,
			"': not a valid identifier\n", NULL);
		g_exit_status = 1;
		return (1);
	}
	pos = ft_strchr(arg, '=');
	if (pos)
		len = pos - arg;
	else
		len = ft_strlen(arg);
	i = var_indx(*envp, arg, len);
	if (i != -1 && pos)
		update_var(envp, arg, i);
	else if (i == -1)
		add_var(envp, arg);
	return (0);
}

int	ft_export(char **args, char ***envp)
{
	int	i;
	int	ret;

	if (!args[1])
	{
		print_export(*envp);
		return (0);
	}
	ret = 0;
	i = 1;
	while (args[i])
	{
		if (export_var(envp, args[i]) != 0)
			ret = 1;
		i++;
	}
	return (ret);
}
