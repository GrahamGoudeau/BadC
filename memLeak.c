#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "user.h"

char *prompt(char *message)
{
    fprintf(stdout, message);
    char *response = NULL;
    size_t len = 0;

    // getline allocates space for its input, so we must free it
    int signal = getline(&response, &len, stdin);

    if (signal == -1)
    {
        return NULL;
    }

    return response;
}

void setUserName(User_T user, char *name)
{
    char **userExistingName = User_getNameWritable(user);
    *userExistingName = name;
}

int main(void)
{
    while (true)
    {
        // includes newline
        User_T user = User_newDefault();
        char *response = prompt("Create new user? ");
        free(response);

        if (strcmp(response, "n\n") == 0 || strcmp(response, "N\n") == 0)
        {
            break;
        }

        char *name = prompt("Set the user's name: ");
        setUserName(user, name);
        fprintf(stdout, "User name: %s\n", User_getName(user));
        User_free(&user);
    }
    return 0;
}
