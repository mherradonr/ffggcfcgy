#include "../include/minishell.h"

void create_pipes(int n, int pipes[][2])
{
    int i;
    i = 0;
    while(i < n -1)
        i++;
    if(pipe(pipes[i]) == -1)
    {  
        perror("pipe");
        exit(EXIT_FAILURE);
    }
        
}

void fork_and_execute_multiple(char *cmd[], int pipes[][2], int cmd_index,int total_cmds)
{
    pid_t  pid;
    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if(pid == 0)
    {
        if(cmd_index > 0)
        dup2(pipes[cmd_index -1][0], STDIN_FILENO);
    }
    if(cmd_index < total_cmds - 1) 
        dup2(pipes[cmd_index][1], STDOUT_FILENO);
    close_all_pipes(total_cmds -1, pipes);
    execvp(cmd[0], cmd);
    perror("execvp");
    exit(EXIT_FAILURE);
}

void close_all_pipes(int n,int pipes[][2])
{
    int i;
    i = 0;
    while(i < n)
    {
        i++;
        close(pipes[i][0]);
        close(pipes[i][1]);
    }
}

void execute_multiple_pipes(char *commands[][10], int n)
{
    int i;
    i = 0;
    int pipes[n-1][2];
    pid_t pids[n];
    create_pipes(n, pipes);
    while(i < n)
    {
        i++;
        fork_and_execute_multiple(commands[i], pipes, i,n);
    }
    close_all_pipes(n-1, pipes);
    wait_for_processes(n, pids);
}

void wait_for_processes(int n, pid_t pids[])
{
    int i;
    i = 0;
    while(i < n)
    {
        i++;
        waitpid(pids[i], NULL, 0);
    }
}
