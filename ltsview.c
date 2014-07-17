#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUF_MAX 1024
#define KEYS_MAX 100

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

int in_array(char *s, char **strings)
{
    int j;
    for (j = 0; strings[j] != NULL; j++) {
	if (strcmp(s, strings[j]) == 0) {
	    return 1;  // found
	}
    }

    return 0; // not found
}


int main(int argc, char **argv)
{
    if (argc >= 2 && strcmp(argv[1],"--help") == 0) {
	usage();
	return(1);
    }


    char *keys[KEYS_MAX];
    memset(keys, 0, sizeof(keys));
    int i;

    if (argc >= 2 && strcmp(argv[1],"-k") == 0) {
	for (i = 2; i < argc ;i++) {
	    keys[i-2] = argv[i];
	    printf("k:%s\n", argv[i]);
	}
    }


    char buf[BUF_MAX];
    struct item items[KEYS_MAX];
    char *tab;
    char *tmp;

    while (fgets(buf, BUF_MAX, stdin) != NULL) {
	printf("=========\n");
	tmp = buf;
	i = 0;
	memset(items,0, sizeof(items)); // is this right?
	while ((tab = strchr(tmp, '\t')) != NULL ) {
	    *tab = '\0';
	    parse_item(&items[i++], tmp);
	    tmp = tab + 1;
	}

	for (i = 0;items[i].key != NULL;i++) {
	    if (keys[0] == NULL) {
		printf("%d:%s: %s\n", i, items[i].key, items[i].value);
	    } else {
		if (in_array(items[i].key, keys)) {
		    printf("%d:%s: %s\n", i, items[i].key, items[i].value);
		}
	    }
	}
    }

    return 0;
}
