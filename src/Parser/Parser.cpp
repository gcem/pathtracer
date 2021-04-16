#include "Parser.hpp"

namespace Parser {
std::shared_ptr<Objects::Scene>
Parser::getScene()
{
    return scene;
}
}