#!/bin/sh

g++ -I/usr/include -I/usr/local/include -I./ImGui -DIMGUI_IMPL_OPENGL_LOADER_GLEW -o App App.cpp Grid.cpp Highlight.cpp ImGui.cpp Object.cpp ObjectManager.cpp Shader.cpp Window.cpp ImGui/imgui.o ImGui/imgui_draw.o ImGui/imgui_widgets.o ImGui/imgui_tables.o ImGui/imgui_impl_glfw.o ImGui/imgui_impl_opengl3.o -lglfw -lGLEW -lGL

./App
