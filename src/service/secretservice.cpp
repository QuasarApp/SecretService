//#
//# Copyright (C) 2024-2024 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "secretservice.h"
#include <QASecret.h>
#include <SecretDB.h>
#include <QASecret/keystorage.h>

SecretService::SecretService(int argc, char **argv):
    Patronum::Service<QCoreApplication>(argc, argv) {

    QASecret::init();
}

bool SecretService::onStart() {
    // call on server started

    QASecret::KeyStorage::initService(std::make_unique<QASecret::KeyStorage>(DBSecret::database()));

    return true;
}

void SecretService::onStop() {
    // call on server stoped
    QASecret::KeyStorage::deinitService();

}

void SecretService::handleReceiveData(const QHash<QString, Patronum::Feature> &data) {
    auto storage = QASecret::KeyStorage::instance();

    if (!storage) {
        sendResuylt(QuasarAppUtils::Locales::tr("Service is stoped. Please use the start command."));
        return;
    }

    bool fAdd = data.contains("add");
    bool fRemove = data.contains("remove");
    bool fGet = data.contains("get");

    int actionsCount = fAdd + fRemove + fGet;
    if (actionsCount > 1) {
        sendResuylt(QuasarAppUtils::Locales::tr("You are try to run multiple commands. please choose some of pleas choose one."));
        return;
    } else if (data.isEmpty()) {
        sendResuylt(QuasarAppUtils::Locales::tr("please choose one of available actions add/remove/get"));
        return;
    };

    if (fAdd) {
        const auto&& dataVal = data.value("-data").arg();
        if (dataVal.isEmpty()) {
            sendResuylt(QuasarAppUtils::Locales::tr("You forget a data. please use the next command add -data yourDataString"));
            return;
        }

        sendResuylt(storage->add(dataVal.toLatin1()));

    } else if (fRemove) {

        const auto&& hashVal = data.value("-hash").arg();
        const auto&& aliasVal = data.value("-alias").arg();

        if (hashVal.isEmpty() && aliasVal.isEmpty()) {
            sendResuylt(QuasarAppUtils::Locales::tr("You forget a hash key of alias of removable data. "
                                                    "Please use the next command remove -hash yourHash or "
                                                    "remove -alias yourAlias"));
            return;
        }

        if (hashVal.size()) {
            sendResuylt(storage->get(hashVal.toLatin1()));
        } else if (aliasVal.size()) {
            sendResuylt(storage->get(aliasVal));
        }

    } else if (fGet) {

        const auto&& hashVal = data.value("-hash").arg();
        const auto&& aliasVal = data.value("-alias").arg();

        if (hashVal.isEmpty() && aliasVal.isEmpty()) {
            sendResuylt(QuasarAppUtils::Locales::tr("You forget a hash key of alias of getting data. "
                                                    "Please use the next command get -hash yourHash or "
                                                    "get -alias yourAlias"));
            return;
        }

        if (hashVal.size()) {
            storage->remove(hashVal.toLatin1());
        } else if (aliasVal.size()) {
            storage->remove(aliasVal);
        }

    } else {
        handleReceiveData(data);
    }
}

bool SecretService::handleReceive(const Patronum::Feature &data) {

    if (data.cmd() == "ping") {
        sendResuylt("Pong");
    } else if (data.cmd() == "state") {
        auto storage = QASecret::KeyStorage::instance();

        if (storage) {
            sendResuylt("application status: Active");
        } else {
            sendResuylt("application status: Stoped");
        }
    }

    return true;
}

QSet<Patronum::Feature> SecretService::supportedFeatures() {
    QSet<Patronum::Feature> data;

    data << Patronum::Feature("ping", {}, QuasarAppUtils::Locales::tr("This is description of the ping command"));
    data << Patronum::Feature("state", {}, QuasarAppUtils::Locales::tr("Returns state"));
    data << Patronum::Feature("add",
                              {},
                              QuasarAppUtils::Locales::tr("Adds new value into seret storage, and return a hash key after adding."),
                              "QASecret add -data mysecretString -alias myCustomKey ");
    data << Patronum::Feature("remove",
                              {},
                              QuasarAppUtils::Locales::tr("Remove data from storage by hash key or alias."),
                              "QASecret remove -hash hashKey or QASecret remove -alias myCustomKey");
    data << Patronum::Feature("get",
                              {},
                              QuasarAppUtils::Locales::tr("return secret from database"),
                              "QASecret get  -hash hashKey or QASecret get -alias myCustomKey ");
    data << Patronum::Feature("-alias", {"aliasName"}, QuasarAppUtils::Locales::tr("Alias name"));
    data << Patronum::Feature("-data", {"data"}, QuasarAppUtils::Locales::tr("Data that will be saved"));
    data << Patronum::Feature("-hash", {"hash"}, QuasarAppUtils::Locales::tr("Hash kay of data"));

    return data;
}
