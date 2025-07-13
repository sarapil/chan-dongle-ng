#include "asterisk.h"
#include "asterisk/cli.h"
#include "asterisk/logger.h"
#include "chan_dongle_ng.h"

static char *cli_show_command(struct ast_cli_entry *e, int cmd, struct ast_cli_args *a) {
    if (cmd == CLI_INIT) {
        e->command = "dongle_ng show";
        e->usage = "Usage: dongle_ng show\n       Shows active dongle_ng devices.";
        return NULL;
    } else if (cmd == CLI_GENERATE)
        return NULL;

    dongle_device_t *dev;
    AST_RWLIST_RDLOCK(&g_device_list);
    AST_RWLIST_TRAVERSE(&g_device_list, dev, list) {
        ast_cli(a->fd, "%-15s IMEI:%s SIM:%s\n", dev->alias, dev->imei, dev->sim_number);
    }
    AST_RWLIST_UNLOCK(&g_device_list);
    return CLI_SUCCESS;
}

static char *cli_reset_command(struct ast_cli_entry *e, int cmd, struct ast_cli_args *a) {
    if (cmd == CLI_INIT) {
        e->command = "dongle_ng reset";
        e->usage = "Usage: dongle_ng reset <alias>\n       Reset a dongle device";
        return NULL;
    } else if (cmd == CLI_GENERATE)
        return NULL;
    if (a->argc != 3) {
        return CLI_SHOWUSAGE;
    }
    const char *alias = a->argv[2];
    ast_log(LOG_NOTICE, "Requested reset for %s\n", alias);
    return CLI_SUCCESS;
}

static struct ast_cli_entry cli_commands[] = {
    AST_CLI_DEFINE(cli_show_command, "Show dongle_ng devices"),
    AST_CLI_DEFINE(cli_reset_command, "Reset dongle device"),
};

int dongle_ng_cli_init(void) {
    return ast_cli_register_multiple(cli_commands, ARRAY_LEN(cli_commands));
}

void dongle_ng_cli_cleanup(void) {
    ast_cli_unregister_multiple(cli_commands, ARRAY_LEN(cli_commands));
}
