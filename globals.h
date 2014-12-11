#ifndef GLOBALS_H
#define GLOBALS_H

namespace Defender {

const int worldUnitWidth = 2;
const int unitWidth = 1024;

const int windowHeight = 512;
constexpr int windowWidth = windowHeight * 16 / 9;

constexpr int worldHeight = windowHeight;
constexpr int worldWidth = unitWidth * worldUnitWidth;

}

#endif // GLOBALS_H
