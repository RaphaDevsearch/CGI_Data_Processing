#include <stdio.h>
#include "utils.h"

int main(void)
{

  // Product products[] =
  // {
  //   {1, "ThinkPad X1 Carbon", "Laptop",    "Lenovo", 1899.99, 12},
  //   {2, "MacBook Pro 14",     "Laptop",    "Apple",  2199.00, 8},
  //   {3, "Dell UltraSharp U2723QE", "Monitor", "Dell", 649.99, 20},
  //   {4, "MX Master 3S",       "Mouse",     "Logitech", 99.99, 35},
  //   {5, "Keychron K8 Pro",    "Keyboard",  "Keychron", 109.00, 18},
  //   {6, "Samsung 990 Pro 1TB","SSD",       "Samsung", 129.99, 42},
  //   {7, "RTX 4070",           "Graphics Card", "NVIDIA", 599.99, 6},
  //   {8, "Raspberry Pi 5",     "Single Board Computer", "Raspberry Pi", 80.00, 25},
  //   {9, "UniFi U6 Lite",      "Access Point", "Ubiquiti", 99.00, 14},
  //   {10, "Synology DS224+",   "NAS",       "Synology", 299.99, 9}
  // };
  int count = 0;

  html_start("View Data");

  printf("<h1>View Data</h1>");

  Product *products = read_products("data_it.csv", &count);

  display_array(
    products,
    count
  );

  printf("<p>CGI program is running successfully.</p>");

  html_end();

  return 0;
}