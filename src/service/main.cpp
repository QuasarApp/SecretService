//#
//# Copyright (C) 2024-2024 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include <secretservice.h>

int main(int argc, char *argv[]) {

    QCoreApplication::setApplicationName("QASecret");
    QCoreApplication::setOrganizationName("QuasarApp");

    SecretService service(argc, argv);

    return service.exec();
}
