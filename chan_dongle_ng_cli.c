#include "asterisk/cli.h"

static char *cli_show_command(struct ast_cli_entry *e, int cmd, struct ast_cli_args *a) {
    if (cmd == CLI_INIT) {
        e->command = "dongle_ng show";
        e->usage = "Usage: dongle_ng show\n       Shows active dongle_ng devices.";
        return NULL;
    } else if (cmd == CLI_GENERATE)
        return NULL;

    ast_cli(a->fd, "dongle_ng CLI not implemented yet.\n");
    return CLI_SUCCESS;
}

static struct ast_cli_entry cli_commands[] = {
    AST_CLI_DEFINE(cli_show_command, "Show dongle_ng devices"),
};

static int load_cli(void) {
    return ast_cli_register_multiple(cli_commands, ARRAY_LEN(cli_commands));
}

static int unload_cli(void) {
    return ast_cli_unregister_multiple(cli_commands, ARRAY_LEN(cli_commands));
}
