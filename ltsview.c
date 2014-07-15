#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

void parse_item(struct item *item, char *key_value)
{
    char *colon;
    colon = strchr(key_value, ':');
    if (colon == NULL) {
	perror("invalid format");
	exit(1);
    }
    *colon = '\0';
    item->key = key_value;
    item->value = colon + 1;
}

int main(int argc, char **argv)
{
    if (argc >= 2 && strcmp(argv[1],"--help") == 0) {
	usage();
	return(1);
    }

    char buf[BUF_MAX];
    struct item *items[100];
    char *tab;
    char *key_value;
    int i;
    struct item item;

    while (fgets(buf, BUF_MAX, stdin) != NULL) {
	printf("=========\n");
	key_value = buf;
	i = 0;
	while ((tab = strchr(key_value, '\t')) != NULL ) {
	    *tab = '\0';
	    //items[i++] = key_value;

	    //item.concate_string = key_value;
	    parse_item(&item, key_value);
	    items[i++] = &item;

	    printf("%s: %s\n", item.key, item.value);

	    key_value = tab + 1;
	}
    }

    return 0;
}
