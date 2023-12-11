/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:27:53 by aminakov          #+#    #+#             */
/*   Updated: 2023/12/11 13:15:44 by aminakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 256 
# endif

# if (BUFFER_SIZE < 0)
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdarg.h>

//# define RES "\001\033[0m\002"
# define RES "\033[0m"
# define BLINKING "\033[5m"
# define RED "\033[31m"
# define BUFF_RED "\001\033[41m\002"
# define GREEN "\033[32m"
# define BUFF_GREEN "\033[42m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define PURPLE "\033[35m"
# define LBL "\033[36m"
# define GREY "\033[37m"
# define WHITE "\033[39m"

typedef long unsigned int	t_size_t;
typedef long unsigned int	t_long_t;
typedef unsigned int		t_uint;
typedef struct s_list
{
	char			*word;
	int				is_special_tkn;
	struct s_list	*next;
}				t_list;

//ft_isalpha.c
int			ft_isalpha(int ch);
//ft_isdigit.c
int			ft_isdigit(int ch);
//ft_isalnum.c
int			ft_isalnum(int ch);
//ft_isascii.c
int			ft_isascii(int ch);
//ft_isprint.c
int			ft_isprint(int ch);

//ft_strlen.c
t_size_t	ft_strlen(const char *str);
//ft_memset.c
void		*ft_memset(void *str, int ch, t_size_t n);
//ft_bzero.c
void		ft_bzero(void *str, t_size_t n);
//ft_memcpy.c
void		*ft_memcpy(void *dest, const void *src, t_size_t n);
//ft_memmove.c
void		*ft_memmove(void *dest, const void *src, t_size_t n);

//ft_strlcpy.c
t_size_t	ft_strlcpy(char *dest, const char *src, t_size_t size);
//ft_strlcat.c
t_size_t	ft_strlcat(char *dest, const char *src, t_size_t size);
//ft_strncmp.c
int			ft_strncmp(const char *str1,
				const char *str2,
				t_size_t n);
//ft_memcmp.c
int			ft_memcmp(const void *s1,
				const void *s2,
				t_size_t n);
//ft_strnstr.c
char		*ft_strnstr(const char *big, const char *little,
				t_size_t len);

//ft_toupper.c
int			ft_toupper(int ch);
//ft_tolower.c
int			ft_tolower(int ch);
//ft_strchr.c
char		*ft_strchr(const char *str, int c);
//ft_strrchr.c
char		*ft_strrchr(char *str, int c);
//ft_memchr.c
void		*ft_memchr(void *str, int ch, t_size_t n);

//ft_atoi.c
int			ft_isspace(char ch);
int			ft_atoi(const char *str);
int			ft_atoi_err(const char *str, int *err);
void		deal_with_sign(char const **str, int *sign);
int			overflow(int res, int oldres, int sign, char ch);

//ft_atoi_0x.c
int			ft_is_generalized_digit(char ch);
int			ft_atoi_0x(const char *str);

//ft_calloc
void		*ft_calloc(t_size_t num, t_size_t size);

//ft_strdup
char		*ft_strdup(const char *str);
char		*ft_strndup(const char *str, size_t n);

//////////////////////////////////
//////////////////////////////////
// PART 2

//ft_substr.c
char		*ft_substr(char const *str, unsigned int start, t_size_t len);

//ft_strjoin.c
char		*ft_strjoin(char const *str1, char const *str2);

//ft_strtrim.c extra functions: [is_in], [allocate_one]
char		*ft_strtrim(char const *str1, char const *set);

//ft_split.c extra functions: [allocate_space_for_res_arr]
t_size_t	ft_wc(char const *str, char delimiter);
t_size_t	ft_len_till_delimiter(const char *str, char ch);
t_size_t	ft_copy(char *dest, char const *src, char delimiter);
char		**ft_split(char const *str, char ch);

//ft_split_aux.c
void		free_split(char **arr_str);

//ft_itoa.c extra functions: [ft_allocate_itoa]
t_size_t	ft_int_len(int n);
t_uint		ft_unsigned_int_len_base(t_uint n, t_uint base);
char		*ft_itoa(int n);

//ft_strmapi.c
char		*ft_strmapi(char const *str, char (*f)(unsigned int, char));

//ft_striteri.c
void		ft_striteri(char *str, void (*f)(unsigned int, char*));

//ft_putchar_fd.c
int			ft_putchar_fd(char ch, int fd);

//ft_putstr_fd.c
int			ft_putstr_fd(char *str, int fd);

//ft_putendl_fd.c
void		ft_putendl_fd(char *str, int fd);

//ft_putnbr_fd.c
int			ft_set_tens_putnbr_fd(int n, int *tens);
int			ft_putnbr_fd(int n, int fd);
int			ft_putnbr_senza_minus_fd(int n, int fd);

//ft_putnbr_base_fd.c
int			ft_set_pows_putnbr_fd(t_uint n, t_uint *pows, \
							t_uint base);
int			ft_putnbr_base_fd(t_uint n, t_uint base, \
						int uplow, int fd);
int			ft_set_pows_putnbr_fd_long(t_long_t n, \
				t_long_t *pows, t_long_t base);
int			ft_putnbr_base_fd_long(t_long_t n, t_long_t base, \
						int uplow, int fd);
int			place_digit(int digit, int uplow, int fd);

////////////////////////////////////////////
////////////////////////////////////////////
//BONUS LIBFT ORIGINAL

//ft_lstnew.c
t_list		*ft_lstnew(char const *str, int beg, int end);
void		ft_print_list(t_list const *list);

//ft_lstadd_front
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_free_lst(t_list **node);

//ft_lstsize.c
int			ft_lstsize(t_list *lst);

//ft_lstlast.c
t_list		*ft_lstlast(t_list *lst);

//ft_lstadd_back.c
void		ft_lstadd_back(t_list **lst, t_list *new);

//ft_lstdelone.c
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lst_del_one_node(t_list **head, t_list *node);
void		basic_free_of_node(t_list *node);

//ft_lstclear.c
void		ft_lstclear(t_list **lst, void (*del)(void *));

//ft_lstiter.c
void		ft_lstiter(t_list *lst, void (*f)(void *));

//ft_lstmap.c extra functions: [set_node_list]
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *),
				void (*del)(void *));

////////////////////////////////////////////
////////////////////////////////////////////
//FT_PRINTF

// ft_printf.c
int			get_class(char ch);
int			treat_four(int num, char ch, t_uint *res, int fd);
int			treat_eight(char *ptr, char ch, t_uint *res, int fd);
int			treat48(va_list *args, char ch, t_uint *res, int fd);
int			ft_printf(const char *str, ...);
int			is_bonus_ch(char ch);

// ft_printf_fd.c
int			ft_printf_fd(int fd, const char *str, ...);

// ft_printf_bonus.c
void		treatbonus(va_list *args, const char **str, t_uint *res);
int			treat_dot(va_list *args, const char **str, \
					t_uint *res, t_uint width);
int			treat_dot_s(va_list *args, t_uint *res, t_uint width);
void		treat_zero(va_list *args, const char **str, t_uint *res, \
							t_uint width);
int			put_nbr_width(va_list *args, const char **str, \
					t_uint width, int flag4minus);

// ft_printf_bonus_aux.c
void		treat_sharp(va_list *args, const char **str, t_uint *res, \
							t_uint width);
t_uint		ft_putoxx_fd(t_uint num, char char4base, int fd);
int			work_space_plus_fd(va_list *args, const char **str, \
						char symb, int fd);
t_uint		treat_space_plus(va_list *args, const char **str, char symb, \
							t_uint width);

// ft_printf_bonus_second_aux.c
int			is_bonus_ch(char ch);
int			read_width(const char **str);
int			treat_minus(va_list *args, const char **str, \
						t_uint *res, t_uint width);
int			treat_digit(va_list *args, const char **str, \
					t_uint *res, t_uint width);

////////////////////////////////////////////
////////////////////////////////////////////
//GET_NEXT_LINE MANDATORY

// get_next_line.c
char		*get_next_line(int fd);
char		*gnl_eou(int fd, char **buffer);
int			doalloc(char **buffer, char *curr_line, int iter);
char		*doiferrornl(char **buffer, char *curr_line, int opt, t_size_t pos);
char		*doifeof(char **buffer, char *curr_line, t_size_t smbcnt);

// get_next_line_utils.c
t_size_t	ft_strlen_gnl(char *str);
int			place_beg_noalloc(char *src, char **dst, t_size_t MAXSIZE);
int			place_end_alloc(char *src, char **dst, t_size_t MAXSIZE);
t_size_t	getpos(char smb, char *str);
int			doread(int fd, char **buffer, t_size_t *smbcnt);

#endif
