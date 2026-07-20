#include "utils.h"

int main(void)
{
  html_start("Add Product");

  // Product product =
  // {
  //   11,
  //   "HP EliteBook 840 G10",
  //   "Laptop",
  //   "HP",
  //   1499.99,
  //   15
  // };

  // if (add_product("/home/praxis/Desktop/www/DATA/data_it.csv", product))
  // {
  //   printf("Product added successfully.\n");
  // }
  // else
  // {
  //   printf("Failed to add product.\n");
  // }
  char *raw = get_user_input();

if (raw == NULL)
{
    /* Handle error */
    return 1;
}

char decoded[1024];

url_decode(raw, decoded);

Product product = {0};

char id[20];
char price[20];
char stock[20];

extract_field(decoded, "id", id, sizeof(id));
extract_field(decoded, "name", product.name, sizeof(product.name));
extract_field(decoded, "category", product.category, sizeof(product.category));
extract_field(decoded, "brand", product.brand, sizeof(product.brand));
extract_field(decoded, "price", price, sizeof(price));
extract_field(decoded, "stock", stock, sizeof(stock));

product.id = atoi(id);
product.price = atof(price);
product.stock = atoi(stock);



display_product(product);
add_product("/home/praxis/Desktop/www/DATA/data_it.csv", product);
free(raw);
html_end();

return 0;
}