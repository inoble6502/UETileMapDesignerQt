#include "tileadd.h"
#include "ui_tileadd.h"
#include <iostream>

tileadd::tileadd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tileadd)
{
    ui->setupUi(this);

    this->scene = new QGraphicsScene();

    ui->graphicsView->setScene(scene);
    this->displayTile.makeTileBlank();
    this->addDisplayTileToScene();
}

tileadd::tileadd(TileSelectionArea *t, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tileadd)
{
    ui->setupUi(this);

    this->area = t;

    this->scene = new QGraphicsScene();

    ui->graphicsView->setScene(scene);
    this->displayTile.makeTileNull();
    this->addDisplayTileToScene();
}

tileadd::~tileadd()
{
    delete ui;
}

void tileadd::addDisplayTileToScene()
{
    if(!this->scene)
        return;

    this->scene->addItem(&this->displayTile);
}

void tileadd::setScene(QGraphicsScene *value)
{
    this->scene = value;
}

void tileadd::updateUITileInfoUponInit()
{
    ui->tileType->setCurrentIndex(this->displayTile.getTileType());

    ui->comboBoxNorth->setCurrentIndex(this->displayTile.getTileNorth());
    ui->comboBoxEast->setCurrentIndex(this->displayTile.getTileEast());
    ui->comboBoxSouth->setCurrentIndex(this->displayTile.getTileSouth());
    ui->comboBoxWest->setCurrentIndex(this->displayTile.getTileWest());
}

void tileadd::on_tileType_currentIndexChanged(int index)
{
    if(index > -1)
        this->displayTile.setTileType(index);

    this->displayTile.update();
}

void tileadd::on_comboBoxNorth_currentIndexChanged(int index)
{
    if(index > -1)
        this->displayTile.setTileNorth(index);

    this->displayTile.update();
}

void tileadd::on_comboBoxEast_currentIndexChanged(int index)
{
    if(index > -1)
        this->displayTile.setTileEast(index);

    this->displayTile.update();
}

void tileadd::on_comboBoxSouth_currentIndexChanged(int index)
{
    if(index > -1)
        this->displayTile.setTileSouth(index);

    this->displayTile.update();
}

void tileadd::on_comboBoxWest_currentIndexChanged(int index)
{
    if(index > -1)
        this->displayTile.setTileWest(index);

    this->displayTile.update();
}

void tileadd::on_pushUpdate_clicked()
{
    if(!this->area)
        return;

    uint8_t t;
    uint8_t n, e, s, w;

    t = this->displayTile.getTileType();
    n = this->displayTile.getTileNorth();
    e = this->displayTile.getTileEast();
    s = this->displayTile.getTileSouth();
    w = this->displayTile.getTileWest();
    this->area->appendTileToVectAndScene(n, e, s, w, t);
}
