/*
 * Author: Graham Goudeau
 * Date Created: Jan 2017
 */
#include "user.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *prompt(char *message)
{
	fprintf(stdout, message);
	char *response = NULL;
	size_t len = 0;

	// getline allocates space for its input, so we must free it
	int signal = getline(&response, &len, stdin);

	if (signal == -1) {
		return NULL;
	}

	return response;
}

User_T create_admin_with_name(char *name)
{
	UserPermissions permissions = malloc(sizeof(struct UserPermissions));
	permissions->read_permission = ADMIN;
	permissions->write_permission = ADMIN;

	return User_new(20, name, permissions);
}

int main(void)
{
	// prompt() allocates enough space for the input
	// this space must be freed later
	char *user_name = prompt("User name: ");

	User_T admin = create_admin_with_name(user_name);

	// free the space we created from prompt()
	free(user_name);

	User_free(&admin);
	return 0;
}
