#include "minishell.h"

void	print_tokens(t_token *token) // ! Apagar
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		ft_printf("type: %d, lexema: %s\n", tmp->type, tmp->lexema);
		tmp = tmp->next;
	}
}