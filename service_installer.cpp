#include "service_installer.h"

void ServiceInstaller::install(Host *host, Service *service) {
    host->services_.push_back(service);
}