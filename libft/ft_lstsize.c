/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 16:43:40 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/06 11:20:18 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lexersize(t_lexer *lexer)
{
	int	i;

	i = 0;
	while (lexer)
	{
		lexer = lexer->next;
		i++;
	}
	return (i);
}

int	ft_envsize(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		env = env->next;
		i++;
	}
	return (i);
}
