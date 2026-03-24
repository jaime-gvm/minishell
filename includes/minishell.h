/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimega2 <jaimega2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 13:37:08 by rnuno-im          #+#    #+#             */
/*   Updated: 2026/01/20 15:09:10 by jaimega2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include "../libft/libft.h"
# include "structs.h"

extern int	g_exit_status;

void	shell_loop(char **envp);
char	**tokenizer(char *input);
char	*preprocess_input(char *input);
void	process_operators(char *input, char *result, int *i, int *j);
char	*handle_heredoc(char *input, char *result, int *i, int *j);
char	*handle_append(char *input, char *result, int *i, int *j);
char	*handle_pipe(char *input, char *result, int *i, int *j);
char	*handle_redirect_out(char *input, char *result, int *i, int *j);
char	*handle_redirect_in(char *input, char *result, int *i, int *j);
void	process_heredoc(t_preprocess *data, t_quote_state *state);
void	process_append(t_preprocess *data, t_quote_state *state);
void	process_pipe(t_preprocess *data, t_quote_state *state);
void	process_redirect_out(t_preprocess *data, t_quote_state *state);
void	process_redirect_in(t_preprocess *data, t_quote_state *state);
void	update_quote_state(char c, t_quote_state *state);
int		is_space_outside_quotes(char c, t_quote_state *state);
int		count_tokens(char *input);
int		calculate_token_length(char *input, int *pos, t_quote_state *state);
void	copy_token_content(char *input, char *token, int start, int end);
char	*extract_one_token(char *input, int *pos, t_quote_state *state);
void	free_tokens(char **tokens, int count);
int		handle_quote_error(char **tokens, char *processed);
int		extract_all_tokens(char **tokens, char *processed,
			t_quote_state *state);
int		handle_redirections(t_cmd *cmds, char **envp);
void	execute_command(t_cmd *cmds, char ***envp, int should_exit);
void	execute_helper(t_cmd *cmds, char ***envp, int should_exit);
void	executor(t_cmd *cmd, char ***envp);
void	exec_child(char *cmd_path, char **args, char **envp);
void	exec_in_child(char *cmd_path, char **args, char **envp);
void	free_split(char **arr);
char	*find_cmd(char *cmd, char **envp);
void	check_access(char *cmd);
char	*build_path(char *dir, char *cmd);
char	*check_envp_path(t_path *all);
int		is_builtin(char *cmd);
int		exec_builtin(char **args, char ***envp);
int		ft_cd(char **args, char ***envp);
int		ft_echo(char **args);
int		ft_env(char **envp);
int		ft_exit(char **args);
int		ft_export(char **args, char ***envp);
int		ft_pwd(void);
int		ft_unset(char **args, char ***envp);
char	**dup_envp(char **envp);
void	free_envp(char **envp);
void	print_export(char **envp);
int		valid_name(char *str);
int		var_indx(char **envp, char *var, int len);
void	update_var(char ***envp, char *arg, int index);
void	add_var(char ***envp, char *arg);
t_cmd	*parse_commands(char *processed);
t_cmd	*create_cmd_node(void);
void	free_cmd_list(t_cmd *cmds);
void	debug_print_list(t_cmd *list);
void	debug_print_args(char **args);
void	add_arg_to_list(char ***args, char *token, int *count);
void	add_cmd_to_list(t_cmd **head, t_cmd *new_node);
void	handle_pipe_token(t_parse_data *data);
void	handle_input_redirect_token(t_parse_data *data);
void	handle_output_redirect_token(t_parse_data *data);
void	handle_append_token(t_parse_data *data);
void	handle_heredoc_token(t_parse_data *data);
void	init_parse_data(t_parse_data *data, char **tokens);
void	finalize_cmd(t_parse_data *data);
t_cmd	*create_cmd_node(void);
void	process_tokens(t_parse_data *data);
int		validate_first_token(char **tokens);
void	init_parse_commands(t_parse_data *data, char *processed);
t_cmd	*parse_tokens(char **tokens);
void	process_token_loop(t_parse_data *data, char **tokens);
t_cmd	*finalize_parse(t_parse_data *data);
t_cmd	*process_input(char *input, char **envp);
int		has_quotes(char *token);
int		is_pure_operator(char *token);
void	expand_single_token(char **token, char **envp);
void	print_error(char *msg);
void	perror_multi(char *s1, char *s2, char *s3, char *s4);
int		count_cmds(t_cmd *cmds);
void	close_pipes(int **pipes, int count);
int		**create_pipes(int count);
void	set_fds(int **pipes, int i, int count);
void	free_pipes(int **pipes, int count);
void	execute_child(t_cmd *cmd, t_pipeline *data, int i);
void	fork_and_execute(t_pipeline *data);
void	wait_processes(int count, pid_t last_pid);
void	process_all_heredocs(t_cmd *cmds, char **envp);
void	execute_pipeline(t_cmd *cmds, char ***envp);
int		exec_heredoc(t_cmd *cmds, char **envp);
char	*expand_vars(char *input, char **envp);
char	*get_env_value(char *var_name, char **envp);
int		append_var_value(char *result, char *var_value);
int		expand_exit_status(int *i, char *result);
int		get_var_name_and_value(char *input, int *i, char **envp);
int		calculate_expanded_size(char *input, char **envp);
char	*remove_quotes(char *input);
int		ft_isspace_shell(char c);
void	handle_eof(void);
void	handle_sigint(int sig);
void	setup_signals(void);

#endif