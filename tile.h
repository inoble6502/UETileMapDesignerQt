#ifndef TILE_H
#define TILE_H

#define MAX_MISCDATA_SIZE 8

#include <QGraphicsItem>
#include <QPixmap>
#include <array>
#include <string>

extern std::array<QPixmap *, 10> tileSideTypePixmaps;
extern std::array<QPixmap *, 21> tileTypePixmaps;

typedef struct TileData
{
    enum TileDValues
    {
        TILE_D_NORTH = 0,
        TILE_D_EAST,
        TILE_D_SOUTH,
        TILE_D_WEST
    };

    enum TileDoorValues
    {
        DOOR_UNLOCKED = 0,
        DOOR_LOCKED
    };

    enum TileType
    {
        TILE_NULL = 0,
        TILE_NORMAL,
        TILE_STAIRS_UP,
        TILE_STAIRS_DOWN,
        TILE_TELEPORT,
        TILE_DAMAGE,
        TILE_POISON,
        TILE_FOG,
        TILE_HOLE,
        TILE_SLIDE_NORTH,
        TILE_SLIDE_EAST,
        TILE_SLIDE_SOUTH,
        TILE_SLIDE_WEST,
        TILE_ENTER_EXIT,
        TILE_ELEVATOR,
        TILE_RANDOM_DIR,
        TILE_EVENT,
        TILE_RESERVE_1,
        TILE_RESERVE_2,
        TILE_RESERVE_3,
        TILE_RESERVE_4
    };

    enum TileSideTypes
    {
        TILE_S_NONE = 0,
        TILE_S_WALL,
        TILE_S_DOORWAY,
        TILE_S_DOOR,
        TILE_S_INVS_WALL,
        TILE_S_ILLS_WALL,
        TILE_S_RESERVE_1,
        TILE_S_RESERVE_2,
        TILE_S_RESERVE_3,
        TILE_S_RESERVE_4
    };

    std::array<uint8_t, 4> sides;
    std::array<bool, 4> doorBools = {true, true, true, true};
    uint8_t type;
    uint8_t coordX, coordY;
    uint8_t teleportX, teleportY;

    std::array<short, 8> miscData = {0, 0, 0, 0, 0, 0, 0, 0};
} TileData;

class Tile : public QGraphicsItem
{
public:
    enum { Type = UserType + 1 };

    Tile();
    Tile(uint8_t y, uint8_t x);
    Tile(uint8_t n, uint8_t e, uint8_t s, uint8_t w);
    Tile(uint8_t n, uint8_t e, uint8_t s, uint8_t w,
         uint8_t y, uint8_t x);
    Tile(uint8_t n, uint8_t e, uint8_t s, uint8_t w,
         uint8_t y, uint8_t x,
         uint8_t t);
    Tile(uint8_t n, uint8_t e, uint8_t s, uint8_t w,
         uint8_t y, uint8_t x,
         uint8_t t,
         uint8_t ty, uint8_t tx);
    Tile(const Tile &t);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;

    int type() const override;

    TileData getData() const;
    void setData(const TileData &value);

    uint8_t getTileNorth() const;
    uint8_t getTileWest() const;
    uint8_t getTileSouth() const;
    uint8_t getTileEast() const;

    uint8_t getTileType() const;

    uint8_t getTileCoordX() const;
    uint8_t getTileCoordY() const;

    uint8_t getTeleportX() const;
    uint8_t getTeleportY() const;

    bool getDoorNorth() const;
    bool getDoorEast() const;
    bool getDoorSouth() const;
    bool getDoorWest() const;
    std::array<bool, 4> getDoorBools();

    std::array<short, 8> getMiscData();

    void setTileNorth(uint8_t n);
    void setTileEast(uint8_t e);
    void setTileSouth(uint8_t s);
    void setTileWest(uint8_t w);

    void setTileType(uint8_t t);

    void setTileCoordX(uint8_t x);
    void setTileCoordY(uint8_t y);

    void setTeleportX(uint8_t x);
    void setTeleportY(uint8_t y);

    void setTileSides(uint8_t n, uint8_t e, uint8_t s, uint8_t w);
    void setTileCoords(uint8_t y, uint8_t x);
    void setTileTeleportCoords(uint8_t y, uint8_t x);
    void setUpTileData(uint8_t n, uint8_t e, uint8_t s, uint8_t w,
                       uint8_t y, uint8_t x,
                       uint8_t t,
                       uint8_t ty, uint8_t tx);

    void setDoorNorth(bool n);
    void setDoorEast(bool e);
    void setDoorSouth(bool s);
    void setDoorWest(bool w);

    void setDoorBools(bool n, bool e, bool s, bool w);
    void setDoorBools(std::array<bool, 4> d);

    void resetDoorBools();

    void setMiscData(std::array<short, 8> m);
    void resetMiscData();
    void setMiscDataAtPos(uint8_t pos, uint8_t value);

    void makeTileNull();
    void makeTileBlank();

    void operator = (const Tile &t);

    void printTileData();
    void printTileData(std::string prepend);

    float getSpacing() const;
    void setSpacing(float value);
    void updateSpacing(float value);

private:
    TileData data;
    float spacing = 1; //spacing between other tiles
};

//void initTilePixmaps();
void initTileSidePixmaps();
void initTileTypePixmaps();
void deleteTileSidePixmaps();
void deleteTileTypePixmaps();
void deleteTilePixmaps();

#endif // TILE_H
