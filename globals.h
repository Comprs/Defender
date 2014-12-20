#ifndef GLOBALS_H
#define GLOBALS_H

namespace Defender {

const int worldUnitWidth = 4;
const int unitWidth = 1024;

const int worldHeight = 512;
constexpr int worldWidth = unitWidth * worldUnitWidth;

constexpr int radarHeight = worldHeight / 3.5;

constexpr int windowHeight = radarHeight + worldHeight;
constexpr int windowWidth = windowHeight * 16/9;

constexpr int radarWidth = windowWidth;

const double resistiveAcceleration = 3000;
const double normalAcceleration = 1000;
const double passiveSlowdown = 100;
const double terminalVelocity = 3000;

const double verticalSpeed = 500;

constexpr double shotSpeed = terminalVelocity * 1.5;
}

#endif // GLOBALS_H
