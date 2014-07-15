#include <stdio.h>
#include <string.h>

#define BUF_MAX 1024

int main()
{
    char buf[BUF_MAX];
    char *items[100];
    char *p;
    char *key_value;
    char *key;
    char *value;
    int i;
    char *colon;
    while (fgets(buf, BUF_MAX, stdin) != NULL) {
	printf("=========\n");
	key_value = buf;
	i = 0;
	while ((p = strchr(key_value, '\t')) != NULL ) {
	    *p = '\0';
	    items[i++] = key_value;

	    colon = strchr(key_value, ':');
	    if (colon == NULL) {
		perror("invalid format");
		return 1;
	    }
	    *colon = '\0';
	    key = key_value;
	    value = colon + 1;

	    printf("%s: %s\n", key,value);

	    key_value = p + 1;
	}
    }

    return 0;
}
