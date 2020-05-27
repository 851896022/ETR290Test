#ifndef TEST290_H
#define TEST290_H

#include <QObject>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <getopt.h>
#include <iconv.h>
#include <Winsock.h>

#define CRC32_POLY 0x04c11db7L
#define TS_PACKET_SIZE 188
#define MAX_PID 8191
#define READ_ONCE   7
#define byte uint8_t
#define SYSTEM_CLOCK_FREQUENCY 27000000
class Test290 : public QObject
{
    Q_OBJECT
public:
    explicit Test290(QObject *parent = nullptr);
    uint32_t crc_table[256];
signals:

public slots:

    void make_crc_table(void);

    uint32_t crc32_block(uint32_t crc, byte *pData, int blk_len);

    int64_t ts_timestamp_diff(int64_t t1, int64_t t0, int64_t ovf);
    unsigned long long parse_timestamp(unsigned char *buf);
    uint32_t check_crc(unsigned char * packet);

    float get_pos( unsigned long long position, unsigned long long value, unsigned long long bitrate);

    int test(int argc, char *argv[]);
    short myntohs(short s);


};
#endif // TEST290_H
