#pragma once

#ifdef _DEBUG

#include <iostream>
#include <glad/glad.h>

#define CHECK_GL_ERROR { GLenum __glerror__ = glGetError(); if(__glerror__ != GL_NO_ERROR)std::cerr << "GL_ERROR: " << __glerror__ << " at line " << __LINE__ << " in file " << __FILE__ << std::endl;}

#else

#define CHECK_GL_ERROR

#endif
