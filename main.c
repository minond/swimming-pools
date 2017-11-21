#include <stdio.h>
#include "pools.h"

typedef struct {
  char *first_name, *last_name;
  int age;
} person;

int main(int argc, char **argv) {
  (void) argc;
  (void) argv;

  sp_pool *pool = sp_build(NULL);

  for (int i = 0; i < 15000; i++) {
    // person *marcos = malloc(sizeof(person));
    // person *marcos = (person*) sp_malloc(pool, sizeof(person));
    person *marcos = (person*) sp_fitted_malloc(pool, sizeof(person));

    marcos->first_name = "Marcos";
    marcos->last_name = "Marcos";
    marcos->age = 28;
  }

  sp_free(pool);

  return 0;
}
