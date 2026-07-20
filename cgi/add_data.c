#include "utils.h"

int main(void)
{
    char *raw = get_user_input();

    if (raw == NULL)
    {
        html_start("Add Product");
        printf("<p>Failed to read form data.</p>");
        html_end();
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

    bool ok = add_product("/home/praxis/Desktop/www/DATA/data_it.csv", product);

    free(raw);

    if (ok)
    {
        /* Success: redirect instead of printing a page.
           This becomes the browser's "last request" — a safe GET. */
        printf("Status: 302 Found\r\n");
        printf("Location: /cgi/view_data.cgi\r\n");
        printf("\r\n");
    }
    else
    {
        /* Failure: it's fine to show a page here, since a failed
           write has no side effect to accidentally repeat. */
        html_start("Add Product");
        printf("<p>Failed to add product.</p>");
        html_end();
    }

    return 0;
}