//#
//# Copyright (C) 2023-2024 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "botdatabase.h"
#include "image.h"
#include "processedid.h"
#include <QCryptographicHash>
#include <dbobjectsrequest.h>
#include <menuitem.h>
#include <menuitem_v0.h>
#include <order.h>
#include <role.h>
#include <sqldb.h>
#include <user.h>

namespace  QASecret {

BotDataBase::BotDataBase() {

    addDBPatch({
        0,
        1,
        [](const QH::iObjectProvider* database) -> bool {
            return database->doSql(":/src/sql/YourTimeDB_1.sql");
        }
    });

    addDBPatch({
        1,
        2,
        [](const QH::iObjectProvider* database) -> bool {
            return database->doSql(":/src/sql/YourTimeDB_2.sql");
        }
    });

    addDBPatch({
        2,
        3,
        [this](QH::iObjectProvider* database) -> bool {
            if (!database->doSql(":/src/sql/YourTimeDB_3.sql")) {
                return false;
            }
            QH::PKG::DBObjectsRequest<MenuItem_v0>
                request("MenuV0");
            auto&& oldMenu = database->getObject(request);

            for (const auto &oldMenuItem: oldMenu->data()) {
                auto&& menuItem = getMenuById(oldMenuItem->getId(), true);
                menuItem->setCategory(oldMenuItem->category());
                menuItem->setName(oldMenuItem->getName());
                menuItem->setDescription(oldMenuItem->getDescription());
                menuItem->setPrice(oldMenuItem->getPrice());
                menuItem->setTranslations(oldMenuItem->getTranslations());

                const auto& image = oldMenuItem->getImage();
                if (image.size()) {
                    auto&& imageId = QCryptographicHash::hash(image,
                                             QCryptographicHash::Sha256).
                                     toBase64(QByteArray::Base64UrlEncoding);

                    auto&& imageObj = getImageById(imageId, true);
                    imageObj->setImage(image);

                    saveImage(imageObj);

                    menuItem->setImage(imageId);
                } else if (oldMenuItem->getImageSource().size()) {
                    menuItem->setImage(oldMenuItem->getImageSource());
                }

                saveMenuItem(menuItem);

            }

            return database->doQuery("DROP TABLE MenuV0");
        }
    });
}

QSet<unsigned long long> BotDataBase::getProcessedIds() {
    QSet<unsigned long long> result;
    QH::PKG::DBObjectsRequest<ProcessedId>
        request("ProcessedIds");

    auto&& responce = db()->getObject(request);
    if (!responce)
        return result;

    auto&& resp = responce->data();

    for (const auto& val: resp) {
        result.insert(val->getId());
    }

    return result;
}

void BotDataBase::addProcessedId(unsigned long long id) {
    auto&& idObj = QSharedPointer<ProcessedId>::create();
    idObj->setId(id);

    db()->insertObject(idObj);
}

void BotDataBase::removeProcessedId(unsigned long long id) {
    auto&& idObj = QSharedPointer<ProcessedId>::create();
    idObj->setId(id);

    db()->deleteObject(idObj);

}

void BotDataBase::setProcessedIds(const QSet<unsigned long long> &ids) {
    auto request = QSharedPointer<QH::PKG::DBObjectsRequest<ProcessedId>>::create(
        "ProcessedIds");

    db()->deleteObject(request);

    for (const auto& id : ids) {
        addProcessedId(id);
    }
}

QSharedPointer<iUser> BotDataBase::getUserById(unsigned long long id, bool ifNotExistsCreate) {
    return getById<User>(id, &User::setId, ifNotExistsCreate);
}

QList<QSharedPointer<iUser>> BotDataBase::getAllUsers(iRole::RoleName roleName) {
    QString condition;
    if (roleName != iRole::All) {
        condition = QString("role = %0").arg(roleName);
        condition = QString("id IN ( SELECT userId FROM Roles WHERE %0 )").arg(condition);
    }

    auto&& data = getAll<User>("Users", condition);
    return {data.begin(), data.end()};
}

void BotDataBase::saveUser(const QSharedPointer<iUser>& user) {
    saveObj(user.dynamicCast<User>());
}

void BotDataBase::removeUser(unsigned long long id) {
    deleteById<User>(id, &User::setId);
}

QSharedPointer<iRole> BotDataBase::getRoleByUserId(unsigned long long userId, bool ifNotExistsCreate) {
    return getById<Role>(userId, &Role::setUserId, ifNotExistsCreate);
}

void BotDataBase::saveRole(const QSharedPointer<iRole>& role) {
    saveObj(role.dynamicCast<Role>());
}

void BotDataBase::removeRole(unsigned long long userId) {
    deleteById<Role>(userId, &Role::setUserId);
}

QSharedPointer<iMenuItem> BotDataBase::getMenuById(int id, bool ifNotExistsCreate) {
    return getById<MenuItem>(id, &MenuItem::setId, ifNotExistsCreate);
}

QList<QSharedPointer<iMenuItem>> BotDataBase::getAllMenuItems() {
    auto&& data = getAll<MenuItem>("Menu");
    return {data.begin(), data.end()};
}

void BotDataBase::saveMenuItem(const QSharedPointer<iMenuItem>& menuItem) {
    saveObj(menuItem.dynamicCast<MenuItem>());
}

unsigned int BotDataBase::insertMenuItem(const QSharedPointer<iMenuItem> &menuItem) {
    auto&& resultId = QSharedPointer<unsigned int>::create();
    insertObj(menuItem.dynamicCast<MenuItem>(), resultId.toWeakRef());

    return *resultId;
}

void BotDataBase::removeMenuItem(int id) {
    deleteById<MenuItem>(id, &MenuItem::setId);
}

void BotDataBase::clearMenuTable() const {
    db()->doQuery("DELETE FROM Menu", {}, true);
}

QSharedPointer<iMenuItem> BotDataBase::makeMenuItem() {
    if (auto&& menuItem = QSharedPointer<MenuItem>::create()) {
        menuItem->setId(insertMenuItem(menuItem));
        return std::move(menuItem);
    }

    return nullptr;
}

QSharedPointer<iOrder> BotDataBase::getOrderById(int id, bool ifNotExistsCreate) {
    return getById<Order>(id, &Order::setId, ifNotExistsCreate);
}

QList<QSharedPointer<iOrder>> BotDataBase::getAllOrders(iOrder::State state) {

    QString condition;
    if (state != iOrder::All) {
        condition = QString("state = %0").arg(state);
    }

    auto&& data = getAll<Order>("Orders", condition);
    return {data.begin(), data.end()};
}

void BotDataBase::saveOrder(const QSharedPointer<iOrder>& order) {
    saveObj(order.dynamicCast<Order>());
}

unsigned int BotDataBase::insertOrder(const QSharedPointer<iOrder> &order) {
    auto&& resultId = QSharedPointer<unsigned int>::create();
    insertObj(order.dynamicCast<Order>(), resultId);

    return *resultId;
}

QSharedPointer<iOrder> BotDataBase::makeOrder() {
    if (auto&& newOrder = QSharedPointer<Order>::create()) {
        newOrder->setId(insertOrder(newOrder));
        return std::move(newOrder);
    }

    return nullptr;
}

void BotDataBase::removeOrder(int id) {
    deleteById<Order>(id, &Order::setId);
}

QList<QSharedPointer<iImage> > BotDataBase::getAllImages() {
    auto&& data = getAll<Image>("Images", "");
    return {data.begin(), data.end()};
}

QSharedPointer<iImage> BotDataBase::getImageById(const QString &id, bool ifNotExistsCreate) {
    return getById<Image>(id, &Image::setId, ifNotExistsCreate);
}

void BotDataBase::saveImage(const QSharedPointer<iImage> &image) {
    saveObj(image.dynamicCast<Image>());
}

void BotDataBase::removeImage(const QString &id) {
    deleteById<Image>(id, &Image::setId);
}


}
