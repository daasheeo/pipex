/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesmunoz <jesmunoz@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 19:20:21 by jesmunoz          #+#    #+#             */
/*   Updated: 2024/01/09 13:04:14 by jesmunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "limits.h"
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/**
 * @param c This is the character to be checked.
 * @note This function displays 1 if c is
 * an alphabetic character, and 0 if not.
 */
int					ft_isalpha(int c);

/**
 * @param c This is the character to be checked.
 * @note This function displays 1 if c is
 * a digit, and 0 if not.
 */
int					ft_isdigit(int c);

/**
 * @param c This is the character to be checked.
 * @note This function displays 1 if c is
 * an alphanumeric character, and 0 if not.
 */
int					ft_isalnum(int c);

/**
 * @param c This is the character to be checked.
 * @note This function displays 1 if c is
 * an ASCII character, and 0 if not.
 */
int					ft_isascii(int c);

/**
 * @param c This is the character to be checked.
 * @note This function displays 1 if c is
 * a printable character, and 0 if not.
 */
int					ft_isprint(int c);

/**
 * @param s This is the string to be measured.
 * @note This function computes the length of the string s.
 */
size_t				ft_strlen(const char *s);

/**
 * @param b This is the pointer to the block of memory to fill.
 * @param c This is the value to be set. The value is passed as an int,
 * @param len This is the number of bytes to be set to the value.
 * @note This function copies n bytes
 * from memory area src to memory area dst.
 */
void				*ft_memset(void *b, int c, size_t len);

/**
 * @param c This is the character to be uppercased.
 * @note This function converts the letter c
 * to uppercase, if possible.
 */
int					ft_toupper(int c);

/**
 * @param c This is the character to be lowercased.
 * @note This function converts the letter c
 * to lowercase, if possible.
 */
int					ft_tolower(int c);

/**
 * @param s This is the string to be used.
 * @param c This is the character to be found.
 * @note This function finds the first occurrence
 * of the character c in the string s.
 */
char				*ft_strchr(const char *s, int c);

/**
 * @param s This is the string to be used.
 * @param c This is the character to be found.
 * @note This function finds the last occurrence
 * of c (converted to a char) in the string pointed to by s.
 * The terminating null character is considered to be part
 * of the string; therefore if c is `\0',
	the functions locate the terminating `\0'.
 */
char				*ft_strrchr(const char *s, int c);

/**
 * @param s1 This is the first string to be compared.
 * @param s2 This is the second string to be compared.
 * @param n This is the maximum number of characters to be compared.
 * @note This function compares string1 and string2 to the maximum of count.
 */
int					ft_strncmp(const char *s1, const char *s2, size_t n);

/**
 * @param s This is the string to be used.
 * @param n This is the number of bytes to be set to the value.
 * @note This function erases the data in the n bytes of the memory
 * starting at the location pointed to by s,
 * by writing zeros (bytes containing '\0') to that area.
 */
void				ft_bzero(void *s, size_t n);

/**
 * @param dst This is a pointer to the destination array where the
 * content is to be copied, type-casted to a pointer of type void*.
 * @param src This is a pointer to the source of data
 * to be copied, type-casted to a pointer of type void*.
 * @param len This is the number of bytes to be copied.
 * @note This function appends the string pointed to by s2
 * to the end of the string pointed to by s1.
 */
void				*ft_memmove(void *dst, const void *src, size_t len);

/**
 * @param dst This is pointer to the destination array where the 
 * content is to be copied, type-casted to a pointer of type void*.
 * @param src This is pointer to the source of data to be copied, 
 * type-casted to a pointer of type void*.
 * @param n This is the number of bytes to be copied.
 * @note This function copies n characters from src to dst and returns dst.
*/
void				*ft_memcpy(void *dst, const void *src, size_t n);

/**
 * @param dst Is the null-terminated string to be modified or appended.
 * @param src Is the string to be appended.
 * @param dstsize Is the size of the destination buffer.
 * @note This function appends the NUL-terminated string src to the end of dst 
 * and returns the total length of the string they tried to create.
 *
*/
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);

/**
 * @param dst Is the null-terminated string to be modified 
 * @param src Is the null-terminated string to be copied.
 * @param dstsize Nothing will be written beyond dst+size-1.
 * @note This function function copies up to size - 1 characters from 
 * the NUL-terminated string src to dst, NUL-terminating the result.
 *
*/
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);

/**
 * @param str Is the string to be converted.
 * @note This function converts the initial
 * portion of the string pointed to by str to 
 * int representation.
*/
int					ft_atoi(const char *str);

/**
 * @param s This is the pointer to the block of memory
 *  where the search is performed.
 * @param c This is the character to be found.
 * @param n This is the number of bytes to be analyzed.
 * @note This function locates the first occurrence of c 
 * (converted to an unsigned char) in string s.
*/
void				*ft_memchr(const void *s, int c, size_t n);

/**
 * @param s1 This is the string to duplicate.
 * @note This function is used to duplicate a string. 
 * It returns a pointer to null-terminated byte string
*/
char				*ft_strdup(const char *s1);

/**
 * @param count This is the number of elements to be allocated.
 * @param size This is the size of elements.
 * @note This function allocates memory for an array of count elements
*/
void				*ft_calloc(size_t count, size_t size);

/**
 * @param s1 This is the string to be compared.
 * @param s2 This is the string to be compared.
 * @param n This is the maximum number of characters to be compared.
 * @note This function compares string1 and string2 to the maximum of count.
*/
int					ft_memcmp(const void *s1, const void *s2, size_t n);

/**
 * @param s The field, expression, or literal value to extract 
 * the substring from.
 * @param start The starting character position of the substring.
 * @param len The number of characters in the substring.
 * @note Returns a specified substring from a string.
*/
char				*ft_substr(char const *s, unsigned int start, size_t len);

/**
 * @param s1 This is the first string to be joined.
 * @param s2 This is the string to be joined with s1.
 * @note Returns the new string that is result of joining 
 * s1 and s2, if fails returns NULL.
*/
char				*ft_strjoin(char const *s1, char const *s2);

/**
 * @param str This is the string to be searched 
 * @param to_find This is the string to be searched.
 * @param len This is the maximum number of bytes to be searched. 
 * @note 
*/
char				*ft_strnstr(const char *str, const char *to_find,
						size_t len);

/**
 * @param s1 This is the string to be trimmed.
 * @param set This is the reference set of characters to trim.
 * @note Returns the new string that is result of trimming.
*/						
char				*ft_strtrim(char const *s1, char const *set);

/**
 * @param c This is the character to be printed.
 * @param fd This is the file descriptor on which to write.
 * @note This function outputs the character c to the given file descriptor.
*/
void				ft_putchar_fd(char c, int fd);

/**
 * @param s This is the string to be printed.
 * @param fd This is the file descriptor on which to write.
 * @note This function outputs the string s to the given file descriptor.
*/
void				ft_putstr_fd(char *s, int fd);

/**
 * @param s This is the string to be printed.
 * @param fd This is the file descriptor on which to write.
 * @note This function outputs the string s to the given file descriptor,
 * followed by a newline.
*/
void				ft_putendl_fd(char *s, int fd);

/**
 * @param n This is the integer to be printed.
 * @param fd This is the file descriptor on which to write.
 * @note This function outputs the integer n to the given file descriptor.
*/
void				ft_putnbr_fd(int n, int fd);

/**
 * @param n This is the integer to be printed.
 * @note This function outputs the integer n converted to a string,
*/
char				*ft_itoa(int n);

/**
 * @param s This is the string to be iterated.
 * @param f This is the function to be applied to each character.
 * @note This function applies the function f to each character of the string s
 * to create a new string (with malloc(3)) resulting from successive applications
 * of f.
*/
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/**
 * @param s This is the string to be iterated.
 * @param c This is the function to be applied to each character.
 * @note Applies the function f to each character of the string passed
 * as argument, and passing its index as first argument. Each character
 * is passed by address to f to be modified if necessary.
*/
void				ft_striteri(char *s, void (*f)(unsigned int, char *));

/**
 * @param s This is the string to be splitted.
 * @param c This is the delimiter character.
 * @note Allocates (with malloc(3)) and returns an array of strings obtained
 * by splitting ’s’ using the character ’c’ as a delimiter. The array must be
 * ended by a NULL pointer.
*/
char				**ft_split(char const *s, char c);

/**
 * @param content This is the content to create the new element with.
 * @note Allocates (with malloc(3)) and returns a new element. The variable
 * ’content’ is initialized with the value of the parameter ’content’. The
 * variable ’next’ is initialized to NULL.
*/
t_list				*ft_lstnew(void *content);

/**
 * @param lst The address of a pointer to an element.
 * @param new The address of a pointer to the element to be added to the list.
 * @note Adds the element ’new’ at the beginning of the list.
*/
void				ft_lstadd_front(t_list **lst, t_list *new);

/**
 * @param lst The beginning of the list.
 * @note Counts the number of elements in a list.
*/
int					ft_lstsize(t_list *lst);

/**
 * @param lst The beginning of the list.
 * @note Returns the last element of the list.
*/
t_list				*ft_lstlast(t_list *lst);

/**
 * @param lst The beginning of the list.
 * @param new The address of a pointer to the element to be added to the list.
 * @note Adds the element ’new’ at the end of the list.
*/
void				ft_lstadd_back(t_list **lst, t_list *new);

/**
 * @param lst The beginning of the list.
 * @param del The address of the function used to delete the content of the
 * element.
 * @note Deletes and frees the given element and every successor of that element,
 * using the function ’del’ and free(3). Finally, the pointer to the list must
 * be set to NULL.
*/
void				ft_lstdelone(t_list *lst, void (*del)(void *));

/**
 * @param lst The beginning of the list.
 * @param del The address of the function used to delete the content of the
 * element.
 * @note Deletes and frees the given element and every successor of that element,
 * using the function ’del’ and free(3). Finally, the pointer to the list must
 * be set to NULL.
*/
void				ft_lstclear(t_list **lst, void (*del)(void *));

/**
 * @param lst The beginning of the list.
 * @param f The address of the function used to iterate on the list.
 * @note Iterates the list ’lst’ and applies the function ’f’ to the content of
 * each element.
*/
void				ft_lstiter(t_list *lst, void (*f)(void *));

/**
 * @param lst The beginning of the list.
 * @param f The address of the function used to iterate on the list.
 * @param del The address of the function used to delete the content of the
 * element.
 * @note Iterates the list ’lst’ and applies the function ’f’ to the content of
 * each element. Creates a new list resulting of the successive applications of
 * the function ’f’. The ’del’ function is used to delete the content of an
 * element if needed.
*/
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
#endif