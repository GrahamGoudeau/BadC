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

User_T createAdminWithName(char *name)
{
    UserPermissions permissions = malloc(sizeof(struct UserPermissions));
    permissions->readPermission = ADMIN;
    permissions->writePermission = ADMIN;

    return User_new(20, name, permissions);
}


int main(void)
{
    // prompt() allocates enough space for the input
    // this space must be freed later
    char *userName = prompt("User name: ");

    User_T admin = createAdminWithName(userName);

    // free the space we created from prompt()
    free(userName);

    User_free(&admin);
    return 0;
}
