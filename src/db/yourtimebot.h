//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef YOURTIMEBOT_H
#define YOURTIMEBOT_H

#include "YourTimeDeliviry/idatabase.h"
#include <qTbot/telegramrestbot.h>

/**
 * @brief The YourTimeBot class
 */
class YourTimeBot: public qTbot::TelegramRestBot
{
    Q_OBJECT
public:
    YourTimeBot(const QSharedPointer<YourTimeDeliviry::IDataBase>& db);
    bool login(const QByteArray &token) override;
    // IBot interface
protected:
    void handleIncomeNewUpdate(const QSharedPointer<qTbot::iUpdate> &update) override;

private:
    QSharedPointer<YourTimeDeliviry::IDataBase> _db;

};

#endif // YOURTIMEBOT_H
