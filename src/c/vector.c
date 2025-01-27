#include "vector.h"

#include <stdlib.h>
#include <string.h>


Vector vec_init(SizeT typesize)
{
  Vector vec = {NULL, 0, 0, typesize};

  return vec;
}

static void _copy_el(void* dest, void* src, SizeT typesize)
{
  if(dest == NULL || src == NULL)
  {
    return;
  }
  memcpy(dest, src, typesize);
}

void vec_reserve(Vector* vec, SizeT capacity)
{
  if(vec->data == NULL)
  {
    vec->data = malloc(capacity * vec->typesize);
  }
  else
  {
    vec->data = realloc(vec->data, capacity * vec->typesize);
  }

  vec->capacity = capacity;
}

void vec_increase_cap(Vector* vec, SizeT min_cap)
{
  if(vec->capacity < VECTOR_MIN_CAPACITY || vec->data == NULL)
  {
    vec_reserve(vec, VECTOR_MIN_CAPACITY);
  }

  else while(vec->capacity < min_cap)
  {
    vec_reserve(vec, vec->capacity * VECTOR_CAP_MULTIPLIER);
  }
}


void* vec_get_ptr(Vector* vec, IndexT index)
{
  return (vec->data + (index * vec->typesize));
}

void vec_set(Vector* vec, IndexT index, void* data)
{
  _copy_el(vec_get_ptr(vec, index), data, vec->typesize);
}

SizeT vec_find(Vector* vec, void* data)
{
  if(vec->size == 0)
  {
    return -1;
  }

  for(SizeT i = 0; i < vec->size; i++)
  {
    if(memcmp(vec_get_ptr(vec, i), data, vec->typesize) == 0)
    {
      return i;
    }
  }

  return -1;
}


void vec_push(Vector* vec, IndexT index, void* el)
{
  if(index < 0 || index > vec->size)
  {
    return;
  }

  if(vec->size >= vec->capacity)
  {
    vec_increase_cap(vec, vec->capacity + 1);
  }

  for(SizeT i = vec->size; i > index; i--)
  {
    _copy_el(vec_get_ptr(vec, i), vec_get_ptr(vec, i - 1), vec->typesize);
  }

  _copy_el(vec_get_ptr(vec, index), el, vec->typesize);
  vec->size++;
}

void vec_push_back(Vector* vec, void* el)
{
  vec_push(vec, vec->size, el);
}

void vec_push_front(Vector* vec, void* el)
{
  vec_push(vec, 0, el);
}


void* vec_pop_ptr(Vector* vec, IndexT index)
{
  if(index < 0 || index >= vec->size)
  {
    return NULL;
  }

  void* el = vec->data + index * vec->typesize;

  for(SizeT i = index; i < vec->size - 1; i++)
  {
    _copy_el(vec_get_ptr(vec, i), vec_get_ptr(vec, i+1), vec->typesize);
  }

  vec->size--;

  return el;
}

void* vec_pop_front_ptr(Vector* vec)
{
  return vec_pop_ptr(vec, 0);
}

void* vec_pop_back_ptr(Vector* vec)
{
  return vec_pop_ptr(vec, vec->size - 1);
}

void vec_release(Vector* vec)
{
  free(vec->data);
  vec->data = NULL;
  vec->size = 0;
  vec->capacity = 0;
}