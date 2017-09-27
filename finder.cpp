#include "finder.h"

Keeper::Keeper(QObject *parent) : QObject(parent), count_(0), startWay_(0, 0), endWay_(0, 0)
{

}

void Keeper::clearAll()
{
    blocks.clear();
    way.clear();
}

bool Keeper::setRectField(const QRect &rect)
{

}

bool Keeper::setRectBlocks(const QRect &rect)
{

}

bool Keeper::setCountBlocks(int count)
{

}

bool Keeper::setStartEndWay(const QPoint &pointStart, const QPoint &pointEnd)
{

}



Finder::Finder(Keeper *keeper, QObject *parent) : QObject(parent), keeper_(keeper)
{

}

void Finder::findWay()
{

}



CreatorRec::CreatorRec(Keeper *keeper, QObject *parent) : QObject(parent), keeper_(keeper)
{

}

void CreatorRec::generateBlocks()
{

}
