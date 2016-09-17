#include <string.h>
#include "user.h"

struct User_T {
    int age;
    char *name;
    UserPermissions userPermissions;
    time_t created;
};

typedef struct User_T *User_T;

User_T User_new(int age, char *name, UserPermissions permissions)
{
    User_T newUser = malloc(sizeof(struct User_T));
    size_t len = strlen(name);
    char *immutableName = malloc(sizeof(char) * len + 1);
    strcpy(immutableName, name);
    immutableName[len - 1] = '\0';

    UserPermissions immutablePermissions = malloc(sizeof(struct UserPermissions));
    immutablePermissions->readPermission = permissions->readPermission;
    immutablePermissions->writePermission = permissions->writePermission;

    newUser->name = immutableName;
    newUser->age = age;
    newUser->userPermissions = immutablePermissions;
    return newUser;
}
