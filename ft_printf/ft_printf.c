/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 16:33:35 by gpaeng            #+#    #+#             */
/*   Updated: 2021/01/16 13:45:36 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//1. %가 나오면 flag(width랑 .precision만) 조사
//2. s,d,x에 맞춰서 출력을 해줍니다.(조건 중요)
// <조건>
// %s
// va_arg(ap, char *);
// 1. s == NULL 이면 s = "(null)";
// 2. dot && precision < len  =>>> len = precision;
// 3. 빈칸은 width - len
// 4. 문자는 len

//%d
// va_arg(ap, int);
// 1. n == 0 && dot =>>> len = 0;
// 2. dot && precision > len =>>> zero = precision - len;
// 3. 빈칸은 width - (zero + len);
// 4. n == 0 && dot =>>> return ;
// 5. 숫자는 len;

//%x
// va_arg(ap, unsigned int)
// 1. n == 0 && dot =>>> len = 0;
// 2. dot && precision > len  =>>> len = precision - len;
// 3. 빈칸은 width - (zero + len);
// 4. n == 0 && dot =>>> return ;
// 5. 문자는 len;

#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>

typedef struct	s_fopt
{
	int		len;
	int		width;
	int		dot;
	int		precision;
	int		negative;
	int		zero_count;
	int		lprint;
}				t_fopt;

static void	ft_init_flags(t_fopt *fopt)
{
	fopt->len = 0;
	fopt->width = 0;
	fopt->dot = 0;
	fopt->precision = 0;
	fopt->negative = 0;
	fopt->zero_count = 0;
}

static void	ft_putchar(char c, t_fopt *fopt)
{
	write(1, &c, 1);
	fopt->lprint += 1;
}

static void	ft_putnstr(t_fopt *fopt, const char *s, const int n)
{
	int idx;

	idx = 0;
	while (idx < n && s[idx])
	{
		ft_putchar(s[idx], fopt);
		idx++;
	}
}

static int	ft_strlen(const char *s)
{
	int	idx;

	idx = 0;
	while (s[idx])
		idx++;
	return (idx);
}

static int	ft_num_baselen(long n, int base_len)
{
	int idx;

	idx = 1;
	while (n >= base_len)
	{
		n /= base_len;
		idx++;
	}
	return (idx);
}

static void	ft_putnbr_base(t_fopt *fopt, long n, int base_len, const char *base)
{
	if (n >= base_len)
		ft_putnbr_base(fopt, n / base_len, base_len, base);
	ft_putchar(base[n % base_len], fopt);
}

static void	ft_print_char(t_fopt *fopt, int len, char c)
{
	int	idx;

	idx = 0;
	while (idx < len)
	{
		ft_putchar(c, fopt);
		idx++;
	}
}

static void	ft_check_flags(char **str, t_fopt *fopt)
{
	(*str)++;
	if (**str >= '0' && **str <= '9')
	{
		while (**str >= '0' && **str <= '9')
		{
			fopt->width = (fopt->width * 10) + (**str - '0');
			(*str)++;
		}
	}
	if (**str == '.')
	{
		(*str)++;
		fopt->dot = 1;
		while (**str >= '0' && **str <= '9')
		{
			fopt->precision = (fopt->precision * 10) + (**str - '0');
			(*str)++;
		}
	}
}

static void	ft_print_s(va_list ap, char **str, t_fopt *fopt)
{
	char	*s;

	(*str)++;
	s = va_arg(ap, char *);
	if (!s)
		s = "(null)";
	fopt->len = ft_strlen(s);
	if (fopt->dot && fopt->precision < fopt->len)
		fopt->len = fopt->precision;
	ft_print_char(fopt, fopt->width - fopt->len, ' ');
	ft_putnstr(fopt, s, fopt->len);
}

static void	ft_print_d(va_list ap, char **str, t_fopt *fopt)
{
	long	n;

	(*str)++;
	n = va_arg(ap, int);
	if (n < 0)
	{
		fopt->negative = 1;
		n *= -1;
	}
	fopt->len = ft_num_baselen(n, 10);
	if (n == 0 && fopt->dot)
		fopt->len = 0;
	if (fopt->dot && fopt->precision > fopt->len)
		fopt->zero_count = fopt->precision - fopt->len;
	ft_print_char(fopt, fopt->width - (fopt->zero_count + fopt->len), ' ');
	fopt->negative ? ft_putchar('-', fopt) : 0;
	ft_print_char(fopt, fopt->zero_count, '0');
	if (fopt->dot && n == 0)
		return ;
	ft_putnbr_base(fopt, n, 10, "0123456789");
}

static void	ft_print_x(va_list ap, char **str, t_fopt *fopt)
{
	unsigned int	n;

	(*str)++;
	n = va_arg(ap, unsigned int);
	fopt->len = ft_num_baselen(n, 16);
	if (n == 0 && fopt->dot)
		fopt->len = 0;
	if (fopt->dot && fopt->precision > fopt->len)
		fopt->zero_count = fopt->precision - fopt->len;
	ft_print_char(fopt, fopt->width - (fopt->zero_count + fopt->len), ' ');
	ft_print_char(fopt, fopt->zero_count, '0');
	if (fopt->dot && n == 0)
		return ;
	ft_putnbr_base(fopt, n, 16, "0123456789abcdef");
}

int			ft_printf(const char *str, ...)
{
	t_fopt	fopt;
	va_list ap;
	char *strptr;

	va_start(ap, str);
	strptr = (char *)str;
	ft_init_flags(&fopt);
	fopt.lprint = 0;
	while (*strptr)
	{
		if (*strptr == '%')
		{
			ft_check_flags(&strptr, &fopt);
			if (*strptr == 's')
				ft_print_s(ap, &strptr, &fopt);
			else if (*strptr == 'd')
				ft_print_d(ap, &strptr, &fopt);
			else if (*strptr == 'x')
				ft_print_x(ap, &strptr, &fopt);
			ft_init_flags(&fopt);
		}
		else
		{
			ft_putchar(*strptr, &fopt);
			strptr++;
		}
	}
	va_end(ap);
	return (fopt.lprint);
}
