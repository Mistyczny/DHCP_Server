#include "DhcpServer.h"
#include "DhcpUtils.h"

int main() {
    /* Initializing server object with it's components */
    DhcpServer server;
    /* Loading settings from file, if failure to find file, loading default */
    server.loadServerSettings();

    /* Starting up all tasks which are used by server */
    if(server.startTasks()) {
        /* Start boost asio loop */
        server.run();
    }

    return 0;
}