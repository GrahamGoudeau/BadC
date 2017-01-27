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

void free_user(User_T user)
{
	User_free(&user);
	user = NULL;
}

void check_to_free_user_loop(User_T user)
{
	while (user != NULL) {
		fprintf(stderr, "User struct pointer is not null... about to "
				"ask to free the memory\n");
		char *response = prompt("Ready to free user? [y\\n] ");
		if (strcmp(response, "y\n") == 0) {
			free_user(user);
		}
	}
}

int main(void)
{
	char *user_name = prompt("User name: ");

	UserPermissions permissions = malloc(sizeof(struct UserPermissions));
	User_T new_user = User_new(20, user_name, permissions);
	check_to_free_user_loop(new_user);

	User_free(&new_user);
	return 0;
}
