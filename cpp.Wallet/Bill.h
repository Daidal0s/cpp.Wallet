#pragma once
#include "pch.h"

struct MYDLL_API stTime
{
	std::chrono::years Y;
	std::chrono::months Mon;
	std::chrono::days D;
	std::chrono::hours H;
	std::chrono::minutes Min;
	std::chrono::seconds S;
};

class MYDLL_API Time
{
private:
	class impl;
	std::unique_ptr<impl> pimpl;
public:
	Time();
	~Time();
public:
	void setTime(int hours, int minutes, int seconds);
	void setDate(int day, int month, int year);
	void getTime(int *hours, int *minutes, int *seconds) const;
	void getDate(int *day, int *month, int *year) const;
	std::string stringDate() const;
	std::string stringTime() const;
};

class MYDLL_API Bill
{
private:
	class impl;
	std::unique_ptr<impl> pimpl;
public:
public:
};

