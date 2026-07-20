
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

bool add_product(const char *filename, Product product){
  FILE *file = fopen(filename, "a");

  if (file == NULL){
    return false;
  }

  fprintf(
    file,
    "%d,%s,%s,%s,%.2f,%d\n",
    product.id,
    product.name,
    product.category,
    product.brand,
    product.price,
    product.stock
  );

  fclose(file);

  return true;
}

// char *get_user_input(){
//   char *input = malloc(256 * sizeof(char));
//   if (input == NULL) {
//     return NULL;
//   }
  

//   //
//   char *length = getenv("CONTENT_LENGTH");
//   int size = length ? atoi(length) : 0;
//   fread(input, 1, size, stdin);
//   input[size] = '\0';

//   return input;
// }
char *get_user_input(void)
{
  char *length = getenv("CONTENT_LENGTH");
  
  if (length == NULL){
    return NULL;
  }

  int size = atoi(length);
  char *input = malloc(size + 1);
  
  if (input == NULL){
    return NULL;
  }
  
  size_t bytes_read = fread(input, 1, size, stdin);
  
  input[bytes_read] = '\0';
  return input;
}

void url_decode(const char *src, char *dest)
{
    while (*src)
    {
      if (*src == '+')
      {
          *dest = ' ';
      }
      else
      {
          *dest = *src;
      }
      src++;
      dest++;
    }

    *dest = '\0';
}
bool extract_field(const char *data,
                   const char *field,
                   char *value,
                   size_t value_size)
{
    char pattern[64];

    snprintf(pattern, sizeof(pattern), "%s=", field);

    const char *start = strstr(data, pattern);

    if (start == NULL)
    {
        return false;
    }

    start += strlen(pattern);

    const char *end = strchr(start, '&');

    if (end == NULL)
    {
        end = start + strlen(start);
    }

    size_t length = end - start;

    if (length >= value_size)
    {
        length = value_size - 1;
    }

    strncpy(value, start, length);

    value[length] = '\0';

    return true;
}

void display_product(Product product)
{
    printf("<table border=\"1\" cellspacing=\"0\" cellpadding=\"8\">");

    printf("<tr>");
    printf("<th>ID</th>");
    printf("<td>%d</td>", product.id);
    printf("</tr>");

    printf("<tr>");
    printf("<th>Name</th>");
    printf("<td>%s</td>", product.name);
    printf("</tr>");

    printf("<tr>");
    printf("<th>Category</th>");
    printf("<td>%s</td>", product.category);
    printf("</tr>");

    printf("<tr>");
    printf("<th>Brand</th>");
    printf("<td>%s</td>", product.brand);
    printf("</tr>");

    printf("<tr>");
    printf("<th>Price</th>");
    printf("<td>%.2f</td>", product.price);
    printf("</tr>");

    printf("<tr>");
    printf("<th>Stock</th>");
    printf("<td>%d</td>", product.stock);
    printf("</tr>");

    printf("</table>");
}