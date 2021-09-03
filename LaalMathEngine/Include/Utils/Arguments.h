#ifndef LAAL_ARGUMENTS_HPP
#define LAAL_ARGUMENTS_HPP

#include <map>
#include <string>
#include "Utils/AnyType.h"

namespace laal
{
	class Arguments
	{

	private:

		std::map<std::string, any> styles;

	public:

		bool Contains(std::string key);

		void Put(std::string key, any value);

		any Get(std::string key);

		void RemoveSymbol(std::string& str);
	};
}

#endif // !LAAL_ARGUMENTS_HPP
