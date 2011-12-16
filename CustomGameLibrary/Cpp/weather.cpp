#include "../Header/weather.h"

namespace cgl
{
	//Private moving of the weather, called automatically when you call Draw();
	void Weather::Move()
	{
		for(int i = 0; i < this->maxparticles; i++)
		{
			if(particles[i].state == 1)			//Active
			{
				particles[i].position[0] += particles[i].velocity[0];
				particles[i].position[1] += particles[i].velocity[1];
				particles[i].position[2] += particles[i].velocity[2];
				if(particles[i].position[1] <= 0.0f)
				{
					particles[i].state = 2;
					particles[i].splashspan = 0;
					particles[i].velocity[0] = particles[i].velocity[1] = particles[i].velocity[2] = 0.0f;
				}
			}
			else
			{
				if(particles[i].state == 2)			//Splash
				{
					particles[i].splashspan += 0.10;
					if(particles[i].splashspan > 3)
					{
						particles[i].state = 0;		//Dead
					}
				}
			}
		}
	}

	//Constructor takes color of the particles, maximum amount allowed and a Splash life span (how long it lives when it has reached ground)
	Weather::Weather(float RGBColors[3], int maximumParticles, float SplashLifespan)
	{
		this->splashSize = 0.30f;
		this->particleSize = 0.15f;
		this->type = SNOW;
		this->WindFactor = 0.0f;
		this->textureID = NULL;
		this->splashTextureID = NULL;
		this->maxparticles = maximumParticles;
		this->maxsplashspan = SplashLifespan;
		this->nextparticle = 0;
		this->incrementsize = 150.0f;
		this->incrementsize2 = 150.0f;
		float temp[6];
		for(int i = 0; i < 6; i++)
		{
			temp[i] = RANDOMFLOAT(-0.02, 0.02) - this->WindFactor;
		}
		this->WINDRANDOM = temp;
		particles = new Particle[maximumParticles];
		for(int i = 0; i < 3; i ++)
		{
			this->RGB[i] = RGBColors[i];
		}
		for(int i = 0; i < this->maxparticles; i++)
		{
			this->particles[i].state = 0;				//Dead to begin with
		}
	}

	//Sets a texture of the particles/weather, usually snow texture/rain
	void Weather::SetTextures(GLuint textureID)
	{
		this->textureID = textureID;
	}

	//First is texture of the weather while in air, other is a texture being drawn when particle has hit the ground
	void Weather::SetTextures(GLuint textureID, GLuint splashTextureID)
	{
		this->textureID = textureID;
		this->splashTextureID = splashTextureID;
	}

	//Draws the weather using GL_TEXTURE_2D with GL_TRIANGLE_STRIP, for all started -not dead- particles
	void Weather::Draw()
	{
		glPushMatrix();
		glEnable(GL_DEPTH_TEST);			//Make GL draw objects behind see-through objects
		glEnable(GL_BLEND);					//Blending ON
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		glColor3f(this->RGB[0], this->RGB[1], this->RGB[2]);			//DRAWS WEATHER RAIN
		if(this->type == SNOW)									//DRAWING SNOW PARTICLES
		{
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, this->textureID); 
			for(int i = 0; i < this->maxparticles; i++)
			{
				if(particles[i].state == 1)
				{
					glBegin(GL_TRIANGLE_STRIP);
							glTexCoord2i(0, 0);	
							glVertex3f(particles[i].position[0], particles[i].position[1], particles[i].position[2]);
							
							glTexCoord2i(1, 0);
							glVertex3f(particles[i].position[0] + particleSize, particles[i].position[1], particles[i].position[2]);
								
							glTexCoord2i(0, 1);
							glVertex3f(particles[i].position[0], particles[i].position[1] + particleSize,  particles[i].position[2]);
							
							glTexCoord2i(1, 1);
							glVertex3f(particles[i].position[0] + particleSize, particles[i].position[1] + particleSize, particles[i].position[2]);
							
					glEnd();
				}
			}
		}
		else
		{
			for(int i = 0; i < this->maxparticles; i++)					//Drawing rain drop particles
			{
				if(particles[i].state == 1)
				{
					glColor3f(0.4, 0.4,0.4);
					glBegin(GL_LINES);
						glVertex3fv(particles[i].position);
						glVertex3f(particles[i].position[0] + particles[i].velocity[0],
							particles[i].position[1] - (particles[i].velocity[1]/4),
							particles[i].position[2] - particles[i].velocity[2]);
					glEnd();
				}
			}
		}
		if(this->maxsplashspan > 0.1f)									//If a splash span has been added, then we draw splash effect on ground
		{		
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, this->splashTextureID);
			if(this->terrain == NULL)									//Drawing upon a terrain, instead of a flat map
			{
				for(int i = 0; i < this->maxparticles; i++)
				{
					if(particles[i].state == 2)							//Draw splash
					{
						glBegin(GL_TRIANGLE_STRIP);
							glBindTexture(GL_TEXTURE_2D, textureID);
						
							glTexCoord2i(0, 0);
							glVertex3f(particles[i].position[0],  0.01, particles[i].position[2]);
							
							glTexCoord2i(1, 0);
							glVertex3f(particles[i].position[0] + this->splashSize,  0.01, particles[i].position[2]);
								
							glTexCoord2i(0, 1);
							glVertex3f(particles[i].position[0], 0.01, particles[i].position[2] + this->splashSize);
							
							glTexCoord2i(1, 1);
							glVertex3f(particles[i].position[0] + this->splashSize , 0.01, particles[i].position[2] + this->splashSize);
						glEnd();
					}
				}
			}
			else
			{
				for(int i = 0; i < this->maxparticles; i++)				//Drawing splash, but takes Y value (height) from terrain->Heights[x][z]
				{
					if(particles[i].state == 2)				
					{
						glBegin(GL_TRIANGLE_STRIP);
							glBindTexture(GL_TEXTURE_2D, textureID);
						
							glTexCoord2i(0, 0);
							glVertex3f(particles[i].position[0],  0.01, particles[i].position[2]);
							
							glTexCoord2i(1, 0);
							glVertex3f(particles[i].position[0] + this->splashSize,  0.01, particles[i].position[2]);
								
							glTexCoord2i(0, 1);
							glVertex3f(particles[i].position[0], 0.01, particles[i].position[2] + this->splashSize);
							
							glTexCoord2i(1, 1);
							glVertex3f(particles[i].position[0] + this->splashSize , 0.01, particles[i].position[2] + this->splashSize);
						glEnd();
					}
				}
			}
		}
		glDisable(GL_TEXTURE_2D);
		//glDisable(GL_DEPTH_TEST);			//Make GL draw objects behind see-through objects
		glDisable(GL_BLEND);					//Blending ON
		this->Move();
		glPopMatrix();
	}

	//Starts one particle from the sky, letting it fall down automatically when you call Draw() unless max limit has been reached
	void Weather::StartOneParticle(float particleVelocity[3], float startPosition[3])
	{			
		this->nextparticle = -1;
		for(int i = 0; i < this->maxparticles; i++)	//Find a free among particles allows by the user
		{											//cannot exceed "MAXPARTICLES" though...
			if(particles[i].state == 0)
			{
				this->nextparticle = i;				//Found a dead particle, resurrect it!
				i = this->nextparticle;				//Exit loop
				for(int i = 0; i < 3; i++)
				{
					particles[this->nextparticle].position[i] = 0.0f;
					particles[this->nextparticle].velocity[i] = 0.0f;
				}
			}
		}
		if(this->nextparticle > -1)
		{
			particles[this->nextparticle].state = 1;		//Active particle
			particles[this->nextparticle].splashspan = 0;
			for(int i = 0; i < 3; i++)
			{
				particles[this->nextparticle].position[i] = startPosition[i]; 
				particles[this->nextparticle].velocity[i] = particleVelocity[i];
			}
		}
	}
	

}