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

void set_user_name(User_T user, char *name)
{
	char **user_existing_name = User_get_name_writable(user);
	*user_existing_name = name;
}

int main(void)
{
	while (true) {
		// includes newline
		User_T user = User_new_default();
		char *response = prompt("Create new user? ");
		free(response);

		if (strcmp(response, "n\n") == 0 ||
		    strcmp(response, "N\n") == 0) {
			break;
		}

		char *name = prompt("Set the user's name: ");
		set_user_name(user, name);
		fprintf(stdout, "User name: %s\n", User_get_name(user));
		User_free(&user);
	}
	return 0;
}
