#ifndef SQLITEUPDATE_H
#define SQLITEUPDATE_H

#include "sqlitequery.h"
#include "sqliteconflictalgo.h"

#include <QStringList>
#include <QMap>

class SqliteExpr;
class SqliteWith;

class API_EXPORT SqliteUpdate : public SqliteQuery
{
    public:
        typedef QPair<QVariant,SqliteExpr*> ColumnAndValue;

        SqliteUpdate();
        SqliteUpdate(const SqliteUpdate& other);
        ~SqliteUpdate();
        SqliteUpdate(SqliteConflictAlgo onConflict, const QString& name1, const QString& name2,
                     bool notIndexedKw, const QString& indexedBy, const QList<ColumnAndValue>& values,
                     SqliteExpr* where, SqliteWith* with);

        SqliteStatement* clone();
        SqliteExpr* getValueForColumnSet(const QString& column);

        SqliteConflictAlgo onConflict = SqliteConflictAlgo::null;
        QString database = QString();
        QString table = QString();
        bool indexedByKw = false;
        bool notIndexedKw = false;
        QString indexedBy = QString();
        QList<ColumnAndValue> keyValueMap;
        SqliteExpr* where = nullptr;
        SqliteWith* with = nullptr;

    protected:
        QStringList getColumnsInStatement();
        QStringList getTablesInStatement();
        QStringList getDatabasesInStatement();
        TokenList getColumnTokensInStatement();
        TokenList getTableTokensInStatement();
        TokenList getDatabaseTokensInStatement();
        QList<FullObject> getFullObjectsInStatement();
        TokenList rebuildTokensFromContents();
};

typedef QSharedPointer<SqliteUpdate> SqliteUpdatePtr;

#endif // SQLITEUPDATE_H
