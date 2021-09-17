#ifndef TILEEDITDIALOG_H
#define TILEEDITDIALOG_H

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "tile.h"

namespace Ui {
class TileEditDialog;
}

class TileEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TileEditDialog(QWidget *parent = nullptr);
    explicit TileEditDialog(Tile *t, QWidget *parent = nullptr);
    ~TileEditDialog();

    Tile *getTile() const;
    void setTile(Tile *value);

    void addDisplayTileToScene();

    QGraphicsScene *getScene() const;
    void setScene(QGraphicsScene *value);
    void updateUITileInfoUponInit();

    void loadClickedTileDataIntoDisplayTile();

    void loadNewTile(Tile *t);

private slots:
    void on_tileType_currentIndexChanged(int index);

    void on_comboBoxNorth_currentIndexChanged(int index);
    void on_comboBoxEast_currentIndexChanged(int index);
    void on_comboBoxSouth_currentIndexChanged(int index);
    void on_comboBoxWest_currentIndexChanged(int index);

    void on_telCoordYSpinBox_valueChanged(int arg1);
    void on_telCoordXSpinBox_valueChanged(int arg1);

    void on_doorNorth_currentIndexChanged(int index);
    void on_doorEast_currentIndexChanged(int index);
    void on_doorSouth_currentIndexChanged(int index);
    void on_doorWest_currentIndexChanged(int index);

    void on_misc0_valueChanged(int arg1);
    void on_misc1_valueChanged(int arg1);
    void on_misc2_valueChanged(int arg1);
    void on_misc3_valueChanged(int arg1);
    void on_misc4_valueChanged(int arg1);
    void on_misc5_valueChanged(int arg1);
    void on_misc6_valueChanged(int arg1);
    void on_misc7_valueChanged(int arg1);

    void on_pushUpdate_clicked();

private:
    Ui::TileEditDialog *ui;
    Tile *tile = 0;
    Tile displayTile;
    QGraphicsScene *scene = 0;
};

#endif // TILEEDITDIALOG_H
