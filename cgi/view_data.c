#include <stdio.h>
#include "utils.h"

int main(void)
{
  html_start("View Data");

  printf("<h1>View Data</h1>");

  printf("<p>CGI program is running successfully.</p>");

  html_end();

  return 0;
}