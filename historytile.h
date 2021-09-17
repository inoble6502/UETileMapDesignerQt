#ifndef HISTORYTILE_H
#define HISTORYTILE_H

#include <QObject>
#include "tile.h"

class HistoryTile : public QObject
{
    Q_OBJECT
public:
    explicit HistoryTile(QObject *parent = nullptr);
    HistoryTile(Tile *ht);
    HistoryTile(Tile *ht, TileData pData);
    HistoryTile(const HistoryTile &ht);

    Tile *getTile() const;
    void setTile(Tile *value);
    TileData getPreviousData() const;
    void setPreviousData(const TileData &value);

    void applyPreviousDataToTile();

    void operator = (const HistoryTile &ht);

signals:

private:
    Tile *t = 0;
    TileData previousData;
};

#endif // HISTORYTILE_H
