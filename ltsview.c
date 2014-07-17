#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUF_MAX 10240
#define KEYS_MAX 100

struct item {
    char *key;
    char *value;
};

void usage();
void parse_item(struct item *item, char *key_value);
int in_array(char *s, char **strings);

int main(int argc, char **argv)
{
    if (argc >= 2 && (strcmp(argv[1],"--help") == 0 || strcmp(argv[1],"-h") == 0)) {
	usage();
	return(1);
    }


    char *keys[KEYS_MAX];
    memset(keys, 0, sizeof(keys));
    int i;
    char *concate_keys;

    /* parse -k options */
    if (argc >= 2 && strcmp(argv[1],"-k") == 0) {
	if (argc == 2) {
	    fprintf(stderr, "no argument for -k option\n");
	    exit(1);
	}

	concate_keys = argv[2];
	printf("concate_keys = %s\n", concate_keys);

	keys[0] = strtok(concate_keys, ",");
	if (keys[0] != NULL) {
	    i = 1;
	    while((keys[i] = strtok(NULL, ",")) != NULL) {
		i++;
	    }
	}
    }

    char buf[BUF_MAX];
    struct item items[KEYS_MAX];
    char *tab;
    char *tmp;

    while (fgets(buf, BUF_MAX, stdin) != NULL) {
	printf("=========\n");
	//printf("%s\n", buf); // debug

	if (buf[BUF_MAX -2] != '\0') {
	    fprintf(stderr, "buffer over run!\n");
	    return 1;
	}

	tmp = buf;
	i = 0;
	memset(items,0, sizeof(items)); // is this right?
	while ((tab = strchr(tmp, '\t')) != NULL ) {
	    *tab = '\0';
	    parse_item(&items[i++], tmp);
	    tmp = tab + 1;
	}

	for (i = 0;items[i].key != NULL;i++) {

	    if (keys[0] != NULL && ! in_array(items[i].key, keys)) {
		continue;
	    }

	    printf("%s: %s\n", items[i].key, items[i].value);
	}
    }

    return 0;
}

void usage() {
    printf("Usage: ltsview [OPTIONS]\n");
    printf("viewer of ltsv log\n");
    printf("\n");
    printf("-k <key,..>     select keys\n");
}

void parse_item(struct item *item, char *key_value)
{
    char *colon;
    colon = strchr(key_value, ':');
    if (colon == NULL) {
	fprintf(stderr, "invalid format:[%s]", key_value);
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

