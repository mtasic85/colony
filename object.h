#ifndef CO_OBJECT_H
#define CO_OBJECT_H

enum co_kind_t;
union co_value_t;
struct co_object_t;

#include <stdlib.h>
#include <stdint.h>
#include "ctx.h"
#include "object.h"

#define CO_OBJECT_INC_RC(ctx, obj) do { \
    ((struct co_object_t *)(obj))->rc++; \
} while(0)

#define CO_OBJECT_DEC_RC(ctx, obj) do { \
    if (obj == NULL) break; \
    ((struct co_object_t *)(obj))->rc--; \
    if (((struct co_object_t *)(obj))->rc == 0) { \
        co_object_free(ctx, (struct co_object_t *)(obj)); \
    } \
} while(0)

typedef enum co_kind_t {
    CO_KIND_BOOL,
    CO_KIND_U8,
    CO_KIND_U16,
    CO_KIND_U32,
    CO_KIND_U64,
    CO_KIND_I8,
    CO_KIND_I16,
    CO_KIND_I32,
    CO_KIND_I64,
    CO_KIND_F32,
    CO_KIND_F64,
    CO_KIND_BYTES,
    CO_KIND_STR,
    CO_KIND_LIST,
    CO_KIND_MUT_LIST,
    CO_KIND_DICT,
    CO_KIND_MUT_DICT,
    CO_KIND_NS,
    CO_KIND_CODE,
    CO_KIND_FUNC,
    CO_KIND_CLOSURE,
    CO_KIND_TUPLE,
    CO_KIND_UNION,
    CO_KIND_LW_TYPE, // light-weight
    CO_KIND_PTR,
    CO_KIND_OWNED_PTR
} co_kind_t;

typedef union co_value_t {
    _Bool b;
    uint8_t u8;
    uint16_t u16;
    uint32_t u32;
    uint64_t u64;
    int8_t i8;
    int16_t i16;
    int32_t i32;
    int64_t i64;
    float f32;
    double f64;
    void *bytes;
    void *str;
    void *list;
    void *mut_list;
    void *dict;
    void *mut_dict;
    void *ns;
    void *code;
    void *func;
    void *closue;
    void *tuple;
    void *union_;
    void *lw_type;
    void *ptr;
    void *owned_ptr;
} co_value_t;

typedef struct co_object_t {
    size_t rc;
    enum co_kind_t kind;
    union co_value_t value;
} co_object_t;

co_object_t *co_object_new(struct co_ctx_t * ctx, co_kind_t kind, co_value_t value);
co_object_t *co_object_free(struct co_ctx_t * ctx, co_object_t *self);

// (self: any) -> str | Err
co_object_t *co_object_repr(struct co_ctx_t * ctx, co_object_t *self);

// (self: any) -> u64 | Err
co_object_t *co_object_hash(struct co_ctx_t * ctx, co_object_t *self);

#endif
