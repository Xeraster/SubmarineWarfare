#ifndef GARBAGECOLLECTION_H
#define GARBAGECOLLECTION_H

bool deletePlayerTorpedo();

void deletePlayerTorpedos();

bool deleteTorpedosNotify = false;

extern playerInfo *playerCampaignInfo;
extern bool showPurchaseScreen;

#include "garbageCollection.hpp"
#endif
