/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobourai <yobourai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 21:29:35 by yobourai          #+#    #+#             */
/*   Updated: 2024/09/04 22:52:25 by yobourai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int len;

int	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_atoi(char *str)
{
	int	i;
	int	res;
	int	sign;

	i = 0;
	res = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 45)
	{
		sign = sign * (-1);
		i++;
	}
	else if (str[i] == 43)
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		res = res * 10 + str[i] - 48;
		i++;
	}
	return (res * sign);
}

void	ft_putstr(char *str)
{
	unsigned int	i;
	unsigned int	l;

	if (!str)
		return ;
	l = ft_strlen(str);
	i = 0;
	while (i < l)
	{
		write(1, &str[i], sizeof(str[i]));
		i++;
	}
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int n)
{
	if (n < 0)
	{
		write(1, "-", 1);
		n *= -1;
	}
	if (n > 9)
		ft_putnbr(n / 10);
	ft_putchar((n % 10) + '0');
}

char	*ft_bin(int a)
{
	static char	bin[9];
	int			i;
	char		flag;

	flag = (char)a;
	i = 7;
	while (i >= 0)
	{
		bin[i] = (a % 2) + '0';
		a = a / 2;
		i--;
	}
	i++;
	bin[8] = '\0';
	while (i > 0)
	{
		bin[i] = '0';
		i++;
	}
	return (bin);
}

void	ft_send_signal(char *pid, char *s)
{
	int	i;

	i = 0;
	while (i <= 7)
	{
		if (s[i] == '0')
			kill(ft_atoi(pid), SIGUSR1);
		else if (s[i] == '1')
			kill(ft_atoi(pid), SIGUSR2);
		usleep(500);
		i++;
	}
}
void ft_hand(int sig)
{
	if (sig == SIGUSR1)
		exit(1);
}
int	main(int argc, char *argv[])
{
	int		i;

	signal(SIGUSR1, ft_hand);
	if (argc != 3)
		exit(1);
	i = 0;
	while (argv[2][i] != '\0')
	{
		ft_send_signal(argv[1], ft_bin(argv[2][i]));
		i++;
	}
	ft_putstr("message has been saved successfuly\n");
	return (0);
}
