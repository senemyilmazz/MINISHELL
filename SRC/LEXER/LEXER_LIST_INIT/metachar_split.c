
#include "../../../INCLUDE/minishell.h"

int chrchr_metachar(char c)
{
    if (c == PIPE)
        return (1);
    else if (c == SIR)
        return (2);
    else if (c == SOR)
        return (3);
    else
        return (0);
}

int strchr_metachar(char *content)
{
    int i;

    i = -1;
    while (content[++i])
    {
        if (chrchr_metachar(content[i]))
            return (1);
    }
    return (0);
}

void    metachar_split(char *content)
{
    int end;
    int start;
    char *str;

    end = 0;
    while (content[end])
    {
        start = end;
        if (chrchr_metachar(content[start]))
            while (content[end] == content[start])
                end++;
        else
            while (content[end] && !chrchr_metachar(content[end]))
                end++;
        str = ft_substr(content, start, end - start);
        lexer_add_node(str, chrchr_metachar(*str));
        free(str);
    }
}

void create_nodes(t_list *lex_slist)
{
    t_list  *temp;

    temp = lex_slist;
    while(temp)
    {
        if (strchr_quotes(temp->content) || !strchr_metachar(temp->content))
            lexer_add_node(temp->content, 0);
        else
            metachar_split(temp->content);
        lex_slist = temp;
        temp = temp->next;
        free(lex_slist);
    }
}