#include <stdio.h>
#include <string.h>

#define BUF_MAX 1024

struct item {
    char *key;
    char *value;
};

void usage() {
    fprintf(stderr, "Usage: ltsview [OPTIONS]\n");
    fprintf(stderr, "viewer of ltsv log\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "-k         select keys\n");
}

int main(int argc, char **argv)
{
    if (argc >= 2 && strcmp(argv[1],"--help") == 0) {
	usage();
	return(1);
    }

    char buf[BUF_MAX];
    char *items[100];
    char *p;
    char *key_value;
    char *key;
    char *value;
    int i;
    char *colon;
    struct item item;

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
	    item.key = key_value;
	    item.value = colon + 1;

	    printf("%s: %s\n", item.key, item.value);

	    key_value = p + 1;
	}
    }

    return 0;
}
