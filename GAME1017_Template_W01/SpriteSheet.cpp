#include "SpriteSheet.h"
#include "TextureManager.h"
#include <fstream>
#include <string>
#include <vector>

SpriteSheet::SpriteSheet(std::string text, const char* path, std::string key) : text(text), path(path), key(key)
{
	TEMA::RegisterTexture(path, key);
	loadText();
}

void SpriteSheet::loadText()
{
    std::string line;
    std::ifstream myfile(text);
	std::string delimeter = " ";

    std::string name;
    int x, y, w, h;

    if (myfile.is_open())
    {
		while (std::getline(myfile, line))
		{
			size_t linePosition = 0;
			std::vector<std::string> tokens;

			for (auto i = 0; i < 5; ++i)
			{
				linePosition = line.find(delimeter);
				tokens.push_back(line.substr(0, linePosition));
				line.erase(0, linePosition + 1);
			}

			
			name = tokens[0];
			x = std::stoi(tokens[1]);
			y = std::stoi(tokens[2]);
			w = std::stoi(tokens[3]);
			h = std::stoi(tokens[4]);

			// add the new frame to the spritesheet
			addFrame(new Frame(name, x, y, w, h));
		}
        myfile.close();
    }

}

void SpriteSheet::addFrame(Frame* frame)
{
	framesOnSpriteSheet[frame->m_name] =frame;
}
