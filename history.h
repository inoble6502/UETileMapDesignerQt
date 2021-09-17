#ifndef HISTORY_H
#define HISTORY_H

#include <QObject>
#include <QMap>
#include <map>
#include "historytile.h"

class History
{
public:
    History();
    History(int i);

    void clearHistory();
    int historySize();
    void revertHistoryTileAtIndex(int index);
    void revertHistoryTilesAtCurrentIndex();

    int getCurrentHistoryIndex() const;
    void setCurrentHistoryIndex(int value);

    void decrementHistoryIndex();
    void incrementHistoryIndex();

    void printCurrentIndex();

    void addTileToHistoryMap(Tile *t);
    void addTileToHistoryMap(Tile *t, TileData d);

    int getCountofIndex(int i);

private:
    int currentHistoryIndex = 0;
    QMap<int, HistoryTile> historyMap;
};

#endif // HISTORY_H
