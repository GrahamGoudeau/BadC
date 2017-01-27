/*
 * Author: Graham Goudeau
 * Date Created: Jan 2017
 */
#ifndef USER_H
#define USER_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// set up a preprocessor directive that replaces every instance of 'T' with
// 'User_T'
#define T User_T

// lots of things going on here-
// * declare a type called 'struct T' (which is expanded by the preprocessor
// directive into 'struct User_T')
// * make the identifier 'User_T' an alias for 'struct User_T *'
typedef struct T *T;

enum Permission { NONE, STANDARD, ADMIN };

// a User can have some permission to read and some permission to write, and we
// don't require those permissions to have the same level
typedef struct UserPermissions {

	// notice that, like for structs, we need an enum keyword here
	enum Permission read_permission;
	enum Permission write_permission;
} * UserPermissions;

// construct a new user with userAge = -1, userName = NULL, permissions = NULL
T User_new_default();

// construct a new user with the given age, name, and permission levels
T User_new(int user_age, char *user_name, UserPermissions permissions);

// check whether the user has certain permissions
bool User_has_read_permission_level(T user, enum Permission permission_level);
bool User_has_write_permission_level(T user, enum Permission permission_level);

// get the user's name, or get a fully writable version of the user's name
char *User_get_name(T user);
char **User_get_name_writable(T user);

// frees the overall User_T object along with the name and permissions
void User_free(T *user);

#undef T
#endif
