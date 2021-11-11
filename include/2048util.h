#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <fstream>
#include <iostream>
#include <cstring>

#include <macros.h>

bool LoadIniFile(const char* path, glm::ivec2* boardSize);

void RenderSettings(glm::ivec2& boardSize, bool& menuOpen);