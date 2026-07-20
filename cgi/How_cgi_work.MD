# How Form Data Travels From the Browser to Your C Program

A beginner's guide to understanding CGI — using the **Add Product** form as the running example.

This is the most important concept in CGI programming: **how a form on a web page turns into data your C program can actually read.** Once this clicks, everything else in CGI (routing, parsing, validation, writing to CSV) makes a lot more sense.

---

## Table of Contents

1. [The big picture](#the-big-picture)
2. [Step-by-step walkthrough](#step-by-step-walkthrough)
3. [The complete flow diagram](#the-complete-flow-diagram)
4. [Beginner's mental model — 4 questions](#beginners-mental-model--4-questions)
5. [Quick reference](#quick-reference)

---

## The big picture

Think of it like passing a note in a classroom.

- The **student** (browser) writes a note (the form data).
- The **note** gets folded into a specific format everyone agrees on (URL encoding).
- The **teacher** (Apache) receives the note and hands it to the right person (your CGI program).
- That person **unfolds the note** (parses it) and **writes the answer on the board** (saves it to `data.csv`).

Twelve steps happen between "user clicks a button" and "a new line appears in `data.csv`." None of them are complicated on their own — they're just easy to lose track of if no one lays them out in order. That's what this README does.

---

## Step-by-step walkthrough

### Step 1 — The user fills in the form

Nothing has been sent anywhere yet. Everything below only exists inside the browser:

```text
Product ID   : 11
Product Name : HP EliteBook
Category     : Laptop
Brand        : HP
Price        : 1499.99
Stock        : 15
```

### Step 2 — The user clicks "Add Product"

The browser reads the form's own instructions:

```html
<form action="/cgi/add_data.cgi" method="POST">
```

That single line tells the browser two things:

| What the browser learns | Value |
|---|---|
| Destination | `/cgi/add_data.cgi` |
| Method | `POST` |

### Step 3 — The browser builds the POST data

Every input becomes a `name=value` pair:

```text
id=11
name=HP EliteBook
category=Laptop
brand=HP
price=1499.99
stock=15
```

Then the browser joins them all with `&`:

```text
id=11&name=HP+EliteBook&category=Laptop&brand=HP&price=1499.99&stock=15
```

Notice that the space in "HP EliteBook" became a `+`. This transformation is called **URL encoding** — it's how special characters (spaces, `&`, `=`, etc.) travel safely inside one long string.

### Step 4 — The browser sends the HTTP request

```http
POST /cgi/add_data.cgi HTTP/1.1
Host: cgi-data.local
Content-Length: 76
Content-Type: application/x-www-form-urlencoded

id=11&name=HP+EliteBook&category=Laptop&brand=HP&price=1499.99&stock=15
```

Don't memorize this. Just take away one idea: **the entire form becomes one long string.**

### Step 5 — Apache receives it

Apache sees a `POST` request aimed at `add_data.cgi`, so it starts that program.

### Step 6 — Apache prepares the environment

Apache hands your program two things:

**Environment variables** — readable with `getenv()`:

```text
REQUEST_METHOD=POST
CONTENT_LENGTH=76
```

```c
char *length = getenv("CONTENT_LENGTH");
```

**`stdin`** — the actual POST data, delivered exactly like something typed at a keyboard:

```text
id=11&name=HP+EliteBook&category=Laptop&brand=HP&price=1499.99&stock=15
```

### Step 7 — Your C program reads `CONTENT_LENGTH`

```c
char *length = getenv("CONTENT_LENGTH");
int size = atoi(length);
```

| Variable | Value |
|---|---|
| `length` | `"76"` |
| `size` | `76` |

### Step 8 — Create a buffer

```c
char buffer[1024];
```

Think of `buffer` as an empty box, waiting to be filled. Right now it holds nothing (`""`).

### Step 9 — Read `stdin` into the buffer

```c
fread(buffer, 1, size, stdin);
```

`buffer` now holds:

```text
id=11&name=HP+EliteBook&category=Laptop&brand=HP&price=1499.99&stock=15
```

**This is the biggest milestone in the whole flow** — your C program has successfully received data sent from a browser.

### Step 10 — Parse the string

`buffer` is still just one long sentence. It needs to be split twice.

**First split — on `&`** (separates each field):

```text
id=11
name=HP+EliteBook
category=Laptop
brand=HP
price=1499.99
stock=15
```

**Second split — on `=`** (separates key from value):

| key | value |
|---|---|
| `id` | `11` |
| `name` | `HP+EliteBook` |
| `category` | `Laptop` |
| `brand` | `HP` |
| `price` | `1499.99` |
| `stock` | `15` |

### Step 11 — Convert into a `Product`

Once every key/value pair is extracted (and `+` is turned back into a space), you build a structure:

```c
Product product;
```

```text
Product
  id       = 11
  name     = HP EliteBook
  category = Laptop
  brand    = HP
  price    = 1499.99
  stock    = 15
```

### Step 12 — Save

```c
add_product(filename, product);
```

This writes one new line into `data.csv`:

```text
11,HP EliteBook,Laptop,HP,1499.99,15
```

---

## The complete flow diagram

```text
User
 │
 │ types data
 ▼
HTML Form
 │
 │ click Submit
 ▼
Browser
 │
 │ converts to
 │ id=11&name=...
 ▼
HTTP POST
 │
 ▼
Apache
 │
 │ sets CONTENT_LENGTH
 │ writes data to stdin
 ▼
add_data.cgi
 │
 │ fread()
 ▼
buffer
 │
 │ parse (split on & then =)
 ▼
Product structure
 │
 │ add_product()
 ▼
data.csv
```

---

## Beginner's mental model — 4 questions

Every time you build a new CGI form, ask yourself these four questions in order:

1. **What does the browser send?**
   → A URL-encoded string, e.g. `id=11&name=...`

2. **How does my C program receive it?**
   → Through `stdin`, with the size given by the `CONTENT_LENGTH` environment variable.

3. **How do I turn that string into usable values?**
   → Parse the `key=value` pairs: split on `&` first, then split each piece on `=`.

4. **What do I do with those values?**
   → Store them in a structure (like `Product`), validate them, and write them to `data.csv`.

If you can answer all four for any form you build, you understand the core of how HTML talks to CGI — the rest (session cookies, authentication, multiple content types) is built on top of this same foundation.

---

## Quick reference

| Concept | C tool | Purpose |
|---|---|---|
| Request method | `getenv("REQUEST_METHOD")` | Confirm it's `POST` (vs `GET`) |
| Payload size | `getenv("CONTENT_LENGTH")` + `atoi()` | Know how many bytes to read |
| Raw payload | `fread(buffer, 1, size, stdin)` | Read the POST body into memory |
| Field separator | `&` | Splits the string into individual fields |
| Key/value separator | `=` | Splits each field into name and value |
| Space encoding | `+` (or `%20`) | Must be decoded back to a real space |
| Final storage | `add_product()` → `data.csv` | Where the parsed values end up |