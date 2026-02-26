#pragma once

#ifdef REPL_EXPORTS
#define REPL_EXPORTS __declspec(dllexport)
#else
#define REPL_EXPORTS __declspec(dllimport)
#endif

#include <stdlib.h>
#include <string.h>

typedef struct Reps
{
  const char *pattern;
  const char *value;
} Reps;

// Used for GO
char *ReplaceVWrapper(const char *source, const char *pattern, const char *value);

char *Replace(const char *source, const char *pattern, const char *value);
char *ReplaceV(const char *source, Reps rep);
char *ReplaceAll(const char *source, Reps *reps, size_t amount);
void FreeString(char *str);
