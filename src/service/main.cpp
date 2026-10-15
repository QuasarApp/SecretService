//#
//# Copyright (C) 2024-2024 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include <QASecret.h>
#include <QASecret/keystorage.h>
#include <QTimer>
#include <QCoreApplication>
#include <iostream>
#include "params.h"

bool processRequest() {
    auto storage = QASecret::KeyStorage::instance();

    if (!storage) {
        QuasarAppUtils::Params::log(QObject::tr("Service is not initialized."));
        return false;
    }

    bool fAdd = QuasarAppUtils::Params::isEndable("add");
    bool fRemove = QuasarAppUtils::Params::isEndable("remove");
    bool fGet = QuasarAppUtils::Params::isEndable("get");

    int actionsCount = fAdd + fRemove + fGet;
    if (actionsCount > 1) {
        QuasarAppUtils::Params::log(QObject::tr("You are try to run multiple commands. please choose some of pleas choose one."),
                                    QuasarAppUtils::Error);
        return false;
    } else if (!actionsCount) {
        QuasarAppUtils::Params::log(QObject::tr("please choose one of available actions add/remove/get"),
                                    QuasarAppUtils::Error);
        return false;
    };

    if (fAdd) {
        const auto&& dataVal = QuasarAppUtils::Params::getArg("data");
        const auto&& aliasVal = QuasarAppUtils::Params::getArg("alias");

        if (dataVal.isEmpty()) {
            QuasarAppUtils::Params::log(QObject::tr("You forget a data. please use the next command add -data yourDataString"),
                                        QuasarAppUtils::Error);
            return false;
        }

        std::cout << storage->add(dataVal.toLatin1(), aliasVal).toStdString() << std::endl;

    } else if ( fGet) {

        const auto&& hashVal = QuasarAppUtils::Params::getArg("hash");
        const auto&& aliasVal = QuasarAppUtils::Params::getArg("alias");

        if (hashVal.isEmpty() && aliasVal.isEmpty()) {
            QuasarAppUtils::Params::log(QObject::tr("You forget a hash key of alias of getting  data. "
                                                    "Please use the next command get -hash yourHash or "
                                                    "get -alias yourAlias"), QuasarAppUtils::Error);
            return false;
        }

        if (hashVal.size()) {
            std::cout << storage->get(hashVal.toLatin1()).toStdString() << std::endl;

        } else if (aliasVal.size()) {

            std::cout << storage->get(aliasVal).toStdString() << std::endl;

        }

    } else if (fRemove) {

        const auto&& hashVal = QuasarAppUtils::Params::getArg("hash");
        const auto&& aliasVal = QuasarAppUtils::Params::getArg("alias");

        if (hashVal.isEmpty() && aliasVal.isEmpty()) {
            QuasarAppUtils::Params::log(QObject::tr("You forget a hash key of alias of removable data. "
                                                    "Please use the next command remove -hash yourHash or "
                                                    "remove -alias yourAlias"), QuasarAppUtils::Error);
            return false;
        }

        if (hashVal.size()) {
            storage->remove(hashVal.toLatin1());
        } else if (aliasVal.size()) {
            storage->remove(aliasVal);
        }

    }

    return true;
}


int main(int argc, char *argv[]) {

    QCoreApplication::setApplicationName("QASecret");
    QCoreApplication::setOrganizationName("QuasarApp");

    QuasarAppUtils::Params::parseParams(argc, argv);
    QCoreApplication app(argc, argv);
    QASecret::init();

    QTimer::singleShot(0, nullptr, []() {

        if (!processRequest()) {
            QCoreApplication::exit(1);
            return;
        }

        QCoreApplication::quit();
    });


    return app.exec();
}
