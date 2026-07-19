#include <stdio.h>
#include "utils.h"

void html_start(const char *title)
{
  printf("Content-Type: text/html\r\n\r\n");

  printf("<!DOCTYPE html>");

  printf("<html lang=\"en\">");

  printf("<head>");

  printf("<meta charset=\"UTF-8\">");
  printf("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");

  printf("<title>%s</title>", title);

  printf("</head>");

  printf("<body>");
}

void html_end(void)
{
  printf("</body>");
  printf("</html>");
}