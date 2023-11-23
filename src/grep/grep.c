#include "grep.h"
#define BUF_SIZE 16364

int main(int argc, char *argv[]) {
  Flagi flagi = {0};
  flagi.e = 0;
  flagi.i = 0;
  flagi.v = 0;
  flagi.c = 0;
  flagi.l = 0;
  flagi.n = 0;
  flagi.h = 0;
  flagi.s = 0;
  flagi.reg = 0;
  char patterns[BUF_SIZE] = {0};
  parser_flagi(argc, argv, &flagi, patterns);
  vivod(argc, argv, flagi, patterns);
}

void parser_flagi(int argc, char *argv[], Flagi *flagi, char *patterns) {
  int flagi_index = 0, a = 0, i = 0;

  while ((a = getopt_long(argc, argv, "e:ivclnhs", NULL, &flagi_index)) != -1) {
    switch (a) {
      case 'e':

        if (strlen(patterns) > 0) strcat(patterns, "|");
        strcat(patterns, optarg);
        flagi->reg |= REG_EXTENDED;
        flagi->e = 1;
        i++;
        break;
      case 'i':
        flagi->reg |= REG_ICASE;
        break;
      case 'v':
        flagi->v = 1;
        break;
      case 'c':
        flagi->c = 1;
        break;
      case 'l':
        flagi->l = 1;
        break;
      case 'n':
        flagi->n = 1;
        break;
      case 'h':
        flagi->h = 1;
        break;
      case 's':
        flagi->s = 1;
        break;
      default:
        fprintf(stderr, "usage: e:ivclnhs");
        exit(1);
        break;
    }
  }
  if (flagi->l || flagi->c) flagi->h = 0;
}
void vivod(int argc, char *argv[], Flagi flagi, char *patterns) {
  if (!flagi.e) {
    if (strlen(patterns) > 0) strcat(patterns, "|");
    strcat(patterns, argv[optind]);
    optind++;
  }
  int count_files = optind == argc - 1;
  regex_t sravnenie = {0};
  if (regcomp(&sravnenie, patterns, flagi.reg)) {
    if (!flagi.s) printf("failed");

  } else {
    while (optind < argc) {
      FILE *document = fopen(argv[optind], "r");
      optind++;
      if (document) {
        int count_str = 1;
        int count_match = 0;

        char *stroka = 0;
        size_t len_str = 0;
        regmatch_t sovpadenie = {0};
        while (getline(&stroka, &len_str, document) > 0) {
          int res = regexec(&sravnenie, stroka, 1, &sovpadenie, 0);
          if (flagi.v) res = !res;
          if (!res) {
            if (!flagi.c && !flagi.l) {
              if (!flagi.h && count_files == 0) printf("%s:", argv[optind - 1]);

              if (flagi.n) printf("%d:", count_str);
              printf("%s", stroka);
            }
            count_match++;
          }
          count_str++;
        }
        if (flagi.l) printf("%s\n", argv[optind - 1]);
        if (flagi.c) printf("%d\n", count_match);

        free(stroka);
        fclose(document);
      }
    }
    regfree(&sravnenie);
  }
}