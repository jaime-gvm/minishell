/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnuno-im <rnuno-im@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:56:13 by rnuno-im          #+#    #+#             */
/*   Updated: 2026/01/13 13:38:59 by rnuno-im         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	find_var(char **envp, char *var)
{
	int	i;
	int	len;

	len = ft_strlen(var);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, len) == 0 && (envp[i][len] == '='))
			return (i);
		i++;
	}
	return (-1);
}

void	remove_var(char ***envp, int index)
{
	int		i;
	int		j;
	int		count;
	char	**new_envp;

	count = 0;
	i = 0;
	while ((*envp)[count])
		count++;
	new_envp = malloc(sizeof(char *) * count);
	if (!new_envp)
		return ;
	j = 0;
	i = 0;
	while (i < count)
	{
		if (i != index)
			new_envp[j++] = (*envp)[i];
		else
			free((*envp)[i]);
		i++;
	}
	new_envp[j] = NULL;
	free(*envp);
	*envp = new_envp;
}

int	ft_unset(char **args, char ***envp)
{
	int	i;
	int	index;

	i = 1;
	while (args[i])
	{
		index = find_var(*envp, args[i]);
		if (index != -1)
		{
			remove_var(envp, index);
		}
		i++;
	}
	return (0);
}
