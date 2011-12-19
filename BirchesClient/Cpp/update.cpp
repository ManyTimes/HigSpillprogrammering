#include "../Header/update.h"


void Update()
{
	for(int i = 0; i < MAXIMUMPLAYERS; i++)
	{
		if(player[i].ID > -1)		//ID must be set
		{
			projectileArc[i].Move(0.075);
		}
	}
	if(projectileArc)
	{
		projectileArc[0].GetPosition().Cout();
		unit[0].GetPosition().Cout();
	}
}