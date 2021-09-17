#include "tile.h"
#include <QPainter>
#include <iostream>

std::array<QPixmap *, 10> tileSideTypePixmaps;
std::array<QPixmap *, 21> tileTypePixmaps;

Tile::Tile()
{
    this->setUpTileData(0, 0, 0, 0, 0, 0, 0, 0, 0);
}

Tile::Tile(uint8_t y, uint8_t x)
{
    this->setUpTileData(0, 0, 0, 0, y, x, 0, 0, 0);
}

Tile::Tile(uint8_t n, uint8_t e, uint8_t s, uint8_t w)
{
    this->setUpTileData(n, e, s, w, 0, 0, 0, 0, 0);
}

Tile::Tile(uint8_t n, uint8_t e, uint8_t s, uint8_t w,
           uint8_t y, uint8_t x)
{
    this->setUpTileData(n, e, s, w, y, x, 0, 0, 0);
}

Tile::Tile(uint8_t n, uint8_t e, uint8_t s, uint8_t w,
           uint8_t y, uint8_t x, uint8_t t)
{
    this->setUpTileData(n, e, s, w, y, x, t, 0, 0);
}

Tile::Tile(uint8_t n, uint8_t e, uint8_t s, uint8_t w,
           uint8_t y, uint8_t x,
           uint8_t t,
           uint8_t ty, uint8_t tx)
{
    this->setUpTileData(n, e, s, w, y, x, t, ty, tx);
}

Tile::Tile(const Tile &t)
    : QGraphicsItem()
{
    uint8_t n, e, s, w;
    uint8_t tp;
    uint8_t y, x;
    uint8_t ty, tx;

    n = t.getTileNorth();
    e = t.getTileEast();
    s = t.getTileSouth();
    w = t.getTileWest();

    tp = t.getTileType();

    y = t.getTileCoordY();
    x = t.getTileCoordX();

    ty = t.getTeleportY();
    tx = t.getTeleportX();

    this->setUpTileData(n, e, s, w, y, x, tp, ty, tx);
    this->data.doorBools = t.getData().doorBools;
    this->data.miscData = t.getData().miscData;

    //update();
}

QRectF Tile::boundingRect() const
{
    return QRectF(this->getTileCoordY() * 16 * this->spacing,
                  this->getTileCoordX() * 16 * this->spacing,
                  16, 16);
}

void Tile::paint(QPainter *painter,
                 const QStyleOptionGraphicsItem *option,
                 QWidget *widget)
{
    QRect rect;
    uint8_t n, e, s, w, t;

    rect = this->boundingRect().toRect();
    n = this->data.sides[TileData::TILE_D_NORTH];
    e = this->data.sides[TileData::TILE_D_EAST];
    s = this->data.sides[TileData::TILE_D_SOUTH];
    w = this->data.sides[TileData::TILE_D_WEST];
    t = this->data.type;

    QPixmap &tPix = *tileTypePixmaps[t];
    QPixmap &nPix = *tileSideTypePixmaps[n];
    QPixmap &ePix = *tileSideTypePixmaps[e];
    QPixmap &sPix = *tileSideTypePixmaps[s];
    QPixmap &wPix = *tileSideTypePixmaps[w];

    //render tile type
    painter->drawPixmap(rect, tPix);

    //render north side
    painter->drawPixmap(rect, nPix);

    //render east side
    painter->translate(this->data.coordY * 16 * this->spacing,
                       this->data.coordX * 16 * this->spacing);
    painter->rotate(90);
    painter->drawPixmap(0, -16, ePix);

    //render west side
    painter->rotate(180);
    painter->drawPixmap(-16, 0, wPix);

    //render south side
    painter->rotate(270);
    painter->drawPixmap(-16, -16, sPix);
}

int Tile::type() const
{
    // Enable the use of qgraphicsitem_cast with this item.
    return Type;
}

TileData Tile::getData() const
{
    return data;
}

void Tile::setData(const TileData &value)
{
    data = value;
}

uint8_t Tile::getTileNorth() const
{
    return this->data.sides[TileData::TILE_D_NORTH];
}

uint8_t Tile::getTileWest() const
{
    return this->data.sides[TileData::TILE_D_WEST];
}

uint8_t Tile::getTileSouth() const
{
    return this->data.sides[TileData::TILE_D_SOUTH];
}

uint8_t Tile::getTileEast() const
{
    return this->data.sides[TileData::TILE_D_EAST];
}

uint8_t Tile::getTileType() const
{
    return this->data.type;
}

uint8_t Tile::getTileCoordX() const
{
    return this->data.coordX;
}

uint8_t Tile::getTileCoordY() const
{
    return this->data.coordY;
}

uint8_t Tile::getTeleportX() const
{
    return this->data.teleportX;
}

uint8_t Tile::getTeleportY() const
{
    return this->data.teleportY;
}

bool Tile::getDoorNorth() const
{
    return this->data.doorBools[TileData::TILE_D_NORTH];
}

bool Tile::getDoorEast() const
{
    return this->data.doorBools[TileData::TILE_D_EAST];
}

bool Tile::getDoorSouth() const
{
    return this->data.doorBools[TileData::TILE_D_SOUTH];
}

bool Tile::getDoorWest() const
{
    return this->data.doorBools[TileData::TILE_D_WEST];
}

std::array<bool, 4> Tile::getDoorBools()
{
    return this->data.doorBools;
}

std::array<short, 8> Tile::getMiscData()
{
    return this->data.miscData;
}

void Tile::setTileNorth(uint8_t n)
{
    this->data.sides[TileData::TILE_D_NORTH] = n;
}

void Tile::setTileEast(uint8_t e)
{
    this->data.sides[TileData::TILE_D_EAST] = e;
}

void Tile::setTileSouth(uint8_t s)
{
    this->data.sides[TileData::TILE_D_SOUTH] = s;
}

void Tile::setTileWest(uint8_t w)
{
    this->data.sides[TileData::TILE_D_WEST] = w;
}

void Tile::setTileType(uint8_t t)
{
    this->data.type = t;
}

void Tile::setTileCoordX(uint8_t x)
{
    this->data.coordX = x;
}

void Tile::setTileCoordY(uint8_t y)
{
    this->data.coordY = y;
}

void Tile::setTeleportX(uint8_t x)
{
    this->data.teleportX = x;
}

void Tile::setTeleportY(uint8_t y)
{
    this->data.teleportY = y;
}

void Tile::setTileSides(uint8_t n, uint8_t e, uint8_t s, uint8_t w)
{
    this->setTileNorth(n);
    this->setTileEast(e);
    this->setTileSouth(s);
    this->setTileWest(w);
}

void Tile::setTileCoords(uint8_t y, uint8_t x)
{
    this->setTileCoordY(y);
    this->setTileCoordX(x);
}

void Tile::setTileTeleportCoords(uint8_t y, uint8_t x)
{
    this->setTeleportY(y);
    this->setTeleportX(x);
}

void Tile::setUpTileData(uint8_t n, uint8_t e, uint8_t s, uint8_t w, uint8_t y, uint8_t x, uint8_t t, uint8_t ty, uint8_t tx)
{
    this->setTileSides(n, e, s, w);
    this->setTileCoords(y, x);
    this->setTileType(t);
    this->setTileTeleportCoords(ty, tx);

    this->setDoorBools(true, true, true, true);

    for(uint8_t i = 0; i < this->data.miscData.size(); i++)
        data.miscData[i] = 0;

    update();
}

void Tile::setDoorNorth(bool n)
{
    this->data.doorBools[TileData::TILE_D_NORTH] = n;
}

void Tile::setDoorEast(bool e)
{
    this->data.doorBools[TileData::TILE_D_EAST] = e;
}

void Tile::setDoorSouth(bool s)
{
    this->data.doorBools[TileData::TILE_D_SOUTH] = s;
}

void Tile::setDoorWest(bool w)
{
    this->data.doorBools[TileData::TILE_D_WEST] = w;
}

void Tile::setDoorBools(bool n, bool e, bool s, bool w)
{
    this->setDoorNorth(n);
    this->setDoorEast(e);
    this->setDoorSouth(s);
    this->setDoorWest(w);
}

void Tile::setDoorBools(std::array<bool, 4> d)
{
    this->data.doorBools = d;
}

void Tile::resetDoorBools()
{
    this->setDoorBools(0, 0, 0, 0);
}

void Tile::setMiscData(std::array<short, 8> m)
{
    this->data.miscData = m;
}

void Tile::resetMiscData()
{
    this->setMiscData({0, 0, 0, 0, 0, 0, 0, 0});
}

void Tile::setMiscDataAtPos(uint8_t pos, uint8_t value)
{
    if(pos > this->data.miscData.size())
        return;

    this->data.miscData[pos] = value;
}

void Tile::makeTileNull()
{
    this->setTileSides(0, 0, 0, 0);
    this->setTileType(TileData::TILE_NULL);
}

void Tile::makeTileBlank()
{
    this->setTileSides(0, 0, 0, 0);
    this->setTileType(TileData::TILE_NORMAL);
}

void Tile::operator = (const Tile &t)
{
    uint8_t n, e, s, w;
    uint8_t tp;
    uint8_t y, x;
    uint8_t ty, tx;

    n = t.getTileNorth();
    e = t.getTileEast();
    s = t.getTileSouth();
    w = t.getTileWest();

    tp = t.getTileType();

    y = t.getTileCoordY();
    x = t.getTileCoordX();

    ty = t.getTeleportY();
    tx = t.getTeleportX();

    this->setUpTileData(n, e, s, w, y, x, tp, ty, tx);
    this->data.doorBools = t.getData().doorBools;
    this->data.miscData = t.getData().miscData;

    update();
}

void Tile::printTileData()
{
    std::string m;
    uint8_t n, e, s, w;
    uint8_t t;
    uint8_t y, x;
    uint8_t ty, tx;

    n = this->getTileNorth();
    e = this->getTileEast();
    s = this->getTileSouth();
    w = this->getTileWest();

    t = this->getTileType();

    y = this->getTileCoordY();
    x = this->getTileCoordX();

    ty = this->getTeleportY();
    tx = this->getTeleportX();

    using namespace std;
    m = "Tile at Y:" + to_string(y) + " X: " + to_string(x) + " \n";
    m += "N: " + to_string(n)
            + " E: " + to_string(e)
            + " S: " + to_string(s)
            + " W: " + to_string(w)
            + " \n";
    m += "Type: " + to_string(t) + " \n ";
    m += "Teleport to Y: " + to_string(ty) + " X: " + to_string(tx) + " \n ";

    cout << m << endl;
}

void Tile::printTileData(std::string prepend)
{
    std::string m;
    uint8_t n, e, s, w;
    uint8_t t;
    uint8_t y, x;
    uint8_t ty, tx;

    n = this->getTileNorth();
    e = this->getTileEast();
    s = this->getTileSouth();
    w = this->getTileWest();

    t = this->getTileType();

    y = this->getTileCoordY();
    x = this->getTileCoordX();

    ty = this->getTeleportY();
    tx = this->getTeleportX();

    using namespace std;
    m = "Tile at Y:" + to_string(y) + " X: " + to_string(x) + " \n";
    m += "N: " + to_string(n)
            + " E: " + to_string(e)
            + " S: " + to_string(s)
            + " W: " + to_string(w)
            + " \n";
    m += "Type: " + to_string(t) + " \n ";
    m += "Teleport to Y: " + to_string(ty) + " X: " + to_string(tx) + " \n ";
    m += "Doors: N:" + to_string(this->getDoorNorth())
            + " E: " + to_string(this->getDoorEast())
            + " S:" + to_string(this->getDoorSouth())
            + " W: " + to_string(this->getDoorWest())
            + "\n";
    m += "Misc: ";

    for(uint8_t i = 0; i < this->getMiscData().size(); i++)
        m += to_string(this->getMiscData()[i]) + " ";

    m += "\n";

    cout << prepend << m << endl;
}

float Tile::getSpacing() const
{
    return spacing;
}

void Tile::setSpacing(float value)
{
    spacing = value;
}

void Tile::updateSpacing(float value)
{
    this->setSpacing(value);
    update();
}

void deleteTilePixmaps()
{
    deleteTileTypePixmaps();
    deleteTileSidePixmaps();
}

void initTileSidePixmaps()
{
    tileSideTypePixmaps = {
        new QPixmap(":/tile_res/tile_gfx/side/side_none.png"),
        new QPixmap(":/tile_res/tile_gfx/side/side_wall.png"),
        new QPixmap(":/tile_res/tile_gfx/side/side_doorway.png"),
        new QPixmap(":/tile_res/tile_gfx/side/side_door.png"),
        new QPixmap(":/tile_res/tile_gfx/side/side_insv_wall.png"),
        new QPixmap(":/tile_res/tile_gfx/side/side_illus_wall.png"),
        new QPixmap(":/tile_res/tile_gfx/side/side_reserve1.png"),
        new QPixmap(":/tile_res/tile_gfx/side/side_reserve2.png"),
        new QPixmap(":/tile_res/tile_gfx/side/side_reserve3.png"),
        new QPixmap(":/tile_res/tile_gfx/side/side_reserve4.png")
    };
}

void deleteTileSidePixmaps()
{
    int s = tileSideTypePixmaps.size();
    for(int i = s - 1; i >= 0; i--)
        delete tileSideTypePixmaps[i];
}

void initTileTypePixmaps()
{
    tileTypePixmaps = {
        new QPixmap(":/tile_res/tile_gfx/type/type_null.png"),
        new QPixmap(":/tile_res/tile_gfx/type/type_normal.png"),
        new QPixmap(":/tile_res/tile_gfx/type/type_stairs_up.png"),
        new QPixmap(":/tile_res/tile_gfx/type/type_stairs_down.png"),
        new QPixmap(":/tile_res/tile_gfx/type/type_teleport.png"),
        new QPixmap(":/tile_res/tile_gfx/type/type_damage.png"),
        new QPixmap(":/tile_res/tile_gfx/type/type_poison.png"),
        new QPixmap(":/tile_res/tile_gfx/type/type_fog.png"),
        new QPixmap(":/tile_res/tile_gfx/type/type_hole.png"),
        new QPixmap(":/tile_res/tile_gfx/type/type_slide_north.png"),
        new QPixmap(":/tile_res/tile_gfx/type/type_slide_east.png"),
        new QPixmap(":/tile_res/tile_gfx/type/type_slide_south.png"),
        new QPixmap(":/tile_res/tile_gfx/type/type_slide_west.png"),
        new QPixmap(":/tile_res/tile_gfx/type/type_entrance_exit.png"),
        new QPixmap(":/tile_res/tile_gfx/type/type_elevator.png"),
        new QPixmap(":/tile_res/tile_gfx/type/type_random_direction.png"),
        new QPixmap(":/tile_res/tile_gfx/type/type_event.png"),
        new QPixmap(":/tile_res/tile_gfx/type/type_reserve_1.png"),
        new QPixmap(":/tile_res/tile_gfx/type/type_reserve_2.png"),
        new QPixmap(":/tile_res/tile_gfx/type/type_reserve_3.png"),
        new QPixmap(":/tile_res/tile_gfx/type/type_reserve_4.png")
    };
}

void deleteTileTypePixmaps()
{
    int s = tileTypePixmaps.size();
    for(int i = s - 1; i >= 0; i--)
        delete tileTypePixmaps[i];
}
