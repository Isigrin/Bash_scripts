#include "cat.h"
#define razmer_buff 16000

int main(int argc, char *argv[]) {
  Flagi flagi = {0};
  flagi.n = 0;
  flagi.e = 0;
  flagi.b = 0;
  flagi.s = 0;
  flagi.t = 0;
  flagi.v = 0;
  parser_flagi(argc, argv, &flagi);
  vivod(argc, argv, flagi);
  return 0;
}

void parser_flagi(int argc, char *argv[], Flagi *flagi) {
  int flagi_index = 0, c = 0;
  struct option long_flagi[] = {{"number-nonblank", 0, 0, 'b'},
                                {"number", 0, 0, 'n'},
                                {"squeeze-blank", 0, 0, 's'},
                                {0, 0, 0, 0}};

  while ((c = getopt_long(argc, argv, "benstvET", long_flagi, &flagi_index)) !=
         -1) {
    switch (c) {
      case 'b':
        flagi->b = 1;
        break;
      case 'e':
        flagi->e = 1;
        flagi->v = 1;
        break;
      case 'n':
        flagi->n = 1;
        break;
      case 's':
        flagi->s = 1;
        break;
      case 't':
        flagi->t = 1;
        flagi->v = 1;
        break;
      case 'v':
        flagi->v = 1;
        break;
      case 'E':
        flagi->e = 1;
        break;
      case 'T':
        flagi->t = 1;
        break;
      default:
        fprintf(stderr, "usage: benstvET");
        exit(1);
        break;
    }
  }
}

void my_print_for_vt(char *stroka, Flagi flagi) {
  int i = 0;
  while (stroka[i] != '\0') {
    if (stroka[i] == '\n') {
      printf("\n");
    } else if (stroka[i] == 127 && flagi.v) {
      printf("^?");
    } else if (flagi.t && stroka[i] == '\t')
      printf("^%c", stroka[i] + 64);
    else if ((stroka[i] > 0 && stroka[i] < 32 && stroka[i] != '\t' &&
              flagi.v)) {
      printf("^%c", stroka[i] + 64);
    } else {
      printf("%c", stroka[i]);
    }
    i++;
  }
}

void vivod(int argc, char *argv[], Flagi flagi) {
  FILE *document = fopen(argv[argc - 1], "r");
  char current_stroka[razmer_buff] = {'\0'};
  int ne_pustie_count = 0, current_not_empty = 0, pred_is_empty = 0,
      pervaja = 0;
  for (int kolvo_str = 1; fgets(current_stroka, razmer_buff, document);
       kolvo_str++) {
    current_not_empty = strlen(current_stroka) != 1;
    if (current_not_empty && pred_is_empty) pervaja = 1;
    if (flagi.s && !current_not_empty && pred_is_empty) continue;
    if (flagi.b) {
      if (current_not_empty) {
        ne_pustie_count++;
        printf("%6d\t", ne_pustie_count);
      }
    } else if (flagi.n) {
      printf("%6d\t", kolvo_str);
    }

    if (flagi.e) {
      int i_for_e = 0, vyhod_iz_cycla = 0;
      while (vyhod_iz_cycla == 0) {
        if (current_stroka[i_for_e] == '\n') {
          current_stroka[i_for_e] = '$';
          current_stroka[i_for_e + 1] = '\n';
          current_stroka[i_for_e + 2] = '\0';
          vyhod_iz_cycla = 1;
        }
        i_for_e++;
      }
    }

    if (flagi.v || flagi.t) {
      my_print_for_vt(current_stroka, flagi);
    } else if (flagi.s && pervaja) {
      pervaja = 0;
      printf("%s", current_stroka);

    } else if (flagi.s && pred_is_empty == 1) {
      // continue
    } else {
      printf("%s", current_stroka);
    }

    if (flagi.s) {
      pred_is_empty = !current_not_empty;
    }
  }
  fclose(document);
}
