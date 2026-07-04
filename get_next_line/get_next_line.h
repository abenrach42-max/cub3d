/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenrach <abenrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:12:24 by abenrach          #+#    #+#             */
/*   Updated: 2026/06/26 17:43:07 by abenrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*gets_line(char *tab);
size_t	count_words(const char *s);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*join_stash(char *stash, char *buf);
char	*fill_tab(int fd, char *stash);
char	*update_tab(char *stash);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

#endif
