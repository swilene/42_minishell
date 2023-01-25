/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 09:12:03 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/25 14:31:49 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <ctype.h>
# include <stdio.h>
# include <string.h>
# include <strings.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "ft_printf/libftprintf.h"

typedef struct s_env
{
	char			*str;
	struct s_env	*next;
}	t_env;

typedef struct s_red
{
	char			*redirection;
	char			*file;
	int				fd;
	int				mode;
	struct s_red	*next;
}	t_red;

typedef struct s_lexer
{
	char			*cmd;
	char			*prog;
	char			*builtin;
	char			**args;
	t_env			*env_var;
	char			*program;
	char			*file_in;
	int				fd_in;
	char			*file_out;
	int				fd_out;
	char			*file_err;
	int				fd_err;
	char			*heredoc;
	int				fd_heredoc[2];
	int				pid;
	t_red			*red;
	struct s_lexer	*next;
}	t_lexer;

typedef struct s_list
{
	char			*word;
	int				var;
	struct s_list	*next;
}	t_list;

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_isspace(int c);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *nptr);
int		ft_strcmp(char *s1, char *s2);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *big, const char *little, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *s);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_substr(char const *s, int *start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_free(char *s1, char *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_itoa(int n);
char	**ft_split(char const *s, char c);
char	**ft_split_spaces(char const *s);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*get_next_line(int fd);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
t_list	*ft_lstnew(char *word);
t_list	*ft_lstlast(t_list *lst);
t_lexer	*ft_lexerlast(t_lexer *lst);
t_red	*ft_redlast(t_red *lst);
t_env	*ft_envlast(t_env *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lexeradd_back(t_lexer **lst, t_lexer *new);
void	ft_redadd_back(t_red **lst, t_red *new);
void	ft_envadd_back(t_env **lst, t_env *new);
void	ft_dellist(t_list **lst, t_lexer **lexer);
void	ft_dellexer(t_lexer **lexer);
void	free_str(char **str);
t_lexer	*ft_lexernew(void);
t_red	*ft_rednew(void);
t_env	*ft_envnew(char *str);
char	*remove_quotes(char *word, int i, int len);
int		ft_envsize(t_env *env);
int		ft_lexersize(t_lexer *lexer);
void	ft_lstdelone(t_env *tmp, t_env **env, t_env **first);
char	*ft_strcpy(char *dest, char *src);
int		str_isdigit(char *str);
void	ft_lst_add_after(t_list **tmp, t_list *after, t_list *new);

/*void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));*/

#endif
