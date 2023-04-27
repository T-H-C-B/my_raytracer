//
// Created by Clément Lagasse on 24/04/2023.
//

#include <algorithm>
#include "EventManager.hpp"

void RayTracer::Core::EventManager::addEvent(RayTracer::Core::EventType &type)
{
    _events.push_back(type);
}

void RayTracer::Core::EventManager::addEvent(RayTracer::Core::EventType &&type)
{
    _events.push_back(type);
}

void RayTracer::Core::EventManager::removeEvent(EventType &type)
{
    _events.erase(std::find(_events.begin(), _events.end(), type));
}


void RayTracer::Core::EventManager::removeEvent(RayTracer::Core::EventType &&type)
{
    removeEvent(type);
}

void RayTracer::Core::EventManager::clearEvents()
{
    _events.clear();
}

bool RayTracer::Core::EventManager::isEventTriggered(RayTracer::Core::EventType &type)
{
    return std::find(_events.begin(), _events.end(), type) != _events.end();
}

bool RayTracer::Core::EventManager::isEventTriggered(RayTracer::Core::EventType &&type)
{
    return std::find(_events.begin(), _events.end(), type) != _events.end();
}
