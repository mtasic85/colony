#ifndef CO_CTX_H
#define CO_CTX_H

struct _co_ctx_t;
struct co_ctx_t;

#define CO_CTX(obj) ((struct co_ctx_t*)(obj))

#include <stdlib.h>

#include "object.h"


/*
ctx_A: Context = Context(None, None, None)

ctx_A.on_message((message: str) -> Result[str, str] {
    message == 'set_x_10' ? {
        ns.x = 10
        Ok('')
    } : message == 'set_y_20' ? {
        ns.y = 20
        Ok('')
    } : message == 'set_z' ? {
        ns.z = ns.x + ns.y
        Ok('')
    } : message == 'get_z' ? {
        ns.z
        Ok('')
    } : {
        Err('ctx_A: unknown message')
    }
})

ctx_A.post_message('set_x_10')
ctx_A.post_message('set_y_20')
ctx_A.post_message('set_z')

// NOTE: post_message returns `Future[str]`
z: str = ctx_A.post_message('get_z').await()
*/

typedef struct _co_ctx_t {
    CO_GC_HEAD;
    struct co_object_t *parent;         // parent: Option[Context] = None
    struct co_object_t *ns;             // ns: Option[Namespace] = None
    struct co_object_t *error;          // error: Option[object] = None
    struct co_object_t *on_error_cb;    // on_error_cb: 
    struct co_object_t *message_queue;  // message_queue: Queue[str]() = Queue[str]()
    struct co_object_t *on_message_cb;  // on_message_cb: Option[fn[Callable, Result[str, str]]] = None
} _co_ctx_t;

typedef struct co_ctx_t {
    CO_OBJECT_HEAD;
    struct _co_ctx_t *ctx;
} co_ctx_t;

/* (parent: Option[Context]=None, ns: Option[Namespace]=None, on_message_cb: Option[fn[Callable, Result[str, str]]]=None) -> Context */
struct co_object_t *co_ctx_new(struct co_object_t *ctx, struct co_object_t *parent, struct co_object_t *ns);

/* (self: Context) -> None */
struct co_object_t *co_ctx_free(struct co_object_t *ctx, struct co_object_t *self);

/* (self: Context, on_error_cb: fn[Callable, Result[object, str]]) -> Context */
struct co_object_t *co_ctx_on_error(struct co_object_t *ctx, struct co_object_t *on_error_cb);

/* (self: Context, error: object) -> Context */
struct co_object_t *co_ctx_set_error(struct co_object_t *ctx, struct co_object_t *error);

/* (self: Context) -> object */
struct co_object_t *co_ctx_get_error(struct co_object_t *ctx);

/* (self: Context, on_message_cb: fn[Callable, Result[str, str]]) -> Context */
struct co_object_t *co_ctx_on_message(struct co_object_t *ctx, struct co_object_t *self, struct co_object_t *on_message_cb);

/* (self: Context, message: str) -> Future[str] */
struct co_object_t *co_ctx_post_message(struct co_object_t *ctx, struct co_object_t *self, struct co_object_t *message);

/*
 * FIXME: finish implementation
struct co_object_t *co_ctx_type = co_type_new(
    ctx,
    co_object_getattr(ctx, (struct co_namespace_t*)ctx->gc), (struct co_object_t*)&(co_str_new(ctx, )),
    'Ctx',
    [object],
    Namespace()
);
*/

#endif
