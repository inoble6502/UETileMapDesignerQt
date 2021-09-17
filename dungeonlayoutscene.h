#ifndef DUNGEONLAYOUTSCENE_H
#define DUNGEONLAYOUTSCENE_H

#define MAX_DIM 32

#include <QGraphicsScene>
#include <QVector>
#include <array>
#include <string>
#include "tile.h"
#include "history.h"
#include "tileeditdialog.h"

class DungeonLayoutScene : public QGraphicsScene
{
    Q_OBJECT

public:
    enum InitialDungeonType
    {
        DUNGEON_ALL_NULL = 0,
        DUNGEON_ALL_BLANK,
        DUNGEON_WALLED_BLANK
    };

    DungeonLayoutScene();
    DungeonLayoutScene(uint8_t initValue);
    DungeonLayoutScene(std::array<std::array<Tile, MAX_DIM>, MAX_DIM> t);
    ~DungeonLayoutScene();

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    void initDungeonWithNullTiles();
    void initDungeonWithBlankTiles();
    void initWalledDungeonWithBlankTiles();

    std::string constructCSVString();
    void saveDungeonLayoutDataToCSV();
    void saveDungeonLayoutDataToCSV(QString f);

    std::array<std::array<Tile, 32>, 32> getTiles() const;
    void setTiles(const std::array<std::array<Tile, 32>, 32> &value);

    Tile getLayoutTileAtCoord(uint8_t y, uint8_t x);
    void setLayoutTileAtCoord(uint8_t y, uint8_t x, Tile t);

    float getTileSpacing() const;
    void setTileSpacing(float value);
    void updateSpacingForTiles();

    void addTilesToScene();
    void updateAllTiles();
    void initTileCoords();

    bool getTilesEditedinMove() const;
    void setTilesEditedinMove(bool value);

    History getActionHistory() const;
    void setActionHistory(const History &value);
    void decrementHistIndexAndRevert();
    void incrementHistIndexAndRevert();

    bool wereTilesEditedinMouseMove();

    QVector<int> getTileIndexes() const;
    void setTileIndexes(const QVector<int> &value);
    void clearTileIndexValues();

signals:
    void DungeonLayoutSceneTileClicked(Tile *t);

private:
    std::array<std::array<Tile, MAX_DIM>, MAX_DIM> tiles;

    History actionHistory;
    QVector<int> tileIndexes;
    Tile *last = 0;

    float tileSpacing = 1.05;
    bool tileEditedinMove = false;
};

#endif // DUNGEONLAYOUTSCENE_H
