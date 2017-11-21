#include <stdlib.h>
#include <stdio.h>

#define POOL_SIZE 32000

typedef struct pool_s {
  char *head, *next, *butt;
  struct pool_s *neighbor;
} sp_pool;

sp_pool *sp_build(sp_pool *neighbor) {
  printf("sp_pool\n"); // XXX
  sp_pool *pool = malloc(sizeof(sp_pool));
  char *head = malloc(POOL_SIZE);

  if (pool == NULL || head == NULL) {
    return NULL;
  }

  pool->head = head;
  pool->next = head;
  pool->butt = head + POOL_SIZE;
  pool->neighbor = NULL;

  if (neighbor != NULL && neighbor->neighbor == NULL) {
    neighbor->neighbor = pool;
  }

  return pool;
}

char *sp_malloc(sp_pool *pool, size_t req_size) {
  if (req_size > POOL_SIZE) {
    return NULL;
  }

  char *loc;
  sp_pool *ours = pool;

  while (ours->neighbor != NULL) {
    ours = ours->neighbor;
  }

  if ((long) req_size > ours->butt - ours->next) {
    ours = sp_build(ours);
  }

  if (ours == NULL || ours->next == NULL) {
    return NULL;
  }

  loc = ours->next;
  ours->next = ours->next + req_size;
  return loc;
}

char *sp_fitted_malloc(sp_pool *pool, size_t req_size) {
  if (req_size > POOL_SIZE) {
    return NULL;
  }

  char *loc;

  sp_pool *last = pool;
  sp_pool *ours = NULL;

  while (ours == NULL && pool != NULL) {
    if ((long) req_size <= pool->butt - pool->next) {
      ours = pool;
    } else {
      last = pool;
      pool = pool->neighbor;
    }
  }

  if (ours == NULL) {
    ours = sp_build(last);
  }

  if (ours == NULL || ours->next == NULL) {
    return NULL;
  }

  loc = ours->next;
  ours->next = ours->next + req_size;
  return loc;
}

void sp_free(sp_pool *pool) {
  while (pool != NULL) {
    sp_pool *temp = pool->neighbor;
    free(pool->head);
    free(pool);
    pool = temp;
  }
}
