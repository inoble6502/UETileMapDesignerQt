#include "historytile.h"

HistoryTile::HistoryTile(QObject *parent) : QObject(parent)
{

}

HistoryTile::HistoryTile(Tile *ht)
{
    this->setTile(ht);
    this->setPreviousData(ht->getData());
}

HistoryTile::HistoryTile(Tile *ht, TileData pData)
{
    this->setTile(ht);
    this->setPreviousData(pData);
}

HistoryTile::HistoryTile(const HistoryTile &ht)
{
    this->setTile(ht.getTile());
    this->setPreviousData(ht.previousData);
}

Tile *HistoryTile::getTile() const
{
    return t;
}

void HistoryTile::setTile(Tile *value)
{
    t = value;
}

TileData HistoryTile::getPreviousData() const
{
    return previousData;
}

void HistoryTile::setPreviousData(const TileData &value)
{
    previousData = value;
}

void HistoryTile::applyPreviousDataToTile()
{
    //give tile its previous data
    //at the same time switch with current data
    if(!t)
        return;

    TileData temp = t->getData();
    t->setData(previousData);
    t->update();
    this->setPreviousData(temp);
}

void HistoryTile::operator =(const HistoryTile &ht)
{
    this->setTile(ht.getTile());
    this->setPreviousData(ht.previousData);
}
