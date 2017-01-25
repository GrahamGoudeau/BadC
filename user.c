#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "user.h"

static bool has_seeded_rand = false;
static const bool is_demonstration = true;
/* what happens when is_demonstration set to true:
 *
 * User_new will use the reference to UserPermissions that it is given rather than make a defensive copy
 * User_free will attempt to free the reference to the user's name
 */

struct User_T {
    int age;
    char *name;
    UserPermissions user_permissions;
    int user_id;
};

typedef struct User_T *User_T;

User_T User_new(int age, char *name, UserPermissions permissions)
{
    if (!has_seeded_rand)
    {
        srand(time(0));
        has_seeded_rand = true;
    }

    User_T new_user = malloc(sizeof(struct User_T));

    char *user_name = NULL;
    if (is_demonstration)
    {
        user_name = name;
    }
    else
    {
        size_t len = strlen(name);
        char *immutable_name = malloc(sizeof(char) * len + 1);
        strcpy(immutable_name, name);
        immutable_name[len - 1] = '\0';
        user_name = immutable_name;
    }

    UserPermissions user_permissions = NULL;
    if (is_demonstration)
    {
        user_permissions = permissions;
    }
    else
    {
        user_permissions = malloc(sizeof(struct UserPermissions));
        user_permissions->read_permission = permissions->read_permission;
        user_permissions->write_permission = permissions->write_permission;
    }

    new_user->name = user_name;
    new_user->age = age;
    new_user->user_permissions = user_permissions;

    // give them a random ID
    new_user->user_id = rand();
    return new_user;
}

void User_free(User_T *user)
{
    if (is_demonstration)
    {
        free((*user)->name);
    }
    free((*user)->user_permissions);
    free(*user);
    *user = NULL;
}

char *User_get_name(User_T user)
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

char **User_get_name_writable(User_T user)
{
    /* this allows us to modify the user's name even MORE -
     * for example, we could make the name longer or shorter.
     * 
     * Using an ampersand here means that we give the caller the
     * REFERENCE to the field INSIDE the User_T struct
     */
    return &(user->name);
}

bool User_has_read_permission_level(User_T user, enum Permission level)
{
    return user->user_permissions->read_permission == level;
}

bool User_has_write_permission_level(User_T user, enum Permission level)
{
    return user->user_permissions->write_permission == level;
}

User_T User_new_default()
{
    return User_new(-1, NULL, NULL);
}
