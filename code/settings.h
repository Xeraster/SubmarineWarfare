#ifndef SETTINGS_H
#define SETTINGS_H

//finally, global screen resolution variables
int gscreenx = 800;
int gscreeny = 600;
int menu_quality = 0;
int graphics_quality = 0;

const int minResX = 640;
const int minResY = 400;

void loadSettingsFile(string filePath);

#include "settings.hpp"
#endif