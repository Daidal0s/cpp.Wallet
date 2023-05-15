#ifdef MYDLL_EXPORTS
#define MYDLL_API __declspec(dllexport)
#else
#define MYDLL_API __declspec(dllimport)
#endif

#ifndef PCH_H
#define PCH_H

// Добавьте сюда заголовочные файлы для предварительной компиляции
#include "framework.h"
#include <memory>
#include <string>
#include <cstdint>
#include <list>
#include <chrono>
#include <functional>

#endif //PCH_H
