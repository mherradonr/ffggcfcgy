#include "../include/minishell.h"

int count_pipes(char *input)
{
    int count;
    int i;
    i = 0;
    count = 0;
    while(input[i] != '\0')
    {
        if(input[i] == '|')
            count++;
        i++;
    }
    return(count +1);
}

char *trim_whitespace(char *str)
{
    char *end;
    while(*str == ' ')
        str++;
    end = str + ft_strlen(str) - 1;
    while(end > str && *end == ' ')
    {
        end--;
        *(end + 1)  = '\0';
    }
    return str; 
}

int count_words(char *command)
{
    int i;
    int in_word;
    int count;
    
    in_word = 0;
    count = 0;
    i = 0;
    
    while(command[i] != '\0')
    {
        if(command[i] != ' ' && !in_word)
        {
            in_word = 1;
            count++;
        }
        else if(command[i] == ' ')
            in_word = 0;
        i++;
    }
    return(count);
}

t_word_info get_word_info(char *command, int index)
{
    t_word_info word_info;
    int i;

    word_info.start = index;
    i = index;
    while(command[i] != '\0' && command[i] != ' ')
        i++;
    word_info.length = i - word_info.start;
    return word_info;
}

char *allocate_and_copy_word(char *command, t_word_info word_info)
{
    char *word;
    int  j;

    word = malloc((word_info.length + 1) * sizeof(char));
    if(!word)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    j = 0;
    while(j < word_info.length)
    {
        word[j] = command[word_info.start + j];
        j++;
    }
    word[word_info.length] = '\0';
    return(word);
}

char **split_command(char *command)
{
    int num_words;
    char **tokens;
    int token_index;
    int start;
    int i;
    t_word_info word_info;

    num_words = count_words(command);
    tokens = malloc((num_words + 1) * sizeof(char*));
    if(!tokens)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    token_index = 0;
    i = 0;
    while(command[i] != '\0')
    {
        if(command[i] != ' ')
        {
            word_info = get_word_info(command, i);
            tokens[token_index] = allocate_and_copy_word(command, word_info);
            token_index++;
            i += word_info.length;
        }
        else 
            i++;
    }     
    tokens[token_index] = NULL;
    return(tokens);
}

void extract_command(char *start, char **commands, int *cmd_index)
{
    char *cleaned_command;
    cleaned_command = trim_whitespace(start);
    commands[*cmd_index] = split_command(cleaned_command);
    (*cmd_index)++;
}

char ***parse_input(char *input, int *num_commands)
{
    *num_commands = count_pipes(input);
    char ***commands = malloc(*num_commands * sizeof(char **));
    char *start;
    char *end;
    int cmd_index;
    
    start = input;
    end = input;
    cmd_index = 0;
    while(*end != '\0')
    {
        if(*end == '|')
        {
            *end = '\0';
            extract_command(start, commands, &cmd_index);
            start = end + 1;
        }
        end++;
    }
    extract_command(start, commands, &cmd_index);
    return(commands);
}

void free_commands(char ***commands, int num_commands)
{
    int i;
    int j;
    char **command;

    i = 0;
    while (i < num_commands)
    {
        command = commands[i];
        j = 0;
        while (command[j] != NULL)
        {
            free(command[j]);
            j++;
        }
        free(command);
        i++;
    }
    free(commands);
}

