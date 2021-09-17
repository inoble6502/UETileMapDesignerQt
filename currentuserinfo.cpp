#include "currentuserinfo.h"

CurrentUserInfo::CurrentUserInfo(QObject *parent) : QObject(parent)
{

}

CurrentUserInfo::CurrentUserInfo(Tile *t, QObject *parent)
{
    this->setSelectedTile(t);
}

Tile *CurrentUserInfo::getSelectedTile() const
{
    return selectedTile;
}

void CurrentUserInfo::setSelectedTile(Tile *value)
{
    selectedTile = value;
}

void CurrentUserInfo::updateClickedTile(Tile *t)
{
    if(!this->selectedTile)
        return;

    uint8_t type;
    uint8_t n, e, s, w;

    type = this->selectedTile->getTileType();

    n = this->selectedTile->getTileNorth();
    e = this->selectedTile->getTileEast();
    s = this->selectedTile->getTileSouth();
    w = this->selectedTile->getTileWest();

    t->setTileType(type);
    t->setTileSides(n, e, s, w);

    t->update();
}

void CurrentUserInfo::updateUserSelectedTile(Tile *t)
{
    this->setSelectedTile(t);
    emit this->tileSelectionChanged(t);

    this->selectedTile->printTileData("Current User Info Selected: ");
}
