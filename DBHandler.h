#ifndef DBHANDLER_H
#define DBHANDLER_H

#include "GlobalDefinitions.h"

class AbstractDB;
class Table;

class DBHandler : public QObject
{
    Q_OBJECT
public:
    DBHandler();
    ~DBHandler() {freeResources();}

    AccessMode getAccessMod();
    int getTablesCount();
    QString getTableName(uint tableID);
    QRect getTableGeometry(uint tableID, DisplayMode mode);
    QAbstractItemModel *getTableFieldsModel(uint tableID);
    QAbstractItemModel *getTableObjectsModel(uint tableID);

    void setAccessMod(AccessMode am);
    void setTableName(uint tableID, const QString &tableName);
    void setTableX(uint tableID, int x, DisplayMode mode);
    void setTableY(uint tableID, int y, DisplayMode mode);
    void setTableWidth(uint tableID, int w, DisplayMode mode);
    void setTableHeight(uint tableID, int h, DisplayMode mode);

signals:
    void connectionSuccess();
    void connectionFailed(QString errorMsg);
    void fillTablesSuccess();
    void fillTablesFailed(QString errorMsg);
    void saveSuccess();
    void saveFailed(QString errorMsg);

public slots:
    void openConnection(DBType type, QStringList options, uint flags);
    void fillTables();
    void save();

private:
    AbstractDB *db = nullptr;
    QVector<Table*> *tables = nullptr;
    AccessMode accessMod;

    void freeResources();
};

#endif // DBHANDLER_H
