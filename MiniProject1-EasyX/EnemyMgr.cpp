#include "stdafx.h"
#include "EnemyMgr.h"

extern Camera G_Camera;

EnemyMgr::EnemyMgr()
{

}

void EnemyMgr::Update()
{
	for (auto it = Goombas.begin(); it != Goombas.end();)
	{
		if ((it->GetXPositiion() - G_Camera.GetWorldXPosition()) <= 256)
		{
			it->Spawn = true;
		}
		if (it->Spawn)
		{
			it->Update();
			if (it->GetYPosition() > 300)
			{
				it = Goombas.erase(it);
			}
			else
			{
				it++;
			}
		}
		else
		{
			it++;
		}
	}
	for (auto it = KoopaTroopas.begin(); it != KoopaTroopas.end();)
	{
		if ((it->GetXPositiion() - G_Camera.GetWorldXPosition()) <= 256)
		{
			it->Spawn = true;
		}
		if (it->Spawn)
		{
			it->Update();
			if (it->GetYPosition() > 300)
			{
				it = KoopaTroopas.erase(it);
			}
			else
			{
				it++;
			}
		}
		else
		{
			it++;
		}
	}
	for (auto it = PiranhaPlants.begin(); it != PiranhaPlants.end();)
	{
		if ((it->GetXPositiion() - G_Camera.GetWorldXPosition()) <= 256)
		{
			it->Spawn = true;
		}
		if (it->Spawn)
		{
			it->Update();
			if (it->GetYPosition() > 300)
			{
				it = PiranhaPlants.erase(it);
			}
			else
			{
				it++;
			}
		}
		else
		{
			it++;
		}
	}
}

void EnemyMgr::Render()
{
	for (int i = 0; i < Goombas.size(); i++)
	{
		Goombas[i].Render();
	}
	for (int i = 0; i < KoopaTroopas.size(); i++)
	{
		KoopaTroopas[i].Render();
	}
	for (int i = 0; i < PiranhaPlants.size(); i++)
	{
		PiranhaPlants[i].Render();
	}
}

