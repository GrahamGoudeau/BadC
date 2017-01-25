#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "user.h"

UserPermissions make_permissions(enum Permission *read, enum Permission *write)
{
    UserPermissions permissions = malloc(sizeof(struct UserPermissions));
    permissions->read_permission = *read;
    permissions->write_permission = *write;

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
    enum Permission *read_permission_pointer;
    enum Permission *write_permission_pointer;
    *read_permission_pointer = ADMIN;
    *write_permission_pointer = STANDARD;

    UserPermissions permissions = make_permissions(read_permission_pointer, write_permission_pointer);

    char *user_name = prompt("Enter a name: ");

    User_T new_user = User_new(20, user_name, permissions);

    User_free(&new_user);
    return 0;
}
