#include <stdio.h>
#include "utils.h"

int main(void)
{
  printf("Content-Type: text/plain\r\n\r\n");// this is verry important to avoid the error "Premature end of script headers" in the browser

  Product product =
  {
    11,
    "HP EliteBook 840 G10",
    "Laptop",
    "HP",
    1499.99,
    15
  };

  if (add_product("/home/praxis/Desktop/www/DATA/data_it.csv", product))
  {
    printf("Product added successfully.\n");
  }
  else
  {
    printf("Failed to add product.\n");
  }

  return 0;
}