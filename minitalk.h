#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>

int		ft_strlen(char *str);
int		ft_atoi(char *str);
void	ft_putstr(char *s);
void	ft_putnbr(int n);
char	*ft_bin(int a);
void	ft_send_signal(char *pid, char *s);
void	ft_handler(int sig, siginfo_t *info, void *context);
int		ft_power(unsigned int a, unsigned int b);
int		ascii(char *str);

#endif