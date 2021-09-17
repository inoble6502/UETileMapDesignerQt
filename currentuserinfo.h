#ifndef CURRENTUSERINFO_H
#define CURRENTUSERINFO_H

#include <QObject>
#include "tile.h"

class CurrentUserInfo : public QObject
{
    Q_OBJECT
public:
    explicit CurrentUserInfo(QObject *parent = nullptr);
    explicit CurrentUserInfo(Tile *t, QObject *parent = nullptr);

    Tile *getSelectedTile() const;
    void setSelectedTile(Tile *value);

signals:
    void tileSelectionChanged(Tile *t);

public slots:
    void updateClickedTile(Tile *t);
    void updateUserSelectedTile(Tile *t);

private:
    Tile *selectedTile = 0;
};

#endif // CURRENTUSERINFO_H
