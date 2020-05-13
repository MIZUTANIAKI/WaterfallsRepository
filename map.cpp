#include <DxLib.h>
#include "scene/SceneMng.h"
#include "map.h"

Map* Map::sInstance = nullptr;

void Map::Update(void)
{
	lpSceneMng.AddDrawQuenex(mapmodel);	//�`��v��
}

Map::Map()
{
	mapmodel = MV1LoadModel("mv/men.mv1");
	MV1SetPosition(mapmodel, VGet(0.0f, 0.0f, 0.0f));	//���W�ύX

	MV1SetOpacityRate(mapmodel, 0.5f);
}

Map::~Map()
{
}
