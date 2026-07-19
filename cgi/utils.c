#include <stdio.h>
#include <stdlib.h>
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

void display_array(Product products[], int count)
{
  printf("<table border=\"1\" cellspacing=\"0\" cellpadding=\"10\">");

  printf("<thead>");
  printf("<tr>");
  printf("<th>ID</th>");
  printf("<th>Name</th>");
  printf("<th>Category</th>");
  printf("<th>Brand</th>");
  printf("<th>Price ($)</th>");
  printf("<th>Stock</th>");
  printf("</tr>");
  printf("</thead>");

  printf("<tbody>");

    for (int i = 0; i < count; i++)
    {
      printf("<tr>");

      printf("<td>%d</td>", products[i].id);
      printf("<td>%s</td>", products[i].name);
      printf("<td>%s</td>", products[i].category);
      printf("<td>%s</td>", products[i].brand);
      printf("<td>%.2f</td>", products[i].price);
      printf("<td>%d</td>", products[i].stock);

      printf("</tr>");
    }

  printf("</tbody>");

  printf("</table>");
}

Product *read_products(const char *filename, int *count)
{
    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        *count = 0;
        return NULL;
    }

    char line[512];

    /* Skip CSV header */
    fgets(line, sizeof(line), file);

    Product *products = NULL;

    *count = 0;

    while (fgets(line, sizeof(line), file))
    {
        products = realloc(products, sizeof(Product) * (*count + 1));

        Product *product = &products[*count];

        sscanf(
            line,
            "%d,%99[^,],%49[^,],%49[^,],%lf,%d",
            &product->id,
            product->name,
            product->category,
            product->brand,
            &product->price,
            &product->stock
        );

        (*count)++;
    }

    fclose(file);

    return products;
}