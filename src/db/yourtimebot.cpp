//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "yourtimebot.h"

#include <qTbot/messages/telegramupdate.h>

#include <QCoreApplication>
#include <locales.h>

YourTimeBot::YourTimeBot(const QSharedPointer<YourTimeDeliviry::IDataBase> &db) {
    _db = db;

    connect(this, &YourTimeBot::sigReceiveUpdate, this, &YourTimeBot::handleIncomeNewUpdate);
}

bool YourTimeBot::login(const QByteArray &token) {

    if (!_db)
        return false;

    setProcessed(_db->getProcessedIds());


    if(!QuasarAppUtils::Locales::init( {QLocale::English,
                                        QLocale::Russian,
                                        QLocale::Ukrainian,
                                        QLocale::Serbian}, {
                                                   ":/YourTime/languages/"
                                               }
                                       )){
        return false;
    }

    return qTbot::TelegramRestBot::login(token);
}

void YourTimeBot::handleIncomeNewUpdate(const QSharedPointer<qTbot::iUpdate> &update) {

    if (auto&& tupdate = update.dynamicCast<qTbot::TelegramUpdate>()) {
        if (tupdate->contains(tupdate->MessageUpdate)) {
            auto mesg = tupdate->message();
            if (mesg->text() == "/start") {

                sendMessage(mesg->chatId(), QuasarAppUtils::Locales::tr("This bot is still under development.",
                                                                        QLocale(mesg->languageCode())));
                QCoreApplication::processEvents();

                sendMessage(mesg->chatId(), QuasarAppUtils::Locales::tr("We are working very hard on our new delivery service to make it as easy as possible for you to be with us wherever you are.",
                                                                        QLocale(mesg->languageCode())));
                QCoreApplication::processEvents();


                sendMessage(mesg->chatId(), QuasarAppUtils::Locales::tr("Thank you for your wait.",
                                                                        QLocale(mesg->languageCode())));

            }
        }
    }

    markUpdateAsProcessed(update);
    _db->addProcessedId(update->updateId());
}
