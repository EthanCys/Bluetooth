#ifndef BTSNOOP_H
#define BTSNOOP_H

#include <stdint.h>
#include <sys/time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>




#define BTSNOOP_VERSION "1.0"
#define TRANSPORT_TYPE_CMD 1
#define TRANSPORT_TYPE_EVT 4
#define TRANSPORT_TYPE_ACL 2
#define TRANSPORT_TYPE_SCO 3


uint8_t btsnoop_open(const char *filename);
uint8_t btsnoop_close(void);
uint8_t btsnoop_write_packet(uint8_t packet_type, uint8_t in, uint16_t len, uint8_t *data);
void big_endian_write(uint8_t *buf, uint32_t val, uint32_t len);
void big_endian_write_64(uint8_t *buf, uint64_t val);
    



#endif
