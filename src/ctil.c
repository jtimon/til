#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"

static char *read_file(const char *path) {
    FILE *f = fopen(path, "rb");
    if (!f) {
        fprintf(stderr, "error: could not open '%s'\n", path);
        return NULL;
    }
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *buf = malloc(size + 1);
    fread(buf, 1, size, f);
    buf[size] = '\0';
    fclose(f);
    return buf;
}

static void print_token(Token *t) {
    printf("  %3d:%2d  %-12s  '%.*s'\n", t->line, t->col, tok_name(t->type), t->len, t->start);
}

static void usage(void) {
    printf("Usage: ctil <command> <path>\n\n");
    printf("Commands:\n");
    printf("  interpret  Read and interpret a .til file\n");
    printf("  build      Compile a .til file to a binary\n");
    printf("  run        Compile and run a .til file\n");
    printf("  help       Print this message\n");
}

int main(int argc, char **argv) {
    if (argc < 2) {
        usage();
        return 1;
    }

    const char *command = argv[1];
    const char *path = NULL;

    if (argc == 2) {
        // Single arg: if it's a known command without a path, handle it
        if (strcmp(command, "help") == 0 || strcmp(command, "--help") == 0) {
            usage();
            return 0;
        }
        // Otherwise treat as a path (like til does)
        path = command;
        command = "interpret";
    } else {
        path = argv[2];
    }

    if (strcmp(command, "help") == 0 || strcmp(command, "--help") == 0) {
        usage();
        return 0;
    }

    char *source = read_file(path);
    if (!source) return 1;

    int count;
    Token *tokens = tokenize(source, path, &count);

    // For now, just print tokens
    printf("Tokens (%d):\n", count);
    for (int i = 0; i < count; i++) {
        print_token(&tokens[i]);
    }

    free(tokens);
    free(source);
    return 0;
}
