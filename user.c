#include <string.h>
#include <stdbool.h>
#include "user.h"

static const bool isDemonstration = true;
/* what happens when isDemonstration set to true:
 *
 * User_new will use the reference to UserPermissiosn that it is given rather than make a defensive copy
 * User_free will attempt to free the reference to the user's name
 */

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
    //char *immutableName = malloc(sizeod(char) * len + 1);
    //strcpy(immutableName, name);
    //immutableName[len - 1] = '\0';

    UserPermissions userPermissions = NULL;
    if (isDemonstration)
    {
        newUser->userPermissions = permissions;
    }
    else
    {
        userPermissions = malloc(sizeof(struct UserPermissions));
        userPermissions->readPermission = permissions->readPermission;
        userPermissions->writePermission = permissions->writePermission;
    }

    newUser->name = name;
    newUser->age = age;
    newUser->userPermissions = userPermissions;
    newUser->created = time(0);
    return newUser;
}

void User_free(User_T *user)
{
    //free((*user)->name);
    free((*user)->userPermissions);
    free(*user);
}

char *User_getName(User_T user)
{
    return user->name;
}

char **User_getNameWritable(User_T user)
{
    return &(user->name);
}
