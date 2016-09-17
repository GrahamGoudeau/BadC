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

void freeUser(User_T user)
{
    User_free(&user);
    user = NULL;
}

void checkToFreeUserLoop(User_T user)
{
    while (user != NULL)
    {
        fprintf(stderr, "User struct pointer is not null... about to ask to free the memory\n");
        char *response = prompt("Ready to free user? [y\\n] ");
        if (strcmp(response, "y\n") == 0)
        {
            freeUser(user);
        }
    }
}

int main(void)
{
    char *userName = prompt("User name: ");

    UserPermissions permissions = malloc(sizeof(struct UserPermissions));
    User_T newUser = User_new(20, userName, permissions);
    checkToFreeUserLoop(newUser);

    User_free(&newUser);
    return 0;
}
