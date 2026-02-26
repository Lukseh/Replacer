#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "./replacer.h"

int main(void)
{
  char *src = "I love $BAND";

  char *rep = Replace(src, "BAND", "Deftones");

  printf("%s -> %s\n", src, rep);

  FreeString(rep);

  return 0;
}