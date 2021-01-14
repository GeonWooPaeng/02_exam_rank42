
#include <stdarg.h>
#include <unistd.h>

typedef struct	s_flags
{
	int		i;
	int		len;
	int		width;
	int		dot;
	int		precision;
	int		negative;
	int		zero_count;
	int		output;
	va_list	arg;
}				t_flags;

static void	ft_init_flags(t_flags *flags)
{
	flags->i = 0;
	flags->output = 0;
}

static void	ft_clear_flags(t_flags *flags)
{
	flags->len = 0;
	flags->width = 0;
	flags->dot = 0;
	flags->precision = 0;
	flags->negative = 0;
	flags->zero_count = 0;
}

static void	ft_putchar(char c)
{
	write(1, &c, 1);
}

static void	ft_putstr_len(const char *s, const int max_i)
{
	int i;

	i = 0;
	while (i < max_i && s[i])
	{
		ft_putchar(s[i]);
		i++;
	}
}

static int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static int	ft_longlen_base(long nbr, int base_len)
{
	int i;

	i = 1;
	while (nbr >= base_len)
	{
		nbr /= base_len;
		i++;
	}
	return (i);
}

static void	ft_putnbr_base(long nbr, int base_len, const char *base)
{
	// if (nbr >= base_len)
	// {
	// 	ft_putnbr_base(nbr / base_len, base_len, base);
	// 	ft_putnbr_base(nbr % base_len, base_len, base);
	// }
	// else
	// 	ft_putchar(base[nbr]);
	if (nbr >= base_len)
		ft_putnbr_base(nbr / base_len, base_len, base);
	ft_putchar(base[nbr % base_len])
}

static void	ft_print_until(const char *s, char c, t_flags *flags)
{
	while (s[flags->i] && s[flags->i] != c)
	{
		ft_putchar(s[flags->i]);
		flags->i++;
		flags->output++;
	}
}

static void	_discover_flags(const char *s, t_flags *flags)
{
	flags->i++;
	if (s[flags->i] >= '0' && s[flags->i] <= '9')
	{
		while (s[flags->i] >= '0' && s[flags->i] <= '9')
		{
			flags->width = (flags->width * 10) + (s[flags->i] - 48);
			flags->i++;
		}
	}
	if (s[flags->i] == '.')
	{
		flags->i++;
		flags->dot = 1;
		while (s[flags->i] >= '0' && s[flags->i] <= '9')
		{
			flags->precision = (flags->precision * 10) + (s[flags->i] - 48);
			flags->i++;
		}
	}
}

static void	ft_print_x_char(int len, char c, t_flags **flags)
{
	int	i;

	i = 0;
	while (i < len)
	{
		ft_putchar(c);
		(**flags).output++;
		i++;
	}
}

static void	ft_print_s(t_flags *flags)
{
	char	*s;

	flags->i++;
	s = va_arg(flags->arg, char *);
	if (!s)
		s = "(null)";
	flags->len = ft_strlen(s);
	if (flags->dot && flags->precision < flags->len)
		flags->len = flags->precision;
	ft_print_x_char(flags->width - flags->len, ' ', &flags);
	ft_putstr_len(s, flags->len);
	flags->output += flags->len;
}

static void	ft_print_d(t_flags *flags)
{
	long	nbr;

	flags->i++;
	nbr = va_arg(flags->arg, int);
	if (nbr < 0)
	{
		flags->negative = 1;
		nbr *= -1;
	}
	flags->len = ft_longlen_base(nbr, 10);
	if (nbr == 0 && flags->dot)
		flags->len = 0;
	if (flags->dot && flags->precision > flags->len)
		flags->zero_count = flags->precision - flags->len;
	if (flags->negative)
		flags->len++;
	ft_print_x_char(flags->width - (flags->zero_count + flags->len), ' ', &flags);
	if (flags->negative)
		ft_putchar('-');
	ft_print_x_char(flags->zero_count, '0', &flags);
	if (flags->dot && nbr == 0)
		return ;
	ft_putnbr_base(nbr, 10, "0123456789");
	flags->output += flags->len;
}

static void	ft_print_x(t_flags *flags)
{
	unsigned int	nbr;

	flags->i++;
	nbr = va_arg(flags->arg, unsigned int);
	flags->len = ft_longlen_base(nbr, 16);
	if (nbr == 0 && flags->dot)
		flags->len = 0;
	if (flags->dot && flags->precision > flags->len)
		flags->zero_count = flags->precision - flags->len;
	ft_print_x_char(flags->width - (flags->zero_count + flags->len), ' ', &flags);
	ft_print_x_char(flags->zero_count, '0', &flags);
	if (flags->dot && nbr == 0)
		return ;
	ft_putnbr_base(nbr, 16, "0123456789abcdef");
	flags->output += flags->len;
}

int			ft_printf(const char *fmt, ...)
{
	t_flags	flags;

	ft_init_flags(&flags);
	va_start(flags.arg, fmt);
	while (fmt[flags.i])
	{
		ft_clear_flags(&flags);
		ft_print_until(fmt, '%', &flags);
		if (fmt[flags.i])
		{
			_discover_flags(fmt, &flags);
			if (fmt[flags.i] == 's')
				ft_print_s(&flags);
			else if (fmt[flags.i] == 'd')
				ft_print_d(&flags);
			else if (fmt[flags.i] == 'x')
				ft_print_x(&flags);
		}
	}
	return (flags.output);
}