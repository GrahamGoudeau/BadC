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

    char *userName = NULL;
    if (isDemonstration)
    {
        userName = name;
    }
    else
    {
        size_t len = strlen(name);
        char *immutableName = malloc(sizeof(char) * len + 1);
        strcpy(immutableName, name);
        immutableName[len - 1] = '\0';
        userName = immutableName;
    }

    UserPermissions userPermissions = NULL;
    if (isDemonstration)
    {
        userPermissions = permissions;
    }
    else
    {
        userPermissions = malloc(sizeof(struct UserPermissions));
        userPermissions->readPermission = permissions->readPermission;
        userPermissions->writePermission = permissions->writePermission;
    }

    newUser->name = userName;
    newUser->age = age;
    newUser->userPermissions = userPermissions;

    // get the current system time
    newUser->created = time(0);
    return newUser;
}

void User_free(User_T *user)
{
    if (isDemonstration)
    {
        free((*user)->name);
    }
    free((*user)->userPermissions);
    free(*user);
}

char *User_getName(User_T user)
{
    /* while we could modify the user's name with this function, e.g.
     *
     * char *name = User_getName(user);
     * name[0] = '!';
     *
     * This does NOT let us do more than that. For instance we cannot
     * resize the name
     */
    return user->name;
}

char **User_getNameWritable(User_T user)
{
    /* this allows us to modify the user's name even MORE -
     * for example, we could make the name longer or shorter.
     * 
     * Using an ampersand here means that we give the caller the
     * REFERENCE to the field INSIDE the User_T struct
     */
    return &(user->name);
}

time_t User_getAccountAge(User_T user)
{
    return user->created;
}

bool User_hasReadPermissionLevel(User_T user, enum Permission level)
{
    return user->userPermissions->readPermission == level;
}

bool User_hasWritePermissionLevel(User_T user, enum Permission level)
{
    return user->userPermissions->writePermission == level;
}

User_T User_newDefault()
{
    return User_new(-1, NULL, NULL);
}
