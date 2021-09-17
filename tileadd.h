#ifndef TILEADD_H
#define TILEADD_H

#include <QDialog>
#include "tileselectionarea.h"
#include <QVector>

namespace Ui {
class tileadd;
}

class tileadd : public QDialog
{
    Q_OBJECT

public:
    explicit tileadd(QWidget *parent = nullptr);
    explicit tileadd(TileSelectionArea *t, QWidget *parent = nullptr);
    ~tileadd();

    void addDisplayTileToScene();

    QGraphicsScene *getScene() const;
    void setScene(QGraphicsScene *value);
    void updateUITileInfoUponInit();

    void loadClickedTileDataIntoDisplayTile();

private slots:
    void on_tileType_currentIndexChanged(int index);

    void on_comboBoxNorth_currentIndexChanged(int index);
    void on_comboBoxEast_currentIndexChanged(int index);
    void on_comboBoxSouth_currentIndexChanged(int index);
    void on_comboBoxWest_currentIndexChanged(int index);

    void on_pushUpdate_clicked();

private:
    Ui::tileadd *ui;

    TileSelectionArea *area;
    Tile displayTile;
    QGraphicsScene *scene = 0;
};

#endif // TILEADD_H
