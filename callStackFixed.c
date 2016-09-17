#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "user.h"

// create a user with "STANDARD" permissions for both read and write
User_T createUser(int userAge, char *userName)
{
    // why can we say UserPermissions instead of struct UserPermissions * ?
    UserPermissions userPermissions = malloc(sizeof(struct UserPermissions));

    // define its initial values
    userPermissions->readPermission = STANDARD;
    userPermissions->writePermission = STANDARD;

    User_T user = User_new(userAge, userName, userPermissions);

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
    fprintf(stdout, "\nUselessly computed y: %d\n", y);
    fprintf(stdout, "This is just to populate a stack frame\n\n");
    return y;
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    char *stackName = "test user name";

    // why do we need + 1 here?
    char *userName = malloc(sizeof(char) * strlen(stackName) + 1);
    strcpy(userName, stackName);
    User_T user = createUser(21, userName);

    // call some other function just to make sure that we have created and destroyed another stack frame
    int t = otherFunction(100);
    fprintf(stdout, "Main computed t (can ignore this): %d\n", t);


    if (User_hasReadPermissionLevel(user, STANDARD))
    {
        fprintf(stderr, "User has STANDARD read permissions in main\n");
    }
    else
    {
        fprintf(stderr, "User does not have STANDARD read permissions in main\n");
    }

    // why is it fine to pass &user here, whereas it was wrong to use an ampersand in ./callStack?
    User_free(&user);
    return 0;
}

