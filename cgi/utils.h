#ifndef UTILS_H
#define UTILS_H

#define MAX_NAME      100
#define MAX_CATEGORY   50
#define MAX_BRAND      50

typedef struct
{
  int id;
  char name[MAX_NAME];
  char category[MAX_CATEGORY];
  char brand[MAX_BRAND];
  double price;
  int stock;

} Product;

void html_start(const char *title);
void html_end(void);
Product *read_products(const char *filename, int *count);
void display_array(Product products[], int count);

#endif