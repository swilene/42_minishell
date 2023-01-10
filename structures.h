/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:10:13 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/06 11:01:09 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H
# include "libft/libft.h"

/*typedef struct s_lexer
{
	char			*cmd;
	char			**options;
	char			**args;
	char			*redirection;
	char			*file;
	struct s_lexer	*next;
}	t_lexer;*/

typedef struct s_init
{
	int		nb_pipe;
	int		**fd_pipe;
	char	**path;
	char	**envp;
	t_list	*sentence;
	t_lexer	*lexer;
	t_env	*env;
	t_env	*var;
}	t_init;

#endif
