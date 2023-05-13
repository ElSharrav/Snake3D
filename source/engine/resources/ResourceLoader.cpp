#pragma once

#include "ResourceLoader.h"

#include "ResourceManager.h"



ResourceLoader::ResourceLoader()
{
	
}


void ResourceLoader::loadResources()
{
    try
    {
        ResourceManager::loadFont("resources/fonts/arial.ttf" , 48 , Fonts::MAIN_FONT);

        ResourceManager::loadShader("resources/shaders/text/textShader.vs", "resources/shaders/text/textShader.fs", Shaders::TEXT_SHADER);
        
    }
    catch (TextureNotFoundException & e)
    {
        exit( EXIT_FAILURE);
    }
}