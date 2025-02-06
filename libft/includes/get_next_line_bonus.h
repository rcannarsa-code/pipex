#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif
# ifndef FD_MAX
#  define FD_MAX 1024
# endif
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

char	*join_buffer(char *joined, char *buffer, ssize_t bytes_read);
char	*read_and_join(char *stash, int fd);
char	*extract_line(char *line);
void	extract_stash(const char *line, char *stash);
size_t	gnl_strlen(const char *s);
size_t	gnl_strlcpy(char *dest, const char *src, size_t size);
char	*gnl_smart_strjoin(char *s1, char *s2, int free1, int free2);
size_t	gnl_strlcat(char *dest, const char *src, size_t size);
int		check_new_line(char *buffer);
char	*get_next_line(int fd);

#endif