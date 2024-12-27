#pragma once

#include "include.h"
#include "trPair.h"

#ifndef __TR_MAP__
#define __TR_MAP__

#ifdef TERMINAL_ENGINE_EXPORT
#define TERMINAL_ENGINE_API __declspec(dllexport)
#else
#define TERMINAL_ENGINE_API __declspec(dllimport)
#endif

template <class INDEX, class MAP_T>
struct trMap : public trObject
{
public:

	// INI default

	trMap() : _map(new std::vector<trPair<INDEX, MAP_T>>()) 
	{

	}

	// INI deep

	trMap(const trMap& other) : _map(new std::vector<trPair<INDEX, MAP_T>>(*other._map)) 
	{

	}

	// copy

	trMap& operator=(const trMap& other)
	{
		if (this == &other) return *this;

		_map = new std::vector<trPair<INDEX, MAP_T>>(*other._map);

		return *this;
	}

	// index

	MAP_T& operator[](const INDEX& idx)
	{
		for (auto& pair : *_map)
		{
			if (*pair.first == idx)
			{
				return *pair.second;
			}
		}

		_map->push_back(trPair<INDEX, MAP_T>(idx, MAP_T()));

		return *_map->back().second;
	}

	// GET

	const size_t& GetSize() const
	{
		return _map->size();
	}

	// Itérateur début

	auto begin() const
	{
		return _map->begin();
	}

	// Itérateur fin

	auto end() const
	{
		return _map->end();
	}

	// Itérateur début (non-const pour modification)

	auto begin()
	{
		return _map->begin();
	}

	// Itérateur fin (non-const pour modification)

	auto end()
	{
		return _map->end();
	}

	// DESTR

	~trMap()
	{
		delete _map;
	}

private:

	std::vector<trPair<INDEX, MAP_T>>* _map; 
};

#endif
