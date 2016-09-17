#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "user.h"

UserPermissions makePermissions(enum Permission *read, enum Permission *write)
{
    UserPermissions permissions = malloc(sizeof(struct UserPermissions));
    permissions->readPermission = *read;
    permissions->writePermission = *write;

    return permissions;
}

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

int main(void)
{
    enum Permission *readPermissionPointer;
    enum Permission *writePermissionPointer;
    *readPermissionPointer = ADMIN;
    *writePermissionPointer = STANDARD;

    UserPermissions permissions = makePermissions(readPermissionPointer, writePermissionPointer);

    char *userName = prompt("Enter a name: ");

    User_T newUser = User_new(20, userName, permissions);

    User_free(&newUser);
    return 0;
}
