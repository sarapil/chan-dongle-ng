#include "asterisk/module.h"
#include "asterisk/logger.h"

static int load_module(void) {
    ast_log(LOG_NOTICE, "chan_dongle_ng module loaded.\n");
    return AST_MODULE_LOAD_SUCCESS;
}

static int unload_module(void) {
    ast_log(LOG_NOTICE, "chan_dongle_ng module unloaded.\n");
    return 0;
}

AST_MODULE_INFO_STANDARD_EXTENDED(
    .name = "chan_dongle_ng",
    .description = "New generation GSM/VoLTE channel driver",
    .load = load_module,
    .unload = unload_module,
);
