#include "btsnoop.h"

int main(){
    btsnoop_open("./hci_btsnoop.log");

    uint8_t hci_reset[] = {0x01, 0x03, 0x0c, 0x00};

    btsnoop_write_packet(TRANSPORT_TYPE_CMD, 0, sizeof(hci_reset), (uint8_t *)hci_reset);
    sleep(1);

    btsnoop_close();
    return 0;
}