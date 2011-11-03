#ifndef _WEATHER_H
#define _WEATHER_H

#include "include.h"
#include "mouse.h"
#include "includegl.h"
#include "mathtool.h"
#include "terrain.h"

namespace cgl
{
	enum WeatherType { SNOW, RAIN };

	struct DECLARE Particle
	{
		public:
		int state;					//Dead, Active, Splash (0, 1, 2)
		float splashspan;			//Time a particle draws a "splash texture" while at ground
		float position[3];			//Position X Y Z
		float velocity[3];			// Velocity X, Y, Z
	};

	class DECLARE Weather
	{
	private:

		float particleSize;
		float splashSize;
		float incrementsize;
		float incrementsize2;
		float RGB[3];	
		float* WINDRANDOM;
		float maxsplashspan;
		int maxparticles;
		int nextparticle;
		GLuint textureID;
		GLuint splashTextureID;
		Particle* particles;
		cgl::Terrain* terrain;		//Draws splash effect on a heightmap through GetHeight[x][z]
		void Weather::Move();
	public:
		WeatherType type;
		float WindFactor;
		Weather::Weather(float RGBcolors[3], int MaximumParticles, float SplashLifeSpan);
		void Weather::SetTextures(GLuint textureID);
		void Weather::SetTextures(GLuint textureID, GLuint splashTextureID);
		void Weather::StartOneParticle(float particleVelocity[3], float startPosition[3]);
		void Weather::Draw();
	};
}

#endif