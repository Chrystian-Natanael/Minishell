#include "minishell.h"

int	ft_isspace(const char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}