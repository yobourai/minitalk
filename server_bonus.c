/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobourai <yobourai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 21:30:05 by yobourai          #+#    #+#             */
/*   Updated: 2024/09/05 21:59:52 by yobourai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

int	ft_power(unsigned int k, unsigned int n)
{
	int	result;

	if (n == 0)
		return (1);
	if (k == 0)
		return (0);
	result = 1;
	while (n > 0)
	{
		if (n % 2 == 1)
			result *= k;
		k *= k;
		n /= 2;
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

void	ft_hand_helper(int sig, int *i, int *n)
{
	if (sig == SIGUSR1)
		g_str[*i] = '0';
	else if (sig == SIGUSR2)
		g_str[*i] = '1';
	(*i)++;
	if (*i == 8)
	{
		*i = 0;
		g_str[8] = '\0';
		*n = ascii(g_str);
		ft_putchar(*n);
	}
}

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
			kill(k, SIGUSR1);
		k = j;
		i = 0;
	}
	ft_hand_helper(sig, &i, &n);
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
