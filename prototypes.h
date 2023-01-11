/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 12:08:36 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/11 10:34:37 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H
# include "structures.h"
# include "libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>

int		parsing_line(char *line, t_init *init);
void	cut_sentence(t_init *init, char *line, int *i, int j);
void	lexer(t_init *init);
char	*take_quotes(t_list *tmp, t_lexer *new, int i, int j);
char	*take_args(t_list **tmp, t_lexer *new, int i, int j);
int		check_builtin(char *word);
void    free_new_lexer(t_lexer *new, char *word);
char	**get_path(char **envp);
void	free_list(t_init *init);
char	*is_redirection(t_lexer *lexer, t_list **sentence);
void	free_list(t_init *init);
t_lexer	*is_pipe(t_list *tmp, t_lexer *new, t_init *init, char *word);
char	*init_files(t_init *init);
void	signal_int(int signal);
void	signal_heredoc(int signal);
void	free_pipe(t_init *init);
void	close_fd_pipe(t_init *init);
void	close_files(t_init *init);
void	exec_cmd(t_lexer *tmp, t_init *init, int i);
void	parent_proc(t_init *init);
int		pipex(t_init *init);
void	execution(t_lexer *lexer, t_init *init, int i);
int		var_len(char *str);
void	free_env(t_init *init);
void	free_var(t_init *init);
void	free_before_exit(t_init *init);
void	do_dup(t_lexer *tmp, t_init *init, int i);
void	close_pipes_before_dup(t_init *init, int i, int j);
void	close_after_dup(t_init *init, t_lexer *tmp, int i);
void	free_before_exit(t_init *init);
int		check_before_dup(t_lexer *tmp, t_init *init);
char	*take_quotes(t_list *tmp, t_lexer *new, int i, int j);
int		check_builtin(char *word);
int		check_envariables(char *word, t_init *init);
int		search_env_var(t_env *tmp, char *word, t_lexer *new);
char	*search_variabl(char *var_name, t_env *tmp, t_lexer *lexer);
char	*write_variable(int *i, char *str, t_init *init, t_lexer *lexer);
void	is_cmd(t_lexer *tmp, t_init *init);
void	is_pwd(t_init *init, t_lexer *tmp, int i);
void	is_env(t_init *init, t_lexer *tmp, int i);
void	is_unset(t_init *init, t_env **env, t_env **var);
void	is_echo(t_init *init, t_lexer *lexer, int i);
void	is_echo_var(t_init *init, t_lexer *lexer, int i);
void	is_cd(t_lexer *tmp);
char	*is_env_var(t_init *init, char *word, t_lexer *new);
int		is_heredoc(t_red *tmp, t_lexer *tmp_lexer, t_init *init);
void	is_export(t_init *init, t_env **env, t_env **var);
int		in_env(char *arg, t_env **env);
int		in_var(char *arg, t_env **env, t_env **var);
void	is_exit(t_init *init);
void	print_list(t_env **list);
void	close_fd_heredoc(t_lexer *lexer);

#endif
