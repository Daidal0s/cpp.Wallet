#ifdef MYDLL_EXPORTS
#define MYDLL_API __declspec(dllexport)
#else
#define MYDLL_API __declspec(dllimport)
#endif

#ifndef PCH_H
#define PCH_H

// Добавьте сюда заголовочные файлы для предварительной компиляции
#include "framework.h"
#include <iostream>						// Хэдер ввода и вывода
#include <cstdint>						// Определение int32_t и т.д.
#include <chrono>						// Время со стандартом C++20
#include <vector>						// Динамический массив
#include <unordered_map>				// Хэш-мап
#include <list>							// Лист
#include <string>						// Для убоства использования строковых типов
#include <algorithm>					// std::last, std::first, std::placeholders::_1
#include <memory>						// std::unique_ptr<>		-Умный указатель
#include <functional>					// std::function			-Указатель на функцию (делегат)
#include <typeindex>					// 
#include <stdexcept>					// Для обработки ошибок

#endif //PCH_H
