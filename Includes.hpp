#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Window.hpp"
#include "Shader.hpp"
#include "ImGui.hpp"
#include "Grid.hpp"
#include "Highlight.hpp"
#include "ObjectManager.hpp"


extern Window window;

extern Shader shader;

extern ImGUI imgui;

extern Grid grid;

extern Highlight highlightCell;

extern ObjectManager manager;


GLfloat gridVertices3D[] = {
    // Horizontal lines
    -0.5f,  0.4f, 0.0f, 0.5f,  0.4f, 0.0f,
    -0.5f,  0.3f, 0.0f, 0.5f,  0.3f, 0.0f,
    -0.5f,  0.2f, 0.0f, 0.5f,  0.2f, 0.0f,
    -0.5f,  0.1f, 0.0f, 0.5f,  0.1f, 0.0f,
    -0.5f,  0.0f, 0.0f, 0.5f,  0.0f, 0.0f,
    -0.5f, -0.1f, 0.0f, 0.5f, -0.1f, 0.0f,
    -0.5f, -0.2f, 0.0f, 0.5f, -0.2f, 0.0f,
    -0.5f, -0.3f, 0.0f, 0.5f, -0.3f, 0.0f,
    -0.5f, -0.4f, 0.0f, 0.5f, -0.4f, 0.0f,
    -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f,

    // Vertical lines
    -0.4f,  0.5f, 0.0f, -0.4f, -0.5f, 0.0f,
    -0.3f,  0.5f, 0.0f, -0.3f, -0.5f, 0.0f,
    -0.2f,  0.5f, 0.0f, -0.2f, -0.5f, 0.0f,
    -0.1f,  0.5f, 0.0f, -0.1f, -0.5f, 0.0f,
    0.0f,   0.5f, 0.0f,  0.0f, -0.5f, 0.0f,
    0.1f,   0.5f, 0.0f,  0.1f, -0.5f, 0.0f,
    0.2f,   0.5f, 0.0f,  0.2f, -0.5f, 0.0f,
    0.3f,   0.5f, 0.0f,  0.3f, -0.5f, 0.0f,
    0.4f,   0.5f, 0.0f,  0.4f, -0.5f, 0.0f,
    0.5f,   0.5f, 0.0f,  0.5f, -0.5f, 0.0f,

    // Border lines
    -0.5f,  0.5f, 0.0f, -0.5f, -0.5f, 0.0f,  // Left border
     0.5f,  0.5f, 0.0f,  0.5f, -0.5f, 0.0f,  // Right border
    -0.5f,  0.5f, 0.0f,  0.5f,  0.5f, 0.0f,  // Top border
    -0.5f, -0.5f, 0.0f,  0.5f, -0.5f, 0.0f   // Bottom border
};

    GLfloat gridIndices[] = {
        // Horizontal lines
        0, 1,
        2, 3,
        4, 5,
        6, 7,
        8, 9,
        10, 11,
        12, 13,
        14, 15,
        16, 17,
        // Vertical lines
        18, 19,
        20, 21,
        22, 23,
        24, 25,
        26, 27,
        28, 29,
        30, 31,
        32, 33,
        34, 35,
        36, 37,
        38, 39,
        // Border lines
        40, 41,
        42, 43,
        44, 45,
        46, 47,
        48, 49,
        50, 51,
        52, 53,
        54, 55
    };



    GLfloat cubeIndices[] = {
        // Front face
        0, 1, 2,
        1, 3, 2,

        // Back face
        4, 5, 6,
        5, 7, 6,

        // Left face
        8, 9, 10,
        9, 11, 10,

        // Right face
        12, 13, 14,
        13, 15, 14,

        // Top face
        16, 17, 18,
        17, 19, 18,

        // Bottom face
        20, 21, 22,
        20, 22, 23
    };
