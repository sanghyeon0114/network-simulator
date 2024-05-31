#include "message_service_installer.h"

MessageService *MessageServiceInstaller::install(Host *host) {
    MessageService* messageService = new MessageService(host, host->nextServicePort(), destAddress_, destPort_);
    ServiceInstaller::install(host, messageService);
    return messageService;
}