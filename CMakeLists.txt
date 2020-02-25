cmake_minimum_required(VERSION 3.16)
project(Engine2Cmake)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "-fpermissive -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -pthread")

add_executable(Engine2Cmake main.cpp UTIL/src/Utility.cpp UTIL/include/Utility.h UTIL/UTIL.h SANDBOX/include/My_game.h
        SANDBOX/include/Test_state.h SANDBOX/src/My_game.cpp SANDBOX/src/Test_state.cpp RES_MANAGER/include/Centralized_resource_manager.h
        RES_MANAGER/include/Resource_manager.h RES_MANAGER/include/Resource_type_counter.h RES_MANAGER/src/Resource_type_counter.cpp
        RES_MANAGER/RES_MANAGER.h LOG/include/Color.h LOG/include/CTimer.h LOG/include/Log_query.h LOG/include/Logger.h LOG/include/Specialized_logger.h
        LOG/src/Color.cpp LOG/src/CTimer.cpp LOG/src/Log_query.cpp LOG/src/Logger.cpp LOG/src/Specialized_logger.cpp LOG/LOG.h
        EV_BUS/include/Event.h EV_BUS/include/Event_bus.h EV_BUS/include/Function_handler.h EV_BUS/EV_BUS.h ENGINE/APP/include/Application.h
        ENGINE/APP/include/Application_state.h ENGINE/APP/src/Application.cpp ENGINE/APP/APP.h ENGINE/CORE/include/Controller.h
        ENGINE/CORE/include/Events.h
        ENGINE/CORE/include/Font.h
        ENGINE/CORE/include/Init.h
        ENGINE/CORE/include/Multithreading.h
        ENGINE/CORE/include/Render.h
        ENGINE/CORE/include/Scancodes.h
        ENGINE/CORE/include/SDL_includes.h
        ENGINE/CORE/include/Surface.h
        ENGINE/CORE/include/Surface_factory.h
        ENGINE/CORE/include/Texture.h
        ENGINE/CORE/include/Timer.h
        ENGINE/CORE/include/Utilities.h
        ENGINE/CORE/include/Window.h
        ENGINE/CORE/include/Window_attributes.h
        ENGINE/CORE/include/Wrappers.h
        ENGINE/CORE/src/Controller.cpp
        ENGINE/CORE/src/Events.cpp
        ENGINE/CORE/src/Font.cpp
        ENGINE/CORE/src/Init.cpp
        ENGINE/CORE/src/Multithreading.cpp
        ENGINE/CORE/src/Render.cpp
        ENGINE/CORE/src/Surface.cpp
        ENGINE/CORE/src/Surface_factory.cpp
        ENGINE/CORE/src/Texture.cpp
        ENGINE/CORE/src/Timer.cpp
        ENGINE/CORE/src/Window.cpp
        ENGINE/CORE/src/Wrappers.cpp
        ENGINE/CORE/CORE.h
        ENGINE/Engine.h
        ECS/include/Component.h
        ECS/include/Component_handle.h
        ECS/include/Component_manager.h
        ECS/include/Component_mask.h
        ECS/include/Engine.h
        ECS/include/Entity.h
        ECS/include/Entity_handle.h
        ECS/include/Entity_manager.h
        ECS/include/Entity_map.h
        ECS/include/Includes.h
        ECS/include/System.h
        ECS/src/Component.cpp
        ECS/src/Component_mask.cpp
        ECS/src/Engine.cpp
        ECS/src/Entity_manager.cpp
        ECS/src/Entity_map.cpp
        ECS/src/System.cpp
        ECS/ECS.h
        )
