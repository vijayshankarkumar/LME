#ifndef CONFIG_H
#define CONFIG_H

#include <map>
#include <string>
#include "Utils/AnyType.h"

namespace laal {

	class Config {

	private:

		std::map<std::string, any> configs;

	public:

		Config();

		bool contains(const std::string& key) const;
		void put(const std::string& key, const any& value);
		any get(const std::string& key);
	};
}

#endif // !CONFIG_H
