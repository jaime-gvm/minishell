/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimega2 <jaimega2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 11:51:23 by rnuno-im          #+#    #+#             */
/*   Updated: 2026/01/20 14:45:24 by jaimega2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_path
{
	char	*full;
	char	*path;
	char	**paths;
	char	*cmd;
	char	*tmp;
	int		i;
}	t_path;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	char			*infile;
	char			*outfile;
	char			*heredoc;
	int				type;
	char			*full_path;
	int				fd_in;
	int				fd_out;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_parse_data
{
	char	**tokens;
	t_cmd	*head;
	t_cmd	*current;
	char	**args_tmp;
	int		arg_count;
	int		i;
	int		error;
}	t_parse_data;

typedef struct s_quote_state
{
	int		simple_quote;
	int		double_quote;
	char	*current_token;
	int		token_len;
}	t_quote_state;

typedef struct s_expand_data
{
	char	*input;
	char	*result;
	int		*i;
	int		*j;
}	t_expand_data;

typedef struct s_preprocess
{
	char	*input;
	char	*result;
	int		*i;
	int		*j;
}	t_preprocess;

typedef struct s_pipeline
{
	t_cmd	*cmds;
	char	***envp;
	int		**pipes;
	int		count;
	pid_t	last_pid;
}	t_pipeline;

#endif