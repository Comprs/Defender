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

const int playerParticleCount = 200;

const double abductorSpeed = 100;
const double abductorSpeedPortion = 1.0;
constexpr double abductingSpeed = abductorSpeed * abductorSpeedPortion;
const int abductorScore = 1;

const double alienProjectileFireRange = 500;
const double alienProjectileSpeed = 16;
const double alienProjectileLifeTime = 2;

const double fighterSpeed = 600;
const int fighterScore = 1;

const int initialManCount = 20;
const double manFallSpeed = abductorSpeed * 3/2;
const int manScoreDeduction = -2;
const int manParticleCount = 10;

const double mutantSpeed = 1000;
const int mutantScore = 2;

const int bombScore = 20;
constexpr int firstBombScore = bombScore;
}

#endif // GLOBALS_H
