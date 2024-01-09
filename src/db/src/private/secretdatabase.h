//#
//# Copyright (C) 2023-2024 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include <YourTimeDeliviry/idatabase.h>

#include <database.h>

#ifndef BOTDATABASE_H
#define BOTDATABASE_H

namespace  QASecret {

class BotDataBase: public IDataBase, public QH::DataBase
{
public:
    BotDataBase();

    // IDataBase interface
public:
    QSet<unsigned long long> getProcessedIds() override;
    void addProcessedId(unsigned long long id) override;
    void removeProcessedId(unsigned long long id) override;
    void setProcessedIds(const QSet<unsigned long long> &ids) override;

    QSharedPointer<iUser> getUserById(unsigned long long id, bool ifNotExistsCreate = false) override;
    QList<QSharedPointer<iUser> > getAllUsers(iRole::RoleName roleName = iRole::All) override;
    void saveUser(const QSharedPointer<iUser> &user) override;
    void removeUser(unsigned long long id) override;
    QSharedPointer<iRole> getRoleByUserId(unsigned long long userId, bool ifNotExistsCreate = false) override;

    void saveRole(const QSharedPointer<iRole> &role) override;
    void removeRole(unsigned long long userId) override;

    QSharedPointer<iMenuItem> getMenuById(int id, bool ifNotExistsCreate = false) override;
    QList<QSharedPointer<iMenuItem> > getAllMenuItems() override;
    void saveMenuItem(const QSharedPointer<iMenuItem> &menuItem) override;
    unsigned int insertMenuItem(const QSharedPointer<iMenuItem> &menuItem) override;

    void removeMenuItem(int id) override;
    void clearMenuTable() const override;
    QSharedPointer<iMenuItem> makeMenuItem() override;

    QSharedPointer<iOrder> getOrderById(int id, bool ifNotExistsCreate = false) override;
    QList<QSharedPointer<iOrder> > getAllOrders(iOrder::State state = iOrder::State::All) override;
    void saveOrder(const QSharedPointer<iOrder> &order) override;
    unsigned int insertOrder(const QSharedPointer<iOrder> &order) override;
    QSharedPointer<iOrder> makeOrder() override;

    void removeOrder(int id) override;

    QList<QSharedPointer<iImage> > getAllImages() override;
    QSharedPointer<iImage> getImageById(const QString &id, bool ifNotExistsCreate = false) override;

    void saveImage(const QSharedPointer<iImage> &image) override;
    void removeImage(const QString &id) override;


};
}
#endif // BOTDATABASE_H
