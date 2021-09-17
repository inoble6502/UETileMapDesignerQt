#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tileselectionarea.h"
#include "dungeonlayoutscene.h"
#include "currentuserinfo.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void connectSignalsAndSlots();

private slots:
    void on_actionSave_as_CSV_triggered();
    void on_actionExit_triggered();
    void on_actionSet_All_to_Blank_triggered();
    void on_actionSet_All_to_Null_triggered();
    void on_actionSet_to_Blank_with_Walls_triggered();

    void on_actionUndo_triggered();
    void on_actionRedo_triggered();

    void setBasicTileInfoUponSelection(Tile *t);

    void on_pushSaveCSV_clicked();
    void on_pushBlank_clicked();
    void on_pushNull_clicked();
    void on_pushWall_clicked();
    void on_actionAdd_Tile_to_Selection_Grid_triggered();
    void on_actionRemove_Last_Tile_From_Selection_Grid_triggered();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_actionSave_as_PNG_triggered();

    void on_actionSave_as_CSV_and_PNG_triggered();

private:
    Ui::MainWindow *ui;

    TileSelectionArea *ts = 0;
    DungeonLayoutScene *ds = 0;
    CurrentUserInfo *userInfo = 0;
};
#endif // MAINWINDOW_H
