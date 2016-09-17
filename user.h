#ifndef USER_H
#define USER_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define T User_T
typedef struct T *T;

enum Permission {
    NONE,
    STANDARD,
    ADMIN
};

typedef struct UserPermissions {
    enum Permission readPermission;
    enum Permission writePermission;
} *UserPermissions;


T User_new(int age, char *name, UserPermissions permissions);
bool User_hasReadPermissionLevel(T user, enum Permission permissionLevel);
bool User_hasWritePermissionLevel(T user, enum Permission permissionLevel);
char *User_getName(T user);
char **User_getNameWritable(T user);
time_t User_getAccountAge(T user);

void User_free(T *user);

#undef T
#endif
