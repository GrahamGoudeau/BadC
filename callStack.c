#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "user.h"

// create a user with "STANDARD" permissions for both read and write
User_T createUser(int userAge, char *userName)
{
    // declare a UserPermissions struct
    struct UserPermissions userPermissions;

    // define its initial values
    userPermissions.readPermission = STANDARD;
    userPermissions.writePermission = STANDARD;

    // use it to create a new user - why is this line (and the above three lines) wrong?
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
    fprintf(stdout, "\nUselessly computed y: %d\n", y);
    fprintf(stdout, "This is just to populate a stack frame\n\n");
    return y;
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    User_T user = createUser(21, "test user name");
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
    User_free(&user);
    return 0;
}
