#include <stdio.h>
#include "core/ctx.h"
#include "object/object.h"

int main(int argc, char **argv) {
    co_object_t *ctx = co_ctx_new(NULL);
    co_unref(NULL, ctx);
    return 0;
}
