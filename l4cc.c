#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
  TK_NUM = 256,
  TK_EOF,
};

typedef struct {
  int type;
  int val;
  char *input;
} Token;

Token tokens[100];

void error(char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  vfprintf(stderr, fmt, ap);
  fprintf(stderr, "\n");
  exit(1);
}

void tokenize(char *p) {
  int i = 0;
  while (*p) {
    if (isspace(*p)) {
      p++;
      continue;
    }

    if (*p == '+' || *p == '-') {
      tokens[i].type = *p;
      tokens[i].input = p;
      i++;
      p++;
      continue;
    }

    if (isdigit(*p)) {
      tokens[i].type = TK_NUM;
      tokens[i].input = p;
      tokens[i].val = strtol(p, &p, 10);
      i++;
      continue;
    }

    error("トークナイズ出来ません: %s", p);
    exit(1);
  }

  tokens[i].type = TK_EOF;
  tokens[i].input = p;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "引数の個数が正しくありません\n");
    return 1;
  }

  tokenize(argv[1]);

  printf(".intel_syntax noprefix\n");
  printf(".global main\n");
  printf("main:\n");

  if (tokens[0].type != TK_NUM)
    error("最初の項が数ではありません");
  printf("  mov rax, %d\n", tokens[0].val);

  int i = 1;
  while (tokens[i].type != TK_EOF) {
    if (tokens[i].type == '+') {
      i++;
      if (tokens[i].type != TK_NUM)
        error("予期しないトークンです: %s", tokens[i].input);
      printf("  add rax, %d\n", tokens[i].val);
      i++;
      continue;
    }

    if (tokens[i].type == '-') {
      i++;
      if (tokens[i].type != TK_NUM)
        error("予期しないトークンです: %s", tokens[i].input);
      printf("  sub rax, %d\n", tokens[i].val);
      i++;
      continue;
    }

    error("予期しないトークンです: %s", tokens[i].input);
  }

  printf("  ret\n");
  return 0;
}
