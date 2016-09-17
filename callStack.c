#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "user.h"

// create a user with "STANDARD" permissions for both read and write
User_T createUser(int userAge, char *userName)
{
    struct UserPermissions userPermissions;
    userPermissions.readPermission = STANDARD;
    userPermissions.writePermission = STANDARD;
    User_T user = User_new(userAge, userName, &userPermissions);
    if (User_hasReadPermissionLevel(user, STANDARD))
    {
        fprintf(stderr, "User has STANDARD read permissions in createUser\n");
    }
    else
    {
        fprintf(stderr, "User does not have STANDARD read permissions in createUser\n");
    }
    return user;
}

int otherFunction(int x)
{
    int y = x / 2 + x;
    fprintf(stdout, "Uselessly computed y: %d\n", y);
    fprintf(stdout, "This is just to populate a stack frame\n");
    return y;
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    char *stackName = "test user name";
    char *name = malloc(sizeof(char) * (strlen(stackName)) + 1);
    strcpy(name, stackName);
    User_T user = createUser(21, name);
    int t = otherFunction(100);
    if (User_hasReadPermissionLevel(user, STANDARD))
    {
        fprintf(stderr, "User has STANDARD read permissions in main\n");
    }
    else
    {
        fprintf(stderr, "User does not have STANDARD read permissions in main\n");
    }
    User_free(&user);
    return 0;
}
