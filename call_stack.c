/*
 * Author: Graham Goudeau
 * Date Created: Jan 2017
 */
#include "user.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// create a user with "STANDARD" permissions for both read and write
User_T create_user(int user_age, char *user_name)
{
	// declare a UserPermissions struct
	struct UserPermissions user_permissions;

	// define its initial values
	user_permissions.read_permission = STANDARD;
	user_permissions.write_permission = STANDARD;

	User_T user = User_new(user_age, user_name, &user_permissions);

	if (User_has_read_permission_level(user, STANDARD)) {
		fprintf(stderr,
			"User has STANDARD read permissions in create_user\n");
	} else {
		fprintf(stderr, "User does not have STANDARD read permissions "
				"in create_user\n");
	}
	return user;
}

int other_function(int x)
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

	User_T user = create_user(21, "test user name");

	// call some other function just to make sure that we have created and
	// destroyed another stack frame
	int t = other_function(100);
	fprintf(stdout, "Main computed t (can ignore this): %d\n", t);

	if (User_has_read_permission_level(user, STANDARD)) {
		fprintf(stderr, "User has STANDARD read permissions in main\n");
	} else {
		// on MY computer at least, the user suddenly does NOT have
		// standard read permissions. Your results may vary
		fprintf(
		    stderr,
		    "User does not have STANDARD read permissions in main\n");
	}

	// why does this line produce at least two valgrind errors regarding
	// invalid frees?
	User_free(&user);
	return 0;
}
