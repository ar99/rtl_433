#ifndef INCLUDE_RTL_433_H_
#define INCLUDE_RTL_433_H_

#include <errno.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#include "rtl_433_devices.h"
#include "decoder.h"

#ifdef _WIN32
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#ifdef _MSC_VER
#include "getopt/getopt.h"
#define F_OK 0
#endif
#endif
#ifndef _MSC_VER
#include <unistd.h>
#include <getopt.h>
#endif

#define DEFAULT_SAMPLE_RATE     250000
#define DEFAULT_FREQUENCY       433920000
#define DEFAULT_HOP_TIME        (60*10)
#define DEFAULT_ASYNC_BUF_NUMBER    0 // Force use of default value (was : 32)
#define DEFAULT_BUF_LENGTH      (16 * 16384)

/*
 * Theoretical high level at I/Q saturation is 128x128 = 16384 (above is ripple)
 * 0 = automatic adaptive level limit, else fixed level limit
 * 8000 = previous fixed default
 */
#define DEFAULT_LEVEL_LIMIT     0

#define MINIMAL_BUF_LENGTH      512
#define MAXIMAL_BUF_LENGTH      (256 * 16384)
#define MAX_PROTOCOLS           112
#define SIGNAL_GRABBER_BUFFER   (12 * DEFAULT_BUF_LENGTH)

struct protocol_state {
    int (*callback)(bitbuffer_t *bitbuffer);

    char *name;
    unsigned int modulation;
    char **fields;
    unsigned int disabled;

    /* pwm limits (provided by driver in µs and converted to samples) */
    float short_limit;
    float long_limit;
    float reset_limit;
    float gap_limit;
    float sync_width;
    float tolerance;
    unsigned demod_arg;
};

#endif /* INCLUDE_RTL_433_H_ */
