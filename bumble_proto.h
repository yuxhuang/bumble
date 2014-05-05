#ifndef __BUMBLE_PROTO_H

#define __BUMBLE_PROTO_H

#include <stdint.h>

#define BUMBLE_SENSOR_TYPE_TEMPERATURE  0x0001
#define BUMBLE_SENSOR_TYPE_HUMIDITY     0X0002
#define BUMBLE_SENSOR_TYPE_BAROMETRIC   0x0003
#define BUMBLE_SENSOR_TYPE_LUMINOSITY   0x0010

#ifdef __cplusplus
extern "C" {
#endif

enum bumble_item_type {
    BUMBLE_ITEM_SIGNED,
    BUMBLE_ITEM_UNSIGNED,
    BUMBLE_ITEM_FLOAT
};

typedef int16_t bumble_size_t;

typedef struct __bumble_item_t {
    uint16_t type;
    enum bumble_item_type data_type;
    union {
        int32_t i;
        uint32_t u;
        float f;
    } data;
} bumble_item_t;

typedef struct __bumble_t {
    bumble_size_t size;
    bumble_item_t items[0];
} bumble_t;

// create a bumble packet with a certain size.
bumble_t*   create_bumble_packet(bumble_size_t size);

// get the size of the packet
bumble_size_t      sizeof_bumble_packet(bumble_t *packet);

// destroy a bumble packet
void        destroy_bumble_packet(bumble_t *packet);

// print the trace of a bumble packet
void        print_bumble_packet(bumble_t *);

#ifdef __cplusplus
}
#endif

#endif

