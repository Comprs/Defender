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
}

#endif // GLOBALS_H
