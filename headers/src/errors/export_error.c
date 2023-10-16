#include "../../headers/error.h"

static int	export_error(char *arg)
{
	ft_putstr_fd("export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	return (1);
}

int	export_error_check(char *arg)
{
	int	i;

	i = 1;
	if (!arg[0])
		return (export_error(arg));
	if (ft_isdigit(arg[0]) || (!ft_isalpha(arg[0]) && arg[0] != '_'))
		return (export_error(arg));
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (export_error(arg));
		i++;
	}
	return (0);
}
