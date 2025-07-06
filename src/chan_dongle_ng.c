#include "asterisk.h"
#include "asterisk/module.h"
#include "chan_dongle_ng.h"

int load_module(void)
{
    ast_log(LOG_NOTICE, "chan_dongle_ng loaded\n");
    return AST_MODULE_LOAD_SUCCESS;
}

int unload_module(void)
{
    ast_log(LOG_NOTICE, "chan_dongle_ng unloaded\n");
    return 0;
}

AST_MODULE_INFO_STANDARD(ASTERISK_GPL_KEY, "Chan Dongle NG stub module");

/* Required when building outside of the Asterisk tree */
struct ast_module_info *AST_MODULE_SELF_SYM = &__mod_info;
