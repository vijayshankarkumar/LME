#include "Utils/Arguments.h"

namespace laal
{
	void Arguments::RemoveSymbol(std::string& str)
	{
		int i = -1, j = 0;
		while (j < str.length())
		{
			if (str[j] >= 'a' && str[j] <= 'z')
			{
				i++;
				str[i] = str[j];
			}
			if (str[j] >= 'A' && str[j] <= 'Z')
			{
				i++;
				str[i] = str[j] - 'A' + 'a';
			}
			j++;
		}
		str.resize(i + 1);
	}

	bool Arguments::Contains(std::string key)
	{
		RemoveSymbol(key);
		return styles.find(key) != styles.end();
	}

	void Arguments::Put(std::string key, any value)
	{
		RemoveSymbol(key);
		styles.insert(std::make_pair(key, value));
	}

	any Arguments::Get(std::string key)
	{
		RemoveSymbol(key);
		return styles.at(key);
	}
}