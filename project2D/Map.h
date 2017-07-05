#pragma once
#include "DynamicArray.h"
#include <stdexcept>

template <typename K, typename V>
struct KeyValuePair
{
	K key;
	V value;
};

template <typename K, typename V>
class Map
{
	typedef KeyValuePair<K,V>* iterator;
	typedef const KeyValuePair<K,V>* const_iterator;

public:
	Map()
	{
	}

	bool Insert(K _key, V _value)
	{
		if (find(_key) == -1)
		{
			kvp.AddToEnd(KeyValuePair<K, V>({ _key, _value }));
			return true;
		}

		// Key is already in map
		return false;
	}

	bool remove(K _key)
	{
		for (int i = 0; i < kvp.Size(); i++)
			if (kvp[i].key == _key)
			{
				kvp.Remove(i);
				return true;
			}

		// Key is not in the Map
		return false;
	}

	V& operator[] (K _key)
	{
		int index = find(_key);
		if (index == -1)
		{
			kvp.AddToEnd(KeyValuePair<K, V>({ _key, V() }));
			index = find(_key);
		}

		return (kvp[index].value);
	}

	iterator begin() { return kvp.begin(); }
	const_iterator begin() const { return kvp.begin(); }

	iterator end() { return kvp.end(); }
	const_iterator end() const { return kvp.end(); }

	DynamicArray<K> Keys()
	{
		DynamicArray<K> returnArray;
		for (KeyValuePair<K,V> p : kvp)
			returnArray.AddToEnd(p.key);
		return returnArray;
	}

	DynamicArray<V> Values()
	{
		DynamicArray<V> returnArray;
		for (KeyValuePair<K, V> p : kvp)
			returnArray.AddToEnd(p.value);
		return returnArray;
	}

	bool Exists(K _key)
	{
		return find(_key) == -1 ? false : true;
	}

	int size() { return kvp.Size(); }
	void clear() { kvp.Clear(); }

	int find(K _key)
	{
		for (int i = 0; i < kvp.Size(); i++)
			if (kvp[i].key == _key)
				return i;
		return -1;
	}

private:
	DynamicArray<KeyValuePair<K,V>> kvp;
};