/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnuno-im <rnuno-im@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 13:44:08 by rnuno-im          #+#    #+#             */
/*   Updated: 2025/12/18 14:16:51 by rnuno-im         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_export(char **envp)
{
	int	i;
	int	j;

	i = -1;
	while (envp[++i])
	{
		printf("declare -x ");
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
		{
			printf("%c", envp[i][j]);
			j++;
		}
		if (envp[i][j] == '=')
		{
			printf("=\"");
			j++;
			while (envp[i][j])
				printf("%c", envp[i][j++]);
			printf("\"");
		}
		printf("\n");
	}
}

int	valid_name(char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	var_indx(char **envp, char *var, int len)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if ((ft_strncmp(envp[i], var, len) == 0 && (envp[i][len] == '='))
			|| envp[i][len] == '\0')
			return (i);
		i++;
	}
	return (-1);
}

void	update_var(char ***envp, char *arg, int index)
{
	char	*new_var;

	new_var = ft_strdup(arg);
	if (!new_var)
		return ;
	free((*envp)[index]);
	(*envp)[index] = new_var;
}

void	add_var(char ***envp, char *arg)
{
	int		i;
	char	**new_envp;

	i = 0;
	while ((*envp)[i])
		i++;
	new_envp = malloc(sizeof(char *) * (i + 2));
	if (!new_envp)
		return ;
	i = -1;
	while ((*envp)[++i])
		new_envp[i] = (*envp)[i];
	new_envp[i] = ft_strdup(arg);
	if (!new_envp[i])
	{
		while (--i >= 0)
			free(new_envp[i]);
		free(new_envp);
		return ;
	}
	new_envp[i + 1] = NULL;
	free(*envp);
	*envp = new_envp;
}
