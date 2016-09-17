#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "user.h"

int main(int argc, char **argv)
{
    UserPermissions userPermissions = malloc(sizeof(struct UserPermissions));
    userPermissions->readPermission = ADMIN;
    userPermissions->writePermission = NONE;
    char *name = calloc(5, sizeof(char));
    strcpy(name, "test");

    User_T user = User_new(3, name, userPermissions);
    char *gotName = User_getName(user);

    fprintf(stderr, "User name: %s\n", gotName);

    gotName[0] = '7';
    char *gotName2 = User_getName(user);

    fprintf(stderr, "user name now: %s\n", gotName2);

    char **writableName = User_getNameWritable(user);
    free(*writableName);
    *writableName = calloc(10, sizeof(char));
    strcpy(*writableName, "123456789");
    fprintf(stderr, "user name now: %s\n", User_getName(user));
    free(userPermissions);
    User_free(&user);
    return 0;
}
