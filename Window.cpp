#include "Window.hpp"

void Window::start()
{
	// Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Set GLFW options
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(WIDTH, HEIGHT, "3D Objects Adder - View Mode", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }
    
    glEnable(GL_DEPTH_TEST);

    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    
    windowPointer = window;
}



void Window::setup()
{

        if(topView)
        {
            projection = glm::mat4(1.0f);
            view = glm::mat4(1.0f);
            model = glm::mat4(1.0f);
        }
        else
        {
            // Set projection matrix
            projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);

            // Set view matrix
            view = glm::lookAt(glm::vec3(0.0f, -1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

            // Set model matrix
            model = glm::mat4(1.0f);
        }
        GLuint projectionLoc = glGetUniformLocation(shaderProgram, "projection");
            glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
        GLuint viewLoc = glGetUniformLocation(shaderProgram, "view");
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        // Set the viewport
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);

        if(topView)
        {
            glfwSetWindowTitle(window, "3D Objects Adder - Edit Mode");
        }
        else
        {
            glfwSetWindowTitle(window, "3D Objects Adder - View Mode");
        }

}






// Just a helper function that does what it says
        float Window::roundToDecimalPlaces(float number, int decimalPlaces) {
            float scale = std::pow(10.0f, decimalPlaces);
                return std::round(number * scale) / scale;
        }

        // Another helper function
// Function to check if two rectangles overlap (touching allowed but not overlapping)
bool Window::doRectanglesOverlap(float x1Left, float x1Right, float y1Bottom, float y1Top,
                         float x2Left, float x2Right, float y2Bottom, float y2Top) {
    // Check if one rectangle is strictly to the left, right, above, or below the other
    if (x1Right <= x2Left || x1Left >= x2Right || y1Top <= y2Bottom || y1Bottom >= y2Top) {
        return false;
    }
    // If none of the above, the rectangles overlap
    return true;
}

// And another helper function. They work hand in hand, by the way.
// Function to check if the space is occupied
bool Window::checkForOccupiedSpace(float xLeft, float xRight, float yBottom, float yTop) {
    
    for (int i = 0; i < manager.getNumObjects(); i++) {
        float objXLeft = objects[i].xLeft;
        float objXRight = objects[i].xRight;
        float objYBottom = objects[i].yBottom;
        float objYTop = objects[i].yTop;

        // Check if the clicked grid square overlaps with any existing object
        if (doRectanglesOverlap(xLeft, xRight, yBottom, yTop, objXLeft, objXRight, objYBottom, objYTop)) {

            // Ma yahasamma aaipugdaa maile click gareko xu, ani kunai object veteko xu

            // So, maile mode check garnu paryo

            if(mode == 0) // I intend to add an object, but the rectangles overlap
            {
                std::cout << "Space is occupied by object at index: " << i << std::endl;
            }

            if(mode == 1 || mode == 2) // I intend to move this object or remove this object, but the rectangles overlap.
                // That simply means that I have successfully selected an object
                // So, I retrieve the id of the object
            {
                selectedObject = i; // I stored the id of the selected object
            }


            return false;
        }
    }
    return true;
}




void Window::cursorCallback(GLFWwindow* window, double xpos, double ypos)
{
	ImGuiIO& io = ImGui::GetIO();
    io.MousePos.x = (float)xpos;
    io.MousePos.y = (float)ypos;


    // If we are not in the top view, then the editing stuffs cannot be done. So, we don't do anything
     if(topView == false)
    {
        return;
    }


    // Get the window size
    int width, height;
    glfwGetWindowSize(window, &width, &height);

    // Convert GLFW coordinates to OpenGL coordinates
    xNorm = (2.0f * xpos / width) - 1.0f;
    yNorm = 1.0f - (2.0f * ypos / height);

    // Grid boundaries
    float minX = -0.5f, maxX = 0.5f, minY = -0.5f, maxY = 0.5f;
    if (xNorm < minX || xNorm > maxX || yNorm < minY || yNorm > maxY) {
        //std::cout << "Cursor is outside the grid boundaries" << std::endl;
        return;
    }

    // If no object is selected, we do nothing
    if(size == -1.0f)
    {
        return;
    }

    // Grid cell size
    float cellWidth = 0.1f, cellHeight = 0.1f;
    // We use the scale variable to change the size of the rectangle according to the object we are selecting
    float scale = size; // Scale factor to cover 2x2 original cells

    // Adjusted cell size with scaling (in terms of number of cells)
    float scaledCellWidth = cellWidth * scale;
    float scaledCellHeight = cellHeight * scale;

    // Determine the row and column of the cursor
    int col = (int)((xNorm - minX) / cellWidth);
    int row = (int)((yNorm - minY) / cellHeight);

    // Ensure col and row are within valid range
    int maxCols = (int)((maxX - minX) / cellWidth);
    int maxRows = (int)((maxY - minY) / cellHeight);

    if (col < 0) col = 0;
    if (col >= maxCols) col = maxCols - 1;
    if (row < 0) row = 0;
    if (row >= maxRows) row = maxRows - 1;

    // Calculate the top-left corner of the scaled cell
    xLeft = minX + col * cellWidth;
    yBottom = minY + row * cellHeight;

    // Clamp the top-left corner to ensure the square is within the grid
    if (xLeft + scaledCellWidth > maxX) {
        xLeft = maxX - scaledCellWidth;
    }
    if (yBottom + scaledCellHeight > maxY) {
        yBottom = maxY - scaledCellHeight;
    }

    // Calculate the coordinates of the scaled cell
    xRight = roundToDecimalPlaces(xLeft + scaledCellWidth, 1);
    yTop = roundToDecimalPlaces(yBottom + scaledCellHeight, 1);
    xLeft = roundToDecimalPlaces(xLeft, 1);
    yBottom = roundToDecimalPlaces(yBottom, 1);


    float rectangleVertices[] = {
        xLeft, yBottom,
        xRight, yBottom,
        xLeft, yTop,
        xRight, yTop
    };

    // Bind the vertex buffer and update its data
    glBindBuffer(GL_ARRAY_BUFFER, highlightedCellVBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(rectangleVertices), rectangleVertices);

}

void Window::setCursorCallback()
{

	// Set the cursor position callback for handling the cursor
    glfwSetCursorPosCallback(window, cursor_position_callback);

}

void Window::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{

    ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {

        // This function also does most of the things the previous function does, and thus can be made better and less redundant

        if(topView == false)
    {
        return;
    }


        // Grid boundaries
    float minX = -0.5f, maxX = 0.5f, minY = -0.5f, maxY = 0.5f;
    if (xNorm < minX || xNorm > maxX || yNorm < minY || yNorm > maxY) {
        //std::cout << "Cursor is outside the grid boundaries" << std::endl;
        return;
    }
    
    if(size == -1.0f)
    {
        return;
    }

    // Grid cell size
    float cellWidth = 0.1f, cellHeight = 0.1f;
    float scale = size; // Scale factor to cover 2x2 original cells

    // Adjusted cell size with scaling (in terms of number of cells)
    float scaledCellWidth = cellWidth * scale;
    float scaledCellHeight = cellHeight * scale;

    // Determine the row and column of the cursor
    int col = (int)((xNorm - minX) / cellWidth);
    int row = (int)((yNorm - minY) / cellHeight);

    // Ensure col and row are within valid range
    int maxCols = (int)((maxX - minX) / cellWidth);
    int maxRows = (int)((maxY - minY) / cellHeight);

    if (col < 0) col = 0;
    if (col >= maxCols) col = maxCols - 1;
    if (row < 0) row = 0;
    if (row >= maxRows) row = maxRows - 1;

    // Calculate the top-left corner of the scaled cell
    xLeft = minX + col * cellWidth;
    yBottom = minY + row * cellHeight;

    // Clamp the top-left corner to ensure the square is within the grid
    if (xLeft + scaledCellWidth > maxX) {
        xLeft = maxX - scaledCellWidth;
    }
    if (yBottom + scaledCellHeight > maxY) {
        yBottom = maxY - scaledCellHeight;
    }

    // Calculate the coordinates of the scaled cell
    xRight = roundToDecimalPlaces(xLeft + scaledCellWidth, 1);
    yTop = roundToDecimalPlaces(yBottom + scaledCellHeight, 1);
    xLeft = roundToDecimalPlaces(xLeft, 1);
    yBottom = roundToDecimalPlaces(yBottom, 1);



    if(checkForOccupiedSpace(xLeft, xRight, yBottom, yTop, objects))
    {
        if(mode == 0) // If I intend to add an object, I add the object
        {
            manager.addObject(xLeft, xRight, yBottom, yTop, size);

            if(wasMoved == true)
            {
                mode = 1;
                wasMoved = false;
            }
        }
        
    }else
    {
        if(manager.noObjects()) // If I don't intend to add the object, but have selected the object, and if there are no objects
            // This can break the program and thus we exit without doing anything
    {
        return;
    }

    if(mode == 1)  // I intend to move this object
    {
        // Moving the object just means first removing the object
        float sizeOfObject = manager.getSizeOfObject(selectedObject);
        manager.removeObject(selectedObject);

        // Then setting the mode to add the object, so that the same object will be added somewhere else
        mode = 0;
        size = sizeOfObject;
        wasMoved = true;
    }

    if(mode == 2) // I intend to remove this object
    {
        manager.removeObject(selectedObject);
    }
    }



    }
}

void Window::setMouseButtonCallback()
{
	// Set the mouse button callback
    glfwSetMouseButtonCallback(window, mouse_button_callback);

}



bool Window::isActive()
{
    return !(glfwWindowShouldClose(window));
}




void Window::clearColor()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
}



void Window::clearBuffer()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
}



void Window::swapBuffers()
{
    // Swap front and back buffers
    glfwSwapBuffers(windowPointer);

    // Poll for and process events
        glfwPollEvents();
}



int Window::getMode()
{
    return mode;
}


bool isTopView()
{
    return topView;
}

