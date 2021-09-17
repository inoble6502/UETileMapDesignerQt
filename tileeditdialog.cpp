#include "tileeditdialog.h"
#include "ui_tileeditdialog.h"

#include <iostream>

TileEditDialog::TileEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TileEditDialog)
{
    ui->setupUi(this);

    this->scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);

    this->addDisplayTileToScene();
}

TileEditDialog::TileEditDialog(Tile *t, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TileEditDialog)
{
    ui->setupUi(this);

    this->scene = new QGraphicsScene();

    this->setTile(t);
    this->loadClickedTileDataIntoDisplayTile();
    this->addDisplayTileToScene();
    this->updateUITileInfoUponInit();

    ui->graphicsView->setScene(scene);
}

TileEditDialog::~TileEditDialog()
{
    //screws with delete on close
//    delete tile;
//    delete scene;
//    delete ui;
}

Tile *TileEditDialog::getTile() const
{
    return tile;
}

void TileEditDialog::setTile(Tile *value)
{
    tile = value;
}

void TileEditDialog::addDisplayTileToScene()
{
    this->scene->addItem(&this->displayTile);
}

void TileEditDialog::on_tileType_currentIndexChanged(int index)
{
    if(index > -1)
        this->displayTile.setTileType(index);

    this->displayTile.update();
}

void TileEditDialog::on_comboBoxNorth_currentIndexChanged(int index)
{
    if(index > -1)
        this->displayTile.setTileNorth(index);

    this->displayTile.update();
}

void TileEditDialog::on_comboBoxEast_currentIndexChanged(int index)
{
    if(index > -1)
        this->displayTile.setTileEast(index);

    this->displayTile.update();
}

void TileEditDialog::on_comboBoxSouth_currentIndexChanged(int index)
{
    if(index > -1)
        this->displayTile.setTileSouth(index);

    this->displayTile.update();
}

void TileEditDialog::on_comboBoxWest_currentIndexChanged(int index)
{
    if(index > -1)
        this->displayTile.setTileWest(index);

    this->displayTile.update();
}

void TileEditDialog::on_telCoordYSpinBox_valueChanged(int arg1)
{
    this->displayTile.setTeleportY(arg1);
}

void TileEditDialog::on_telCoordXSpinBox_valueChanged(int arg1)
{
    this->displayTile.setTeleportX(arg1);
}

void TileEditDialog::on_doorNorth_currentIndexChanged(int index)
{
    if(index > -1)
        this->displayTile.setDoorNorth(index);
}

void TileEditDialog::on_doorEast_currentIndexChanged(int index)
{
    if(index > -1)
        this->displayTile.setDoorEast(index);
}

void TileEditDialog::on_doorSouth_currentIndexChanged(int index)
{
    if(index > -1)
        this->displayTile.setDoorSouth(index);
}

void TileEditDialog::on_doorWest_currentIndexChanged(int index)
{
    if(index > -1)
        this->displayTile.setDoorWest(index);
}

void TileEditDialog::on_misc0_valueChanged(int arg1)
{
    this->displayTile.setMiscDataAtPos(0, arg1);
}

void TileEditDialog::on_misc1_valueChanged(int arg1)
{
    this->displayTile.setMiscDataAtPos(1, arg1);
}

void TileEditDialog::on_misc2_valueChanged(int arg1)
{
    this->displayTile.setMiscDataAtPos(2, arg1);
}

void TileEditDialog::on_misc3_valueChanged(int arg1)
{
    this->displayTile.setMiscDataAtPos(3, arg1);
}

void TileEditDialog::on_misc4_valueChanged(int arg1)
{
    this->displayTile.setMiscDataAtPos(4, arg1);
}

void TileEditDialog::on_misc5_valueChanged(int arg1)
{
    this->displayTile.setMiscDataAtPos(5, arg1);
}

void TileEditDialog::on_misc6_valueChanged(int arg1)
{
    this->displayTile.setMiscDataAtPos(6, arg1);
}

void TileEditDialog::on_misc7_valueChanged(int arg1)
{
    this->displayTile.setMiscDataAtPos(7, arg1);
}

QGraphicsScene *TileEditDialog::getScene() const
{
    return scene;
}

void TileEditDialog::setScene(QGraphicsScene *value)
{
    scene = value;
}

void TileEditDialog::updateUITileInfoUponInit()
{
    if(!tile)
        return;

    ui->tileType->setCurrentIndex(this->displayTile.getTileType());

    ui->comboBoxNorth->setCurrentIndex(this->displayTile.getTileNorth());
    ui->comboBoxEast->setCurrentIndex(this->displayTile.getTileEast());
    ui->comboBoxSouth->setCurrentIndex(this->displayTile.getTileSouth());
    ui->comboBoxWest->setCurrentIndex(this->displayTile.getTileWest());

    ui->telCoordYSpinBox->setValue(this->displayTile.getTeleportY());
    ui->telCoordXSpinBox->setValue(this->displayTile.getTeleportX());

    ui->doorNorth->setCurrentIndex(this->displayTile.getDoorNorth());
    ui->doorEast->setCurrentIndex(this->displayTile.getDoorEast());
    ui->doorSouth->setCurrentIndex(this->displayTile.getDoorSouth());
    ui->doorWest->setCurrentIndex(this->displayTile.getDoorWest());

    ui->misc0->setValue(this->displayTile.getData().miscData[0]);
    ui->misc1->setValue(this->displayTile.getData().miscData[1]);
    ui->misc2->setValue(this->displayTile.getData().miscData[2]);
    ui->misc3->setValue(this->displayTile.getData().miscData[3]);
    ui->misc4->setValue(this->displayTile.getData().miscData[4]);
    ui->misc5->setValue(this->displayTile.getData().miscData[5]);
    ui->misc6->setValue(this->displayTile.getData().miscData[6]);
    ui->misc7->setValue(this->displayTile.getData().miscData[7]);

    ui->tileCoordY->setText(QString::number(this->displayTile.getTileCoordY()));
    ui->tileCoordX->setText(QString::number(this->displayTile.getTileCoordX()));
}

void TileEditDialog::on_pushUpdate_clicked()
{
//    this->tile->setTileSides(this->displayTile.getTileNorth(), this->displayTile.getTileEast(),
//                             this->displayTile.getTileSouth(),this->displayTile.getTileWest());

    this->tile->setData(this->displayTile.getData());
    this->tile->update();
}

void TileEditDialog::loadClickedTileDataIntoDisplayTile()
{
    if(!tile)
        return;

    this->displayTile = *this->tile;
}

void TileEditDialog::loadNewTile(Tile *t)
{
    this->setTile(t);
    this->loadClickedTileDataIntoDisplayTile();

    this->updateUITileInfoUponInit();
}
