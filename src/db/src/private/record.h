//#
//# Copyright (C) 2024-2024 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef RECORD_H
#define RECORD_H

#include "dbobject.h"
#include <SecretDB/irecord.h>

#include <QByteArray>
#include <QString>

namespace DBSecret {

/**
 * @brief The Record class
 */
class Record : public QH::PKG::DBObject, public iRecord
{
public:
    Record();

    // iRecord interface
    const QString &getAlias() const override;
    void setAlias(const QString &alias) override;
    const QByteArray &getHash() const override;
    void setHash(const QByteArray &source) override;
    const QByteArray &getData() const override;
    const QByteArray & setData(const QByteArray &newData) override;

    // DBObject interface
    QH::PKG::DBObject* createDBObject() const override;
    bool fromSqlRecord(const QSqlRecord& q) override;
    QString table() const override;
    QH::PKG::DBVariantMap variantMap() const override;

    QString primaryKey() const override;
    QVariant primaryValue() const override;

private:
    QString _alias;
    QByteArray _hash;
    QByteArray _data;
};
}
#endif // RECORD_H
