#ifndef VECTOR_H
#define VECTOR_H

#include "generic.h"
#include "status.h"

typedef void* MY_VECTOR;

struct vector
{
  int size;
  int capacity;
  Item* data;
};
typedef struct vector Vector;


MY_VECTOR vector_init_default(void);

Status vector_push_back(MY_VECTOR hVector, Item item);

Status vector_pop_back(MY_VECTOR hVector);

int vector_get_size(MY_VECTOR hVector);
int vector_get_capacity(MY_VECTOR hVector);

Boolean vector_empty(MY_VECTOR hVector);

Item* vector_at(MY_VECTOR hVector, unsigned int index);

void vector_destroy(MY_VECTOR* phVector);

#endif