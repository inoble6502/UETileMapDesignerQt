#include "tileselectionarea.h"
#include <iostream>
#include <QGraphicsSceneMouseEvent>

TileSelectionArea::TileSelectionArea()
{
    this->initSelectionTileVec();
    this->addTilesToScene();
    this->setTileCoordsV();
    this->setTileSpacing(1.05);
    this->updateSpacingForTiles();
}

TileSelectionArea::TileSelectionArea(float spacing)
{
    this->initSelectionTileVec();
    this->addTilesToScene();

    this->setTileSpacing(spacing);
    this->updateSpacingForTiles();
}

void TileSelectionArea::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Tile *t;
    QPointF mousePos;
    mousePos = event->scenePos();
    t = qgraphicsitem_cast<Tile*>(this->itemAt(mousePos.x(), mousePos.y(), QTransform()));

    if(!t)
        return;

    if(event->button() == Qt::LeftButton)
    {
        t->printTileData("TileSelectionArea: \n");
        emit this->leftClicked(t);
    }
}

QVector<Tile> TileSelectionArea::getSelectionTileVec() const
{
    return selectionTileVec;
}

void TileSelectionArea::setSelectionTileVec(const QVector<Tile> &value)
{
    selectionTileVec = value;
}

void TileSelectionArea::initSelectionTileVec()
{
    this->initBasicTilesVertical();
}

void TileSelectionArea::initBasicTilesVertical()
{
    this->selectionTileVec.append(Tile(0, 0, 0, 0, 0, 0, TileData::TILE_NORMAL));
    this->selectionTileVec.append(Tile(0, 0, 0, 1, 1, 0, TileData::TILE_NORMAL));
    this->selectionTileVec.append(Tile(0, 0, 1, 0, 0, 1, TileData::TILE_NORMAL));
    this->selectionTileVec.append(Tile(0, 0, 1, 1, 1, 1, TileData::TILE_NORMAL));
    this->selectionTileVec.append(Tile(0, 1, 0, 0, 0, 2, TileData::TILE_NORMAL));
    this->selectionTileVec.append(Tile(0, 1, 0, 1, 1, 2, TileData::TILE_NORMAL));
    this->selectionTileVec.append(Tile(0, 1, 1, 0, 0, 3, TileData::TILE_NORMAL));
    this->selectionTileVec.append(Tile(0, 1, 1, 1, 1, 3, TileData::TILE_NORMAL));
    this->selectionTileVec.append(Tile(1, 0, 0, 0, 0, 4, TileData::TILE_NORMAL));
    this->selectionTileVec.append(Tile(1, 0, 0, 1, 1, 4, TileData::TILE_NORMAL));
    this->selectionTileVec.append(Tile(1, 0, 1, 0, 0, 5, TileData::TILE_NORMAL));
    this->selectionTileVec.append(Tile(1, 0, 1, 1, 1, 5, TileData::TILE_NORMAL));
    this->selectionTileVec.append(Tile(1, 1, 0, 0, 0, 6, TileData::TILE_NORMAL));
    this->selectionTileVec.append(Tile(1, 1, 0, 1, 1, 6, TileData::TILE_NORMAL));
    this->selectionTileVec.append(Tile(1, 1, 1, 0, 0, 7, TileData::TILE_NORMAL));
    this->selectionTileVec.append(Tile(1, 1, 1, 1, 1, 7, TileData::TILE_NORMAL));
    this->selectionTileVec.append(Tile(0, 0, 0, 0, 0, 8, TileData::TILE_NULL));

    this->selectionTileVec.append(Tile(0, 0, 0, 0, 1, 8, TileData::TILE_TELEPORT));
    this->selectionTileVec.append(Tile(0, 0, 0, 0, 0, 9, TileData::TILE_DAMAGE));
    this->selectionTileVec.append(Tile(0, 0, 0, 0, 1, 9, TileData::TILE_POISON));
    this->selectionTileVec.append(Tile(0, 0, 0, 0, 0, 10, TileData::TILE_FOG));

    this->selectionTileVec.append(Tile(0, 0, 0, 0, 1, 10, TileData::TILE_SLIDE_NORTH));
    this->selectionTileVec.append(Tile(0, 0, 0, 0, 0, 11, TileData::TILE_SLIDE_EAST));
    this->selectionTileVec.append(Tile(0, 0, 0, 0, 1, 11, TileData::TILE_SLIDE_SOUTH));
    this->selectionTileVec.append(Tile(0, 0, 0, 0, 0, 12, TileData::TILE_SLIDE_WEST));

    this->selectionTileVec.append(Tile(0, 0, 0, 0, 1, 12, TileData::TILE_HOLE));
    this->selectionTileVec.append(Tile(0, 0, 0, 0, 0, 13, TileData::TILE_RANDOM_DIR));

    this->selectionTileVec.append(Tile(0, 0, 0, 0, 1, 13, TileData::TILE_RESERVE_1));
    this->selectionTileVec.append(Tile(0, 0, 0, 0, 0, 14, TileData::TILE_RESERVE_2));
    this->selectionTileVec.append(Tile(0, 0, 0, 0, 1, 14, TileData::TILE_RESERVE_3));
    this->selectionTileVec.append(Tile(0, 0, 0, 0, 0, 15, TileData::TILE_RESERVE_4));

    this->selectionTileVec.append(Tile(1, 1, TileData::TILE_S_DOORWAY, 1, 1, 15, TileData::TILE_STAIRS_UP));
    this->selectionTileVec.append(Tile(1, 1, TileData::TILE_S_DOORWAY, 1, 0, 16, TileData::TILE_STAIRS_DOWN));
}

void TileSelectionArea::setTileCoordsV()
{
    int s = this->getTileVecLength();

    for(int i = 0; i < s; i++)
        this->selectionTileVec[i].setTileCoords(i % 5, i / 5 % s);
}

void TileSelectionArea::addLastTileToScene()
{
    this->addItem(&this->selectionTileVec.last());
}

void TileSelectionArea::addTilesToScene()
{
    uint8_t s = this->selectionTileVec.size();

    for(uint8_t i = 0; i < s; i++)
        this->addItem(&this->selectionTileVec[i]);
}

void TileSelectionArea::removeTilesFromScene()
{
    uint8_t s = this->selectionTileVec.size();

    for(uint8_t i = 0; i < s; i++)
        this->removeItem(&this->selectionTileVec[i]);
}

void TileSelectionArea::appendTileToVectAndScene(uint8_t n, uint8_t e, uint8_t s, uint8_t w, uint8_t t)
{
    this->selectionTileVec.append(Tile(n, e, s, w, 0, 0, t));
    this->updateCoordsOfTileAtVecPos(this->selectionTileVec.size() - 1);
    this->addTilesToScene();
    this->updateSpacingForTiles();
}

void TileSelectionArea::removeLastTileFromVecAndScene()
{
    this->removeItem(&this->selectionTileVec.last());
    this->selectionTileVec.removeLast();
}

void TileSelectionArea::setTileSpacing(float value)
{
    tileSpacing = value;
}

void TileSelectionArea::updateSpacingForTiles()
{
    uint8_t s = this->selectionTileVec.size();
    for(uint8_t i = 0; i < s; i++)
        this->selectionTileVec[i].updateSpacing(this->tileSpacing);
}

int TileSelectionArea::getTileVecLength()
{
    return this->selectionTileVec.length();
}

void TileSelectionArea::updateCoordsOfTileAtVecPos(int p)
{
    int s = this->selectionTileVec.size();

    if(p > (s - 1))
        return;

    if(p < 0)
        return;

    this->selectionTileVec[p].setTileCoords(p % 5, p / 5 % s);
}
