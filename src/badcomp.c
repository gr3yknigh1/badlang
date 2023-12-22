/*
 * BADCOMP
 *
 * */
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "badlang/bits.h"
#include "badlang/logs.h"
#include "badlang/rc.h"

enum opt {
    OPT_NONE = MKFLAG(0),
    OPT_HELP = MKFLAG(1),
};

static const struct option LONG_OPTS[] = {
    {"help", false, NULL, OPT_HELP},
};

static const char *SHORT_OPTS = "h";

int
main(int argc, char *const *argv) {
    int opt_value = 0, opt_index = 0;
    enum opt optmask = OPT_NONE;

    while ((opt_value = getopt_long(argc, argv, SHORT_OPTS, LONG_OPTS,
                                    &opt_index)) != RC_END) {
        switch (opt_value) {
        case OPT_HELP:
            ADDFLAG(optmask, OPT_HELP);
            break;
        default:
            break;
        }
    }

    return RC_OK;
}
