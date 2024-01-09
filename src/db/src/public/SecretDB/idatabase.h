//#
//# Copyright (C) 2024-2024 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef IDATABASE_H
#define IDATABASE_H

#include <QSet>
#include <QSharedPointer>
#include "global.h"
#include "irecord.h"


namespace  QASecret {
/**
 * @brief The IDataBase class Main database
 */
class SECRETDB_EXPORT IDataBase
{
public:
    IDataBase();

    /**
     * @brief Get a user by their ID.
     * @param id The ID of the user to retrieve.
     * @param ifNotExistsCreate - this option will create a new object if object with @a id is not existst into database. But object wil not save into database.
     * @return A QSharedPointer to the user object if found, nullptr otherwise.
     */
    virtual QSharedPointer<iUser> getRecordByAlias(const QString& alias, bool ifNotExistsCreate = false) = 0;

    /**
     * @brief Get a list of all users in the database.
     * @return A list of QSharedPointer<iUser> objects.
     */
    virtual QList<QSharedPointer<iUser>> getAllUsers(iRole::RoleName roleName = iRole::All) = 0;

    /**
     * @brief Update old, or insert if not exists a new user to the database.
     * @param user The user object to add.
     */
    virtual void saveUser(const QSharedPointer<iUser>& user) = 0;

    /**
     * @brief Remove a user from the database by their ID.
     * @param id The ID of the user to remove.
     */
    virtual void removeUser(unsigned long long id) = 0;

    /**
     * @brief Get a user's role by their ID.
     * @param userId The ID of the user.
     * @param ifNotExistsCreate - this option will create a new object if object with @a id is not existst into database. But object wil not save into database.
     * @return A QSharedPointer to the role object if found, nullptr otherwise.
     */
    virtual QSharedPointer<iRole> getRoleByUserId(unsigned long long userId, bool ifNotExistsCreate = false) = 0;

    /**
     * @brief Update old, or insert if not exists a new role to the database.
     * @param role The role object to add.
     */
    virtual void saveRole(const QSharedPointer<iRole>& role) = 0;

    /**
     * @brief Remove a role from the database by the user's ID.
     * @param userId The ID of the user whose role should be removed.
     */
    virtual void removeRole(unsigned long long userId) = 0;

    /**
     * @brief Get a menu item by its ID.
     * @param id The ID of the menu item to retrieve.
     * @param ifNotExistsCreate - this option will create a new object if object with @a id is not existst into database. But object wil not save into database.
     * @return A QSharedPointer to the menu item object if found, nullptr otherwise.
     */
    virtual QSharedPointer<iMenuItem> getMenuById(int id, bool ifNotExistsCreate = false) = 0;

    /**
     * @brief Get a list of all menu items in the database.
     * @return A list of QSharedPointer<iMenu> objects.
     */
    virtual QList<QSharedPointer<iMenuItem>> getAllMenuItems() = 0;

    /**
     * @brief Update old, or insert if not exists  a new menu item to the database.
     * @param menuItem The menu item object to add.
     */
    virtual void saveMenuItem(const QSharedPointer<iMenuItem>& menuItem) = 0;

    /**
     * @brief insertMenuItem This method create a new record of the menuItem and return them id
     * @param menuItem This is data to save.
     * @return id of the new record of the @a menuItem
     */
    virtual unsigned int insertMenuItem(const QSharedPointer<iMenuItem> &menuItem) = 0;

    /**
     * @brief Remove a menu item from the database by its ID.
     * @param id The ID of the menu item to remove.
     */
    virtual void removeMenuItem(int id) = 0;

    /**
     * @brief clearMenuTable This method remove all data from the menu table.
     */
    virtual void clearMenuTable() const = 0;

    /**
     * @brief makeMenuItem This method create a new record of the menu item in database.
     * @return new record of the menu item.
     */
    virtual QSharedPointer<iMenuItem> makeMenuItem() = 0;

    /**
     * @brief Get an order by its ID.
     * @param id The ID of the order to retrieve.\
     * @param ifNotExistsCreate - this option will create a new object if object with @a id is not existst into database. But object wil not save into database.
     * @return A QSharedPointer to the order object if found, nullptr otherwise.
     */
    virtual QSharedPointer<iOrder> getOrderById(int id, bool ifNotExistsCreate = false) = 0;

    /**
     * @brief Get a list of all orders in the database.
     * @param state filter order by status. If you want to get all orders with all statuses use the iOrder::State:All
     * @return A list of QSharedPointer<iOrder> objects.
     */
    virtual QList<QSharedPointer<iOrder>> getAllOrders(iOrder::State state = iOrder::State::All) = 0;

    /**
     * @brief Update old, or insert if not exists a new order to the database.
     * @param order The order object to add.
     */
    virtual void saveOrder(const QSharedPointer<iOrder>& order) = 0;

    /**
     * @brief insertOrder This method create a new record of the order and return them id
     * @param order This is data to save.
     * @return id of the new record of the @a order
     */
    virtual unsigned int insertOrder(const QSharedPointer<iOrder> &order) = 0;

    /**
     * @brief makeOrder This method create a new record of the order into database.
     * @return new record of the order.
     */
    virtual QSharedPointer<iOrder> makeOrder() = 0;


    /**
     * @brief Remove an order from the database by its ID.
     * @param id The ID of the order to remove.
     */
    virtual void removeOrder(int id) = 0;


    /**
     * @brief Get a list of all images in the database.
     * @return A list of QSharedPointer<iImage> objects.
     */
    virtual QList<QSharedPointer<iImage>> getAllImages() = 0;

    /**
     * @brief Update old, or insert if not exists a new image to the database.
     * @param image The order object to add.
     */
    virtual void saveImage(const QSharedPointer<iImage>& image) = 0;

    /**
     * @brief Remove an image from the database by its ID.
     * @param id The ID of the image to remove.
     */
    virtual void removeImage(const QString& id) = 0;

    /**
     * @brief Get an image by its ID.
     * @param id The ID of the image to retrieve.\
     * @param ifNotExistsCreate - this option will create a new object if object with @a id is not existst into database. But object wil not save into database.
     * @return A QSharedPointer to the image object if found, nullptr otherwise.
     */
    virtual QSharedPointer<iImage> getImageById(const QString &id, bool ifNotExistsCreate = false) = 0;



};
}


#endif // IDATABASE_H
