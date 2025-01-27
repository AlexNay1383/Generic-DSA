#ifndef VECTOR_H_
#define VECTOR_H_

typedef int IndexT;
typedef unsigned int SizeT;

#define VECTOR_MIN_CAPACITY ((SizeT)8)
#define VECTOR_CAP_MULTIPLIER ((SizeT)2)

typedef struct
{
  void* data;
  SizeT size;
  SizeT capacity;
  const SizeT typesize;
} Vector;

Vector vec_init(SizeT typesize);

void vec_reserve(Vector* vec, SizeT capacity);
void vec_increase_cap(Vector* vec, SizeT min_cap);

void* vec_get_ptr(Vector* vec, IndexT index);
#define vec_get(vec, i, t) (*((t*) vec_get_ptr(vec, i)))
void vec_set(Vector* vec, IndexT index, void* data);
SizeT vec_find(Vector* vec, void* data);

void vec_push(Vector* vec, IndexT index, void* el);
void vec_push_back(Vector* vec, void* el);
void vec_push_front(Vector* vec, void* el);

void* vec_pop_ptr(Vector* vec, IndexT index);
void* vec_pop_front_ptr(Vector* vec);
void* vec_pop_back_ptr(Vector* vec);
#define vec_pop(vec, i, t) (*((t*) vec_pop_ptr(vec, i)))
#define vec_pop_front(vec, t) (*((t*) vec_pop_front_ptr(vec)))
#define vec_pop_back(vec, t) (*((t*) vec_pop_back_ptr(vec)))

void vec_release(Vector* vec);

#endif // VECTOR_H_