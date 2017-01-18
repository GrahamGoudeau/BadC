#ifndef USER_H
#define USER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// set up a preprocessor directive that replaces every instance of 'T' with 'User_T'
#define T User_T

// lots of things going on here-
// * declare a type called 'struct T' (which is expanded by the preprocessor directive into 'struct User_T')
// * make the identifier 'User_T' an alias for 'struct User_T *'
typedef struct T *T;

enum Permission {
    NONE,
    STANDARD,
    ADMIN
};

// a User can have some permission to read and some permission to write, and we don't require those permissions to have the same level
typedef struct UserPermissions {

    // notice that, like for structs, we need an enum keyword here
    enum Permission readPermission;
    enum Permission writePermission;
} *UserPermissions;


// construct a new user with userAge = -1, userName = NULL, permissions = NULL
T User_newDefault();

// construct a new user with the given age, name, and permission levels
T User_new(int userAge, char *userName, UserPermissions permissions);

// check whether the user has certain permissions
bool User_hasReadPermissionLevel(T user, enum Permission permissionLevel);
bool User_hasWritePermissionLevel(T user, enum Permission permissionLevel);

// get the user's name, or get a fully writable version of the user's name
char *User_getName(T user);

// frees the overall User_T object along with the name and permissions
void User_free(T *user);

#undef T
#endif
