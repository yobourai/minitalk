/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobourai <yobourai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 21:30:05 by yobourai          #+#    #+#             */
/*   Updated: 2024/09/04 22:44:40 by yobourai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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
int	ft_power(unsigned int k, unsigned int n)
{
	if (n == 0)
		return (1);
	if (k == 0)
		return (0);
	int result = 1; // 5 3
					// 3
	while (n > 0) // 1
	{
		if (n % 2 == 1)  // true
			result *= k; // result == 5 == > 25
		k *= k;          // 25
		n /= 2;          // 1
	}
	return (result);
}

int	ascii(char *str)
{
	int	n;
	int	i;

	n = 0;
	i = 0;
	while (i < 8)
	{
		n += (str[i] - '0') * ft_power(2, 7 - i);
		i++;
	}
	return (n);
}
char	g_str[9];
void	ft_handler(int sig, siginfo_t *info, void *context)
{
	static int	i;
	static int	k;
	int			n;
	int			j;

	(void)context;
	j = info->si_pid;
	if (k == 0 || j != k)
	{
		if (k)
			kill(k , SIGUSR1);
		k = j;
		i = 0;
	}
	if (sig == SIGUSR1)
		g_str[i] = '0';
	else if (sig == SIGUSR2)
		g_str[i] = '1';
	i++;
	if (i == 8)
	{
		i = 0;
		g_str[8] = '\0';
		n = ascii(g_str);
		ft_putchar(n);
	}
}

int	main(void)
{
	int					pid;
	struct sigaction	msg;

	pid = getpid();
	ft_putstr("PID:");
	ft_putnbr(pid);
	write(1, "\n", 1);
	msg.sa_sigaction = ft_handler;
	msg.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &msg, NULL);
	sigaction(SIGUSR2, &msg, NULL);
	while (1)
		;
	pause();
	return (0);
}
