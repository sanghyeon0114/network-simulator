#include "bulk_send_service_installer.h"

BulkSendService *BulkSendServiceInstaller::install(Host *host, Address destination, short destPort, double delay, double startTime, double stopTime) {
    BulkSendService *bulkSendService = new BulkSendService(host, destination, host->nextServicePort(), delay, startTime, stopTime);
    ServiceInstaller::install(host, bulkSendService);

    for(double time = startTime; time <= stopTime; time+=delay) {
        Simulator::schedule(time, [bulkSendService, host, destination, destPort]() {
            bulkSendService->send(host, destination, destPort);
        });
    }
    
    return bulkSendService;
}