#include "../../../INCLUDE/minishell.h"

int	parameters_count(char **str)
{
	int	count;

	count = 0;
	while (str && *(str++))
		count++;
	return (count);
}
