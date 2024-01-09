//#
//# Copyright (C) 2023-2024 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef IMAGE_H
#define IMAGE_H

#include "dbobject.h"
#include <SecretDB/iimage.h>

#include <QByteArray>
#include <QString>

namespace  QASecret {

/**
 * @brief The Image class
 */
class Image : public QH::PKG::DBObject, public iImage
{
public:
    Image();

    // iImage interface

    const QString &getId() const override;
    void setId(const QString &id) override;
    const QByteArray &getImage() const override;
    void setImage(const QByteArray &source) override;

    // DBObject interface
    QH::PKG::DBObject* createDBObject() const override;
    bool fromSqlRecord(const QSqlRecord& q) override;
    QString table() const override;
    QH::PKG::DBVariantMap variantMap() const override;

    QString primaryKey() const override;
    QVariant primaryValue() const override;

private:
    QString _id;
    QByteArray _image;
};
}
#endif // IMAGE_H
