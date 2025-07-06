#ifndef _CHAN_DONGLE_NG_H_
#define _CHAN_DONGLE_NG_H_

typedef struct dongle_device {
    char imei[32];
    char imsi[32];
    char sim_number[32];
    char dev_path[64];
    char usb_id[32];
    char alias[32];
    int rssi;
    int fd;
    time_t last_response;
    int is_registered;
    struct ast_channel *owner;
    pthread_t reader_thread;
} dongle_device_t;

#endif
