#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
bool add_product(const char *filename, Product product);
char *get_user_input(void);
void url_decode(const char *src, char *dest);
bool extract_field(const char *data,
                   const char *field,
                   char *value,
                   size_t value_size);
                   
void display_product(Product product);
#endif