#pragma once
#define GLFW_INCLUDE_VULKAN
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <functional>
#include <cstdlib>
#include <map>
#include <set>
#include <cstdint>
#include <algorithm>
#include <fstream>
#include <vector>
#include <optional>
#include <array>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <chrono>

struct Vertex
{
    glm::vec3 pos;
    glm::vec3 color;
    glm::vec2 texCoord;

    static auto getBindingDescription()
    {
        VkVertexInputBindingDescription bindingDescription;
        bindingDescription.binding = 0;
        bindingDescription.stride = sizeof(Vertex);
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
        return bindingDescription;
    }

    static auto getAttributeDescriptions()
    {
        std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions;

        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[0].offset = offsetof(Vertex, pos);

        attributeDescriptions[1].binding = 0;
        attributeDescriptions[1].location = 1;
        attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[1].offset = offsetof(Vertex, color);

        attributeDescriptions[2].binding = 0;
        attributeDescriptions[2].location = 2;
        attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
        attributeDescriptions[2].offset = offsetof(Vertex, texCoord);

        return attributeDescriptions;
    }
};

struct UniformBufferObject
{
    alignas(16) glm::mat4 model;
    alignas(16) glm::mat4 view;
    alignas(16) glm::mat4 proj;
};

constexpr uint8_t planeVertices = 4;
constexpr uint8_t planeIndices = 6;

constexpr uint8_t cubeVertices = 8;
constexpr uint8_t cubeIndices = 36;

const std::vector<Vertex> vertices = {
    {{0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
    {{1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
    {{1.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
    {{0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},

    {{0.0f, 0.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
    {{1.0f, 0.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
    {{1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
    {{0.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
};

const std::vector<uint16_t> indices = {
    0, 1, 2, 2, 3, 0,
    5, 4, 7, 7, 6, 5,
    1, 5, 6, 6, 2, 1,
    4, 0, 3, 3, 7, 4,
    3, 2, 6, 6, 7, 3,
    4, 5, 1, 1, 0, 4
};

