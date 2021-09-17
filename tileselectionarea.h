#ifndef TILESELECTIONAREA_H
#define TILESELECTIONAREA_H

#include <QGraphicsScene>
#include <QVector>
#include "tile.h"

class TileSelectionArea : public QGraphicsScene
{
    Q_OBJECT
public:
    TileSelectionArea();
    TileSelectionArea(float spacing);

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    QVector<Tile> getSelectionTileVec() const;
    void setSelectionTileVec(const QVector<Tile> &value);

    void initSelectionTileVec();
    void initBasicTilesVertical();
    void setTileCoordsV();

    void addLastTileToScene();
    void addTilesToScene();
    void removeTilesFromScene();
    void appendTileToVectAndScene(uint8_t n, uint8_t e, uint8_t s, uint8_t w, uint8_t t);
    void removeLastTileFromVecAndScene();

    void setTileSpacing(float value);
    void updateSpacingForTiles();

    int getTileVecLength();
    void updateCoordsOfTileAtVecPos(int p);

signals:
    void leftClicked(Tile *t);

private:
    QVector<Tile> selectionTileVec;
    float tileSpacing;
};

#endif // TILESELECTIONAREA_H
