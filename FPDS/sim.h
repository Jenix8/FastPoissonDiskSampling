#pragma once

#include <vector>
#include <glm/glm.hpp>

void init();
void run();
std::vector<glm::vec2>& getActive();
std::vector<glm::vec2>& getPos();