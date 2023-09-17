#include "shell.h"


/**
 * findingMyBuiltinFunc - A function to gives us a pointer
 * to the required builtin functions that we have implmented
 * @myInfo: A pointer to myInfoObject that contains everything
 * about the shell currently
 *
 * Return: -1 on failure or other exiting condition
 * or success
*/

int findingMyBuiltinFunc(myInfoObject *myInfo)
{
    int i, myBuiltinRetValue = -1;
    
    myBuiltin myTableofBuilding[] = {
        {"exit", _exit_shell},
        {"env", printingEnviormentList},
        {"help", _help_},
        {"history", print_history},
        {"setenv", preparnigForSettingEnv},
        {"unsetenv", preparingForUnsettingEnv},
        {"cd", _cd_},
        {"alias", man_alias},
        {NULL, NULL}
    };

    for (i = 0; myTableofBuilding[i].nameofFunction != NULL; i++)
    {
        if (_strcmp(myTableofBuilding[i].nameofFunction, (*myInfo).arguments[0]) == 0)
        {
            (*myInfo).line_count = (*myInfo).line_count + 1;
            myBuiltinRetValue = myTableofBuilding[i].myCommandFun(myInfo);
            break;
        }
    }
    return (myBuiltinRetValue);
}

/**
 * forkingMyCmd - A function to fork the process when
 * we need to execute a commmand
 * @myInfo: A pointer to myInfoObject that contains everything
 * about the shell currently
 * 
 * Return: Nothing (void)
*/

void forkingMyCmd(myInfoObject *myInfo)
{
    pid_t myChildPid;
    int myReturnedStatus;
    myChildPid = fork();
    if (myChildPid == -1)
    {
        perror("Error: couldn't fork\n");
        return;
    }
    if (myChildPid == 0)
    {
        myReturnedStatus = execve((*myInfo).path,
        (*myInfo).argument,gettingMyEnviron(myInfo));
        if (myReturnedStatus == -1)
        {
            freeMyInfo(myInfo);
            if (errno == EACCES)
                exit(126);
            exit(1);
        }
    }
    else
    {
        wait(&(*myInfo).status);
        if (WIFEXITED((*myInfo).status))
        {
            (*myInfo).status = WEXITSTATUS((*myInfo).status);
            if ((*myInfo).status == 126)
                printingErros(myInfo, "Permission denied\n");
        }
    }
}