#include "dungeonlayoutscene.h"
#include <QGraphicsSceneMouseEvent>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <iostream>

DungeonLayoutScene::DungeonLayoutScene()
{
    this->initWalledDungeonWithBlankTiles();

    this->addTilesToScene();
    this->setTileSpacing(1.05);
    this->updateSpacingForTiles();
    this->setTilesEditedinMove(false);
}

DungeonLayoutScene::DungeonLayoutScene(uint8_t initValue)
{
    switch(initValue)
    {
    case DungeonLayoutScene::DUNGEON_ALL_NULL:
        this->initDungeonWithNullTiles();
        break;
    case DungeonLayoutScene::DUNGEON_ALL_BLANK:
        this->initDungeonWithBlankTiles();
        break;
    case DungeonLayoutScene::DUNGEON_WALLED_BLANK:
        this->initWalledDungeonWithBlankTiles();
        break;
    default:
        this->initWalledDungeonWithBlankTiles();
    }

    this->addTilesToScene();
    this->setTileSpacing(1.05);
    this->initTileCoords();
    this->updateSpacingForTiles();
    this->setTilesEditedinMove(false);
}

DungeonLayoutScene::DungeonLayoutScene(std::array<std::array<Tile, MAX_DIM>, MAX_DIM> t)
{
    this->tiles = t;

    this->addTilesToScene();
    this->setTileSpacing(1.05);
    this->updateSpacingForTiles();
}

DungeonLayoutScene::~DungeonLayoutScene()
{

}

void DungeonLayoutScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Tile *t;
    QPointF mousePos;
    int s = 0;
    mousePos = event->scenePos();
    t = qgraphicsitem_cast<Tile*>(this->itemAt(mousePos.x(), mousePos.y(), QTransform()));

    if(!t)
        return;

    if(event->button() == Qt::LeftButton)
    {
        t->printTileData("TileSelectionArea: \n");

        this->actionHistory.addTileToHistoryMap(t);
        this->actionHistory.incrementHistoryIndex();
        emit this->DungeonLayoutSceneTileClicked(t);
    }
    else if(event->button() == Qt::RightButton)
    {
        t->printTileData("TileSelectionArea: \n");
        TileEditDialog *tEdit = new TileEditDialog(t);
        tEdit->setAttribute(Qt::WA_DeleteOnClose, true);
        tEdit->show();
    }

    s++;
    std::cout << "Move : " << s << std::endl;
}

void DungeonLayoutScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    Tile *t;
    QPointF mousePos;
    mousePos = event->scenePos();
    t = qgraphicsitem_cast<Tile*>(this->itemAt(mousePos.x(), mousePos.y(), QTransform()));

    if(!t)
        return;

    if(t == this->last)
        return;

    this->actionHistory.addTileToHistoryMap(t, t->getData());
    this->tileIndexes.append(this->actionHistory.getCurrentHistoryIndex());
    this->actionHistory.incrementHistoryIndex();
    this->setTilesEditedinMove(true);

    //set clicked tile to current one
    emit this->DungeonLayoutSceneTileClicked(t);

    this->last = t;
}

void DungeonLayoutScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->actionHistory.printCurrentIndex();
    std::cout << "History Size: " <<
                 this->actionHistory.historySize() << std::endl;
}

void DungeonLayoutScene::initDungeonWithNullTiles()
{
    for(uint8_t i = 0; i < MAX_DIM; i++)
    {
        for(uint8_t j = 0; j < MAX_DIM; j++)
        {
            tiles[i][j].makeTileNull();
            tiles[i][j].update();
        }
    }
}

void DungeonLayoutScene::initDungeonWithBlankTiles()
{
    for(uint8_t i = 0; i < MAX_DIM; i++)
    {
        for(uint8_t j = 0; j < MAX_DIM; j++)
        {
            tiles[i][j].makeTileBlank();
            tiles[i][j].update();
        }
    }
}

void DungeonLayoutScene::initWalledDungeonWithBlankTiles()
{
    this->initDungeonWithBlankTiles();

    for(uint8_t i = 0; i < MAX_DIM; i++)
    {
        this->tiles[0][i].setTileWest(TileData::TILE_S_WALL);
        this->tiles[0][i].update();
        this->tiles[i][MAX_DIM - 1].setTileSouth(TileData::TILE_S_WALL);
        this->tiles[i][MAX_DIM - 1].update();
        this->tiles[MAX_DIM - 1][i].setTileEast(TileData::TILE_S_WALL);
        this->tiles[MAX_DIM - 1][i].update();
        this->tiles[i][0].setTileNorth(TileData::TILE_S_WALL);
        this->tiles[i][0].update();
    }
}

std::string DungeonLayoutScene::constructCSVString()
{
    using namespace std;
    string r;
    r = ",tType,tSideN,tSideE,tSideS,tSideW,tDoorN,tDoorE,tDoorS,tDoorW,tCoordY,tCoordX,tTelY,tTelX,Misc0,Misc1,Misc2,Misc3,Misc4,Misc5,Misc6,Misc7";
    r += "\n";
    int f = 0;
    uint8_t type = 0;
    uint8_t n = 0, e = 0, s = 0, w = 0;
    uint8_t doorN = 0, doorE = 0, doorS = 0, doorW = 0;
    uint8_t y = 0, x = 0;
    uint8_t tY = 0, tX = 0;
    array<short, 8> m;
    Tile currentTile;

    for(uint8_t i = 0; i < MAX_DIM; i++)
    {
        for(uint8_t j = 0; j < MAX_DIM; j++)
        {
            currentTile = this->tiles[i][j];

            type = currentTile.getTileType();

            n = currentTile.getTileNorth();
            e = currentTile.getTileEast();
            s = currentTile.getTileSouth();
            w = currentTile.getTileWest();

            doorN = currentTile.getDoorNorth();
            doorE = currentTile.getDoorEast();
            doorS = currentTile.getDoorSouth();
            doorW = currentTile.getDoorWest();

            y = currentTile.getTileCoordY();
            x = currentTile.getTileCoordX();

            tY = currentTile.getTeleportY();
            tX = currentTile.getTeleportX();

            m = currentTile.getMiscData();

            //construct line with vars
            r += to_string(f) + ",";
            r += to_string(type) + ",";

            r += to_string(n) + "," +
                    to_string(e) + "," +
                    to_string(s) + "," +
                    to_string(w) + ",";

            r += to_string(doorN) + "," +
                    to_string(doorE) + "," +
                    to_string(doorS) + "," +
                    to_string(doorW) + ",";

            r += to_string(y) + "," + to_string(x) + ",";

            r += to_string(tY) + "," + to_string(tX) + ",";

            r += to_string(m[0]) + "," + to_string(m[1]) + "," +
                    to_string(m[2]) + "," + to_string(m[3]) + "," +
                    to_string(m[4]) + "," + to_string(m[5]) + "," +
                    to_string(m[6]) + "," + to_string(m[7]);

            r += "\n";

            f++;
        }
    }

    return r;
}

void DungeonLayoutScene::saveDungeonLayoutDataToCSV()
{
    QString f = QFileDialog::getSaveFileName(nullptr, "Save as CSV", ".", "CSV (*.csv)");
    QFile file(f);
    QString text = "";

    if(!file.open(QFile::Text | QFile::WriteOnly))
    {
        QMessageBox::warning(nullptr, "Error", "Cannot save file" + file.errorString() );
        return;
    }

    QTextStream out(&file);
    text = QString::fromStdString(this->constructCSVString());
    out << text;
    file.close();
}

void DungeonLayoutScene::saveDungeonLayoutDataToCSV(QString f)
{
    f += ".csv";
    QFile file(f);
    QString text = "";

    if(!file.open(QFile::Text | QFile::WriteOnly))
    {
        QMessageBox::warning(nullptr, "Error", "Cannot save file" + file.errorString() );
        return;
    }

    QTextStream out(&file);
    text = QString::fromStdString(this->constructCSVString());
    out << text;
    file.close();
}

std::array<std::array<Tile, 32>, 32> DungeonLayoutScene::getTiles() const
{
    return tiles;
}

void DungeonLayoutScene::setTiles(const std::array<std::array<Tile, 32>, 32> &value)
{
    tiles = value;
}

float DungeonLayoutScene::getTileSpacing() const
{
    return tileSpacing;
}

void DungeonLayoutScene::setTileSpacing(float value)
{
    tileSpacing = value;
}

void DungeonLayoutScene::updateSpacingForTiles()
{
    for(uint8_t i = 0; i < MAX_DIM; i++)
        for(uint8_t j = 0; j < MAX_DIM; j++)
            tiles[i][j].updateSpacing(this->getTileSpacing());
}

void DungeonLayoutScene::addTilesToScene()
{
    for(uint8_t i = 0; i < MAX_DIM; i++)
        for(uint8_t j = 0; j < MAX_DIM; j++)
            this->addItem(&tiles[i][j]);
}

void DungeonLayoutScene::updateAllTiles()
{
    for(uint8_t i = 0; i < MAX_DIM; i++)
        for(uint8_t j = 0; j < MAX_DIM; j++)
            tiles[i][j].update();
}

void DungeonLayoutScene::initTileCoords()
{
    for(uint8_t i = 0; i < MAX_DIM; i++)
        for(uint8_t j = 0; j < MAX_DIM; j++)
            tiles[i][j].setTileCoords(i, j);
}

bool DungeonLayoutScene::getTilesEditedinMove() const
{
    return tileEditedinMove;
}

void DungeonLayoutScene::setTilesEditedinMove(bool value)
{
    tileEditedinMove = value;
}

History DungeonLayoutScene::getActionHistory() const
{
    return actionHistory;
}

void DungeonLayoutScene::setActionHistory(const History &value)
{
    actionHistory = value;
}

void DungeonLayoutScene::decrementHistIndexAndRevert()
{
    this->actionHistory.decrementHistoryIndex();
    this->actionHistory.revertHistoryTilesAtCurrentIndex();
}

void DungeonLayoutScene::incrementHistIndexAndRevert()
{
    this->actionHistory.revertHistoryTilesAtCurrentIndex();
    this->actionHistory.incrementHistoryIndex();
}

QVector<int> DungeonLayoutScene::getTileIndexes() const
{
    return tileIndexes;
}

void DungeonLayoutScene::setTileIndexes(const QVector<int> &value)
{
    tileIndexes = value;
}

void DungeonLayoutScene::clearTileIndexValues()
{
    this->tileIndexes.clear();
}
