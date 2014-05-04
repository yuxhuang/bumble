#include "proto.h"

#include <stdio.h>

int main() {
    bumble_t *packet = create_bumble_packet(4);

    packet->items[0].type = BUMBLE_SENSOR_TYPE_TEMPERATURE;
    packet->items[0].data.i = 0x1234;

    print_bumble_packet(packet);
    destroy_bumble_packet(packet);
}
