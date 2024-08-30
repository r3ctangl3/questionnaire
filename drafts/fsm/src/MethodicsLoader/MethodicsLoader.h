#include <map>
#include <string>
#include <vector>


#include "Methodology.h"


namespace quest
{


/// @brief Loads and owns all available methodics to avoid runtime overhead
class MethodicsLoader
{
private:
    std::map<std::string, quest::Methodology *> methodics;

public:
    MethodicsLoader();
    ~MethodicsLoader();
    std::vector<const quest::Methodology*> get_methodics(const std::vector<std::string>& methodicsNames);
};


}
