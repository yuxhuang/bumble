#include "bumble_proto.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#ifdef __cplusplus
extern "C" {
#endif

bumble_t *create_bumble_packet(size_t size) {
    bumble_t *result = (bumble_t*) malloc(sizeof(bumble_t) + size * sizeof(bumble_item_t));
    result->size = size;
    return result;
}

void destroy_bumble_packet(bumble_t *packet) {
    assert(packet != NULL);
    
    free(packet);
}

size_t sizeof_bumble_packet(bumble_t *packet) {
    return sizeof(bumble_t) + packet->size * sizeof(bumble_item_t);
}

void print_bumble_packet(bumble_t *packet) {
    assert(packet != NULL);

    printf("Bumble packet:\n");
    for (int idx = 0; idx < packet->size; idx ++) {
        printf("\tType: %d\n", packet->items[idx].type);
        switch (packet->items[idx].data_type) {
            case BUMBLE_ITEM_SIGNED:
                printf("\tData: %d\n", packet->items[idx].data.i);
                break;
            case BUMBLE_ITEM_UNSIGNED:
                printf("\tData: %u\n", packet->items[idx].data.u);
                break;
            case BUMBLE_ITEM_FLOAT:
                printf("\tData: %f\n", packet->items[idx].data.f);
                break;
        }
    }
}

#ifdef __cplusplus
}
#endif
