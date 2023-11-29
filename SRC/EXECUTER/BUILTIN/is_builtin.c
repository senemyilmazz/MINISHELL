#include "../../../INCLUDE/minishell.h"

int	is_builtin(char *str)
{
	if (!str)
		return (1);
	else if (!ownstrcmp(str, "echo") || !ownstrcmp(str, "ECHO"))
		return (ECHO);
	else if (!ownstrcmp(str, "cd"))
		return (CD);
	else if (!ownstrcmp(str, "pwd") || !ownstrcmp(str, "PWD"))
		return (PWD);
	else if (!ownstrcmp(str, "export"))
		return (EXPORT);
	else if (!ownstrcmp(str, "unset"))
		return (UNSET);
	else if (!ownstrcmp(str, "env") || !ownstrcmp(str, "ENV"))
		return (ENV);
	else if (!ownstrcmp(str, "exit"))
		return (EXIT);
	else
		return (0);
}
