#pragma once

#include "renderer.h"
#include "stb_image.h"

#include <array>
#include <vector>

static constexpr size_t MaxQuadCount = 1000;
static constexpr size_t MaxVertexCount = MaxQuadCount * 4;
static constexpr size_t MaxIndexCount = MaxQuadCount * 6;

static constexpr size_t MaxTextureCount = 32;


struct Vertex
{
    glm::vec2 position;
	glm::vec2 texCoord;
    float textureIndex;
};

struct RendererData
{
    size_t QuadCount = 0;

    size_t VertexCount = 0;
    Vertex verticies[MaxVertexCount];

    uint32_t VAO;
    uint32_t VBO;
    uint32_t IBO;

    std::vector<uint32_t> textures;
};

static std::array<Vertex, 4> CreateQuad(const glm::vec2& pos, const glm::vec2& size, float textureIndex)
{
	std::array<Vertex, 4> verticies;
	verticies[0].position = {pos.x - size.x / 2, pos.y - size.y / 2};
	verticies[0].textureIndex = textureIndex;
	verticies[0].texCoord = {0.0f, 0.0f};

	verticies[1].position = {pos.x + size.x / 2, pos.y - size.y / 2};
	verticies[1].textureIndex = textureIndex;
	verticies[1].texCoord = {1.0f, 0.0f};

	verticies[2].position = {pos.x + size.x / 2, pos.y + size.y / 2};
	verticies[2].textureIndex = textureIndex;
	verticies[2].texCoord = {1.0f, 1.0f};

	verticies[3].position = {pos.x - size.x / 2, pos.y + size.y / 2};
	verticies[3].textureIndex = textureIndex;
	verticies[3].texCoord = {0.0f, 1.0f};

	return verticies;
}

static uint32_t LoadTexture(const char* filepath)
{
    stbi_set_flip_vertically_on_load(true);

	int x, y, bits;
	unsigned char* buffer = stbi_load(filepath, &x, &y, &bits, 4);

	if (buffer == nullptr)
		return 0;

	unsigned int id = -1;
	glGenTextures(1, &id);
	

	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);

	if (buffer != nullptr)
		stbi_image_free(buffer);

	return id;
}

