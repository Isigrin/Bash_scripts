#ifndef CAT_H
#define CAT_H

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Flagi {
  int t;
  int b;
  int e;
  int n;
  int s;
  int v;
} Flagi;

void parser_flagi(int argc, char *argv[], Flagi *flagi);
void vivod(int argc, char *argv[], Flagi flagi);

#endif  // CAT_H