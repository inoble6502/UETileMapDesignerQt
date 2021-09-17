#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tileadd.h"
#include <QGraphicsScene>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    initTileSidePixmaps();
    initTileTypePixmaps();

    ts = new TileSelectionArea();
    ui->tsView->setScene(ts);

    this->ds = new DungeonLayoutScene(DungeonLayoutScene::DUNGEON_WALLED_BLANK);
    ui->editorView->setScene(ds);
    ui->editorView->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    this->userInfo = new CurrentUserInfo();

    this->connectSignalsAndSlots();
}

MainWindow::~MainWindow()
{
    deleteTilePixmaps();
    delete userInfo;
    delete ts;
    delete ds;
    delete ui;
}

void MainWindow::connectSignalsAndSlots()
{
    if(!(this->ts && this->ds && this->userInfo))
        return;

    connect(this->ts, &TileSelectionArea::leftClicked,
            this->userInfo, &CurrentUserInfo::updateUserSelectedTile);

    connect(this->ds, &DungeonLayoutScene::DungeonLayoutSceneTileClicked,
            this->userInfo, &CurrentUserInfo::updateClickedTile);

    connect(this->userInfo, &CurrentUserInfo::tileSelectionChanged,
            this, &MainWindow::setBasicTileInfoUponSelection);
}


void MainWindow::on_actionSave_as_CSV_triggered()
{
    if(!this->ds)
        return;

    this->ds->saveDungeonLayoutDataToCSV();
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionSet_All_to_Blank_triggered()
{
    if(!ds)
        return;

    ds->initDungeonWithBlankTiles();
}

void MainWindow::on_actionSet_All_to_Null_triggered()
{
    if(!ds)
        return;

    ds->initDungeonWithNullTiles();
}

void MainWindow::on_actionSet_to_Blank_with_Walls_triggered()
{
    if(!ds)
        return;

    ds->initWalledDungeonWithBlankTiles();
}

void MainWindow::on_actionUndo_triggered()
{
    this->ds->decrementHistIndexAndRevert();
}

void MainWindow::on_actionRedo_triggered()
{
    if(!this->ds->getActionHistory().historySize())
        return;

    if(!this->ds->getActionHistory().getCountofIndex(this->ds->getActionHistory().getCurrentHistoryIndex()))
        return;

    this->ds->incrementHistIndexAndRevert();
    this->ds->getActionHistory().printCurrentIndex();
}

void MainWindow::setBasicTileInfoUponSelection(Tile *t)
{
    ui->sType->setText(QString::number(t->getTileType()));
    ui->sNorth->setText(QString::number(t->getTileNorth()));
    ui->sEast->setText(QString::number(t->getTileEast()));
    ui->sSouth->setText(QString::number(t->getTileSouth()));
    ui->sWest->setText(QString::number(t->getTileWest()));
}

void MainWindow::on_pushSaveCSV_clicked()
{
    if(!this->ds)
        return;

    this->ds->saveDungeonLayoutDataToCSV();
}

void MainWindow::on_pushBlank_clicked()
{
    if(!ds)
        return;

    ds->initDungeonWithBlankTiles();
}


void MainWindow::on_pushNull_clicked()
{
    if(!ds)
        return;

    ds->initDungeonWithNullTiles();
}

void MainWindow::on_pushWall_clicked()
{
    if(!ds)
        return;

    ds->initWalledDungeonWithBlankTiles();
}

void MainWindow::on_actionAdd_Tile_to_Selection_Grid_triggered()
{
    if(!ts)
        return;

    tileadd *ta = new tileadd(this->ts);
    ta->setAttribute(Qt::WA_DeleteOnClose);
    ta->show();
}

void MainWindow::on_actionRemove_Last_Tile_From_Selection_Grid_triggered()
{
    this->ts->removeLastTileFromVecAndScene();
}

void MainWindow::on_pushButton_clicked()
{
    this->on_actionAdd_Tile_to_Selection_Grid_triggered();
}

void MainWindow::on_pushButton_2_clicked()
{
    this->on_actionRemove_Last_Tile_From_Selection_Grid_triggered();
}

void MainWindow::on_actionSave_as_PNG_triggered()
{
    QString f = QFileDialog::getSaveFileName(nullptr, "Save as PNG", ".", "PNG (*.png)");

    QPixmap p = ui->editorView->grab(ui->editorView->sceneRect().toRect());
    p.save(f);
}

void MainWindow::on_actionSave_as_CSV_and_PNG_triggered()
{
    QString f = QFileDialog::getSaveFileName(nullptr, "Save as CSV and PNG", ".", "");

    this->ds->saveDungeonLayoutDataToCSV(f);
    QPixmap p = ui->editorView->grab(ui->editorView->sceneRect().toRect());
    p.save(f + ".png");

}
