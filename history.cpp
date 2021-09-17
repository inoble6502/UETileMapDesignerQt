#include "history.h"
#include <iostream>

History::History()
{
    this->setCurrentHistoryIndex(0);
    this->historyMap.clear();
}

History::History(int i)
{
    this->setCurrentHistoryIndex(i);
}

void History::clearHistory()
{
    this->historyMap.clear();
}

int History::historySize()
{
    return this->historyMap.size();
}

void History::revertHistoryTileAtIndex(int index)
{
    if(this->historyMap.empty())
        return;

    if(!this->historyMap.count(index))
        return;

    QMap<int, HistoryTile>::iterator i = this->historyMap.find(index);
    while(i != this->historyMap.end() && i.key() == index)
    {
        i.value().applyPreviousDataToTile();
        ++i;
    }
}

void History::revertHistoryTilesAtCurrentIndex()
{
    this->revertHistoryTileAtIndex(this->getCurrentHistoryIndex());
}

int History::getCurrentHistoryIndex() const
{
    return currentHistoryIndex;
}

void History::setCurrentHistoryIndex(int value)
{
    currentHistoryIndex = value;
}

void History::decrementHistoryIndex()
{
    if(this->getCurrentHistoryIndex() < 1)
        return;

    this->currentHistoryIndex--;
}

void History::incrementHistoryIndex()
{
    this->currentHistoryIndex++;
}

void History::printCurrentIndex()
{
    std::cout << "Current History Index: " <<
                 this->currentHistoryIndex << std::endl;
}

void History::addTileToHistoryMap(Tile *t)
{
    this->historyMap.insert(this->currentHistoryIndex, HistoryTile(t));
}

void History::addTileToHistoryMap(Tile *t, TileData d)
{
    this->historyMap.insert(this->currentHistoryIndex, HistoryTile(t, d));
}

int History::getCountofIndex(int i)
{
    return this->historyMap.count(i);
}


