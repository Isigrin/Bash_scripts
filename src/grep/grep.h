#ifndef GREP_H
#define GREP_H

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Flagi {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int reg;
} Flagi;
void parser_flagi(int argc, char *argv[], Flagi *flagi, char *patterns);
void vivod(int argc, char *argv[], Flagi flagi, char *patterns);

#endif // GREP_H