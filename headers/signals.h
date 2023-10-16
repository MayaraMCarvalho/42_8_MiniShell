#ifndef SIGNALS_H
# define SIGNALS_H

//SIG EXEC-
void	sign_interrupt(int signum);
void	sign_interrupt_delimiter(int signum);
void	ctrl_d(int latest_exit_code);

//SIG INIT
void	sign_child(void);
void	sign_delimiter(void);
void	sign_init(void);
void	sign_ignore(void);

#endif