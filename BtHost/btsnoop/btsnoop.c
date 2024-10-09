#include "btsnoop.h"

int btsnoop_fd = -1;

void big_endian_write(uint8_t *buf, uint32_t val, uint32_t len){
    uint32_t i;
    for(i = 0; i < len; i++){
        buf[i] = (val >> (i * 8)) & 0xff;
    }
}

void big_endian_write_64(uint8_t *buf, uint64_t val){
    big_endian_write(buf, (uint32_t)(val >> 32), 4);
    big_endian_write(buf + 4, (uint32_t)val, 4);
}

uint8_t btsnoop_open(const char *filename){
    btsnoop_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if(btsnoop_fd < 0){
        return 1;
    }

    //write(logfile_fd, "btsnoop\0\0\0\0\1\0\0\x3\xea", 16);
    write(btsnoop_fd, "btsnoop\0\0\0\0\1\0\0\x3\xea", 16);

    return 0;
}
uint8_t btsnoop_close(void){
    if(btsnoop_fd < 0){
        return 1;
    }
    close(btsnoop_fd);
    btsnoop_fd = -1;
    return 0;

}
uint8_t btsnoop_write_packet(uint8_t packet_type, uint8_t in, uint16_t len, uint8_t *data){
    uint32_t original_len;
    uint32_t included_len;
    uint32_t flags;
    uint32_t drops;
    uint64_t timestamp;

    if(packet_type == TRANSPORT_TYPE_CMD){
        flags = 2;
    }else if (packet_type == TRANSPORT_TYPE_ACL){
        flags = in;
    }else if(packet_type == TRANSPORT_TYPE_EVT){
        flags = 3;
    }else if(packet_type == TRANSPORT_TYPE_SCO){
        flags = 4;
    }

    struct timeval current_time;
    gettimeofday(&current_time, NULL);

    big_endian_write((uint8_t *)&original_len, len, 4);
    big_endian_write((uint8_t *)&included_len, len, 4);
    big_endian_write((uint8_t *)&flags, flags, 4);
    big_endian_write((uint8_t *)&drops, 0, 4);
    big_endian_write_64((uint8_t *)&timestamp, current_time.tv_usec);


    write(btsnoop_fd, &original_len, 4);
    write(btsnoop_fd, &included_len, 4);
    write(btsnoop_fd, &flags, 4);
    write(btsnoop_fd, &drops, 4);
    write(btsnoop_fd, (uint8_t *)&timestamp, 8);
    write(btsnoop_fd, data, len);

    return 0;
}
