#include <stdlib.h>

typedef struct pool_s {
  char *head, *next, *butt;
  struct pool_s *neighbor;
} sp_pool;

sp_pool *sp_build(sp_pool*);
char *sp_malloc(sp_pool*, size_t);
char *sp_fitted_malloc(sp_pool*, size_t);
void sp_free(sp_pool*);
