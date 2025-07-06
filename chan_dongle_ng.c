#include "asterisk/module.h"
#include "asterisk/logger.h"
#include "asterisk/config.h"
#include "asterisk/cli.h"
#include "asterisk/strings.h"
#include "asterisk/utils.h"
#include "chan_dongle_ng.h"

struct dongle_device_list g_device_list;

static int load_config(void) {
    struct ast_config *cfg;
    const char *cat = NULL;
    struct ast_variable *v;
    struct ast_flags flags = {0};

    AST_RWLIST_INIT(&g_device_list);

    cfg = ast_config_load("dongle_ng.conf", flags);
    if (!cfg) {
        ast_log(LOG_ERROR, "Unable to load dongle_ng.conf\n");
        return -1;
    }

    while ((cat = ast_category_browse(cfg, cat))) {
        if (!strcmp(cat, "general"))
            continue;

        dongle_device_t *dev = ast_calloc(1, sizeof(*dev));
        if (!dev) continue;
        ast_copy_string(dev->alias, cat, sizeof(dev->alias));

        for (v = ast_variable_browse(cfg, cat); v; v = v->next) {
            if (!strcmp(v->name, "imei"))
                ast_copy_string(dev->imei, v->value, sizeof(dev->imei));
            else if (!strcmp(v->name, "sim_number"))
                ast_copy_string(dev->sim_number, v->value, sizeof(dev->sim_number));
            else if (!strcmp(v->name, "dev_path"))
                ast_copy_string(dev->dev_path, v->value, sizeof(dev->dev_path));
        }

        AST_RWLIST_INSERT_TAIL(&g_device_list, dev, list);
    }

    ast_config_destroy(cfg);
    return 0;
}

static int load_module(void) {
    if (load_config())
        return AST_MODULE_LOAD_FAILURE;
    if (dongle_ng_cli_init())
        ast_log(LOG_WARNING, "Failed to register CLI commands\n");
    ast_log(LOG_NOTICE, "chan_dongle_ng module loaded.\n");
    return AST_MODULE_LOAD_SUCCESS;
}

static int unload_module(void) {
    dongle_device_t *dev;
    AST_RWLIST_WRLOCK(&g_device_list);
    while ((dev = AST_RWLIST_REMOVE_HEAD(&g_device_list, list))) {
        ast_free(dev);
    }
    AST_RWLIST_UNLOCK(&g_device_list);
    dongle_ng_cli_cleanup();
    ast_log(LOG_NOTICE, "chan_dongle_ng module unloaded.\n");
    return 0;
}

AST_MODULE_INFO_STANDARD_EXTENDED(
    .name = "chan_dongle_ng",
    .description = "New generation GSM/VoLTE channel driver",
    .load = load_module,
    .unload = unload_module,
);
