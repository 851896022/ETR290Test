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
#include <QDebug>
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

    //=========================
    int byte_read;//读取到的字节数
    int fd_ts;//文件指针
    int sc;//transport_scrambling_control    : 2; //传输加扰控制
    int sl;
    int pdl;
    int i;
    int b;
    unsigned short pid;
    int sync_error;
    unsigned long long sync_count = 0;
    unsigned long long sync_error_count = 0;
    unsigned long long sync_loss_count = 0;
    int tei; //transport_error_indicator : 1; //传输误码指示符
    int table_id;
    int pmt_start;
    unsigned long long last_pat = 0;
    unsigned long long last_nit = 0;
    unsigned long long last_sdt = 0;
    unsigned long long last_eit = 0;
    unsigned long long last_tdt = 0;
    unsigned long long last_tot = 0;
    unsigned long long last_bat = 0;
    unsigned long long last_rst = 0;
    unsigned long long last_cat = 0;
    unsigned long long last_pts[MAX_PID];
    int progindex = 0;
    int streams = 0;
    unsigned int adaptation_field; //: 2; //自适应控制 01仅含有效负载，10仅含调整字段，11含有调整字段和有效负载。为00解码器不进行处理
    unsigned char packet[TS_PACKET_SIZE];//一个TS包
    unsigned char pid_cc_table[MAX_PID];
    unsigned char repeated_cc_table[MAX_PID];
    unsigned char pid_cc_status[MAX_PID];
    unsigned int programs[MAX_PID];
    unsigned long long streamtypes[MAX_PID];
    unsigned long long streampids[MAX_PID];
    unsigned int total_pids[MAX_PID];
    int pid_count = 0;
    int ispmt;
    unsigned int valid_stream[MAX_PID];
    unsigned long long pcr_pids[MAX_PID];
    unsigned long long cc_error_count = 0;
    unsigned long long position = 1;
    unsigned long long last_pcr[MAX_PID];
    unsigned long long last_pmt[MAX_PID];
    float pcr_jitter;
    float pcr_delta;
    unsigned int pcr_ext = 0;
    unsigned long long int pcr_base = 0;
    unsigned long long int pid_pcr_table[MAX_PID];
    unsigned long long int pid_pcr_index_table[MAX_PID];
    unsigned long long int new_pcr = 0;
    unsigned long long int new_pcr_index = 0;
    unsigned long long bitrate;
    int pcrbitrate = 0;

    float value;
    FILE  *pcr_jitter_values;
    FILE  * pcr_delta_values;
    unsigned long long int pcr_count = 0;
    FILE  * pat_delta_values;
    unsigned long long int pat_count = 0;
    FILE  * pmt_delta_values;
    unsigned long long int pmt_count = 0;
    FILE  * sdt_delta_values;
    unsigned long long int sdt_count = 0;
    FILE  * nit_delta_values;
    unsigned long long int nit_count = 0;
    FILE  * eit_delta_values;
    unsigned long long int eit_count = 0;
    FILE  * tdt_delta_values;
    unsigned long long int tdt_count = 0;
    FILE  * tot_delta_values;
    unsigned long long int tot_count = 0;
    FILE  * bat_delta_values;
    unsigned long long int bat_count = 0;
    FILE  * rst_delta_values;
    unsigned long long int rst_count = 0;
    FILE  * cat_delta_values;
    unsigned long long int cat_count = 0;
    int reports = 0;

    unsigned char timestamp[5];
    unsigned long long atime = 0;
    //=========================
    QStringList errorList;
    QString tmp;
signals:
    void readyError(QString);
public slots:

    void make_crc_table(void);

    uint32_t crc32_block(uint32_t crc, byte *pData, int blk_len);

    int64_t ts_timestamp_diff(int64_t t1, int64_t t0, int64_t ovf);
    unsigned long long parse_timestamp(unsigned char *buf);
    uint32_t check_crc(unsigned char * packet);

    float get_pos( unsigned long long position, unsigned long long value, unsigned long long bitrate);

    int test(unsigned char *);
    short myntohs(short s);
    void logErrorData(QString);


};
#endif // TEST290_H
