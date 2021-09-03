#include "Utils/Config.h"

namespace laal {

	Config::Config() {

	}

	bool Config::contains(const std::string& key) const{
		return this->configs.find(key) != configs.end();
	}

	void Config::put(const std::string& key, const any& value) {
		this->configs[key] = value;
	}

	any Config::get(const std::string& key){
		return this->configs[key];
	}
}