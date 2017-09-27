#include "finder.h"

Keeper::Keeper(QObject *parent) : QObject(parent), high_(0), width_(0), count_(0)
{

}

void Keeper::clearAll()
{
    high_ = 0;
    width_ = 0;
    count_ = 0;
    blocks.clear();
    way.clear();
}



Finder::Finder(Keeper *keeper, QObject *parent) : QObject(parent), keeper_(keeper)
{

}



CreatorRec::CreatorRec(Keeper *keeper, QObject *parent) : QObject(parent), keeper_(keeper)
{

}
