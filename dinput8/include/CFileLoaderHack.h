#pragma once

class CFileLoaderHack
{
public:
	static bool initialise();

	static void LoadPedPathNode(const char *line, int modelId, int nodeNum);
	static void LoadObjectTypesHack();
};
