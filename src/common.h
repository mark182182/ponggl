#ifndef COMMON_H
#define COMMON_H
#pragma comment(lib, "rpcrt4.lib") 

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <windows.h>

const char *WINDOW_NAME = "PongGL";
GLFWwindow *window;
int WINDOW_HEIGHT = 720;
int WINDOW_WIDTH = 1280;
float deltaTime = 0.0f;
float lastFrame = 0.0f;

std::string gen_uuid() {
  UUID uuid;
  UuidCreate(&uuid);
  char *str;
  UuidToStringA(&uuid, (RPC_CSTR*)&str);
  std::string uuidStr = str;
  RpcStringFreeA((RPC_CSTR*)&str);
  return uuidStr;
}

#endif