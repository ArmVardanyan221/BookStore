#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    char *author;
    size_t cost;
} Book;

typedef struct {
    Book book;
    size_t count;
} eachBook;
typedef struct {
    eachBook *books;
    size_t BookSize;
    // size_t *count;
    size_t bookCount;
    size_t capasity;
}Bookstore;

void openStore(Bookstore *store) {
    assert(store);
    store -> books = (eachBook*)malloc(sizeof(eachBook) * 100);
    assert(store -> books);
    store -> BookSize = 0;
    store -> bookCount = 0;
    store -> capasity = 100;
    for (int i = 0; i < store -> capasity; ++i) {
        store -> books[i].count = 0;
    }
}
void pushBook(Bookstore *store, Book *add, int addedCount) {
    assert(store || add);
    if (store -> BookSize == store -> capasity) {
        store -> books = (eachBook*)realloc(store -> books, sizeof(eachBook) * (store -> capasity * 2));
        //store -> count = (size_t*)realloc(store -> count, sizeof(size_t) * store -> capasity * 2);
        assert(store -> books);
        store -> capasity *= 2;
    }
    store -> books[store -> BookSize].book = *add;
    store -> books[(store -> BookSize)++].count += addedCount;
    store -> bookCount += addedCount;
}
int includes(Bookstore *store, const Book *add) {
    assert(store);
    for (int i = 0; i < store -> BookSize; ++i) {
        if (!strcmp(store -> books[i].book.name, add -> name)) {
            return i;
        }
    }
    return -1;
}
int includesbyNames(const Bookstore *store, const char *name) {
    assert(store || name);
    for (int i = 0; i < store -> BookSize; ++i) {
        if (!strcmp(store -> books[i].book.name, name)) {
            return i;
        }
    }
    return -1;
}
int includesbyAuthor(const Bookstore *store, const char *author) {
    assert(store || author);
    for (int i = 0; i < store -> BookSize; ++i) {
        if (!strcmp(store -> books[i].book.author, author)) {
            return i;
        }
    }
    return -1;
}
void addBook(Bookstore *store, Book *addedBook, int addedCount) {
    assert(store || addedBook);
    if (store -> BookSize == 0) {
        openStore(store);
        pushBook(store, addedBook, addedCount);
        return;
    }
    int index = includes(store, addedBook);
    if (index != -1) {
        store -> books[index].count += addedCount;
        store -> bookCount += addedCount;
    } else {
        pushBook(store, addedBook, addedCount);
    }
}

void deleteBook(Bookstore *store, const Book *deletedBook) {
    assert(store || deletedBook);
    if (store -> BookSize == 0) {
        printf("Dont have this Book");
        return;
    }
    int index = includes(store, deletedBook);
    if (index == -1 || store -> books[index].count == 0) {
        printf("Dont have this Book");
        return;
    } else {
        --(store -> books[index].count);
        --(store -> bookCount);
    }
}
void infoBook(const Bookstore *store, const char *name) {
    assert(store || name);
    int ind = includesbyNames(store, name);
    if (ind == -1) {
        printf("Don't have Book");
        return;
    } else if (store -> books[ind].count == 0) {
        printf("Don't have this book but ");
    }
        printf("Author: %s, and it is cost: %zuAMD\n", store -> books[ind].book.author, store -> books[ind].book.cost);
    
}

void listBook(Bookstore *store) {
    assert(store);
    if (store -> BookSize == 0) {
        printf("Dont have this Book");
        return;
    }
    for (int i = 0; i < store -> BookSize; ++i) {
        if (store -> books[i].count != 0) {
            printf("There are %zu of this books: %s it cost's %zuAMD\n",
            store -> books[i].count, store -> books[i].book.name, store -> books[i].book.cost);
        }
    }
}
void searchBook(const Bookstore *store, const char* name) {
    assert(store || name);
    if (store -> BookSize == 0) {
        printf("Dont have this Book");
        return;
    }
    int index = includesbyNames(store, name);
    if (index == -1 || store -> books[index].count == 0) {
        printf("False");
    } else {
        printf("True");
    }
}
int main() {
    Book Book1;
    Book1.author = "Raffi";
    Book1.name = "Samvel";
    Book1.cost = 500;
    
    Book Book2;
    Book2.author = "Raffi";
    Book2.name = "Samvel1";
    Book2.cost = 1000;

    Book Book3;
    Book3.author = "Hovhannes";
    Book3.name = "Mi katil mexr";
    Book3.cost = 5000;

    Bookstore Arman;
    openStore(&Arman);
    addBook(&Arman, &Book1, 7);
    addBook(&Arman, &Book2, 5);
    addBook(&Arman, &Book3, 10);
    listBook(&Arman);
    infoBook(&Arman, "Samvel");
    return 0;
    
}
