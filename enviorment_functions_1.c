#include "shell.h"

/**
 * printingEnviormentList - A function to print the variables in the enviroment
 * @myInfo: A pointer to the enviorment linked list
 * 
 * Return: Always 0 (Success)
*/

int printingEnviormentList(myInfoObject *myInfo)
{
        int theReturedValue = print_list((*myInfo).environment);
        return (0);
}

/**
 * gettingEnviormentVariable - A function to get a pointer to the enviroment varible
 * that is stored in our linked list
 * @myInfo: A pointer to myInfo variable
 * @myRVar: A pointer to a string that we want to find
 * and this string represnts the enviorment variable that we want
 * to find
 * 
 * Return: NULL or a pointer to node that cointains the required varible
*/

char *gettingEnviormentVariable(myInfoObject *myInfo, const char *myRVar)
{
        myList *myTempHead = (*myInfo).environment;
        char *myCP;

        while (myTempHead != NULL)
        {
                myCP = startsWith((*myTempHead).myString, myRVar);
                if (myCP != NULL && *myCP != NULL)
                        return (myCP);
                myTempHead = (*myTempHead).next;
        }
        return (NULL);
}

/**
 * preparingForSettingEnv - A function to prepare the setting enviorment
 * function to do its work
 * @myInfo: A pointer to info variable
 * 
 * Return: 0 if success and 1 if failure
*/

int preparnigForSettingEnv(myInfoObject *myInfo)
{
        if ((*myInfo).argument_count != 3)
        {
                _puts_fd("Not correct number of arguments\n", STDERR_FILENO);
                return (1);
        }
        if (setEnvVar(myInfo, (*myInfo).arguments[1], (*myInfo).arguments[2]) != 0)
                return (1);
        return (0);
}