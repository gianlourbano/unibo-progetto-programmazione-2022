#pragma once

#include <ncurses.h>

#include "debug/debugger.hpp"
#include "core/color/color.hpp"
#include "graphics/window/window.hpp"
#include "engine.hpp"
#include "input/input.hpp"
//////
#include "core/ECS/entity/entity.hpp"
#include "core/ECS/entity/scriptable_entity.hpp"
#include "core/event/event_manager.hpp"
#include "core/ECS/entity_manager.hpp"
#include "core/ECS/component_manager.hpp"
#include "core/ECS/system_manager.hpp"
#include "core/brain.hpp"
#include "core/time/time.hpp"
//////
//#include "debug/debug_state.hpp"
//////
#include "core/ECS/components/animation.hpp"
#include "core/ECS/components/animator_controller.hpp"
#include "core/ECS/components/transform.hpp"
#include "core/ECS/components/sprite.hpp"
#include "core/ECS/components/native_script.hpp"
#include "core/ECS/components/ui.hpp"
#include "core/ECS/systems/scripts_system.hpp"
#include "core/ECS/systems/animation_system.hpp"
#include "core/ECS/systems/render_system.hpp"
#include "core/ECS/systems/UI_system.hpp"
///
#include "math/mat.hpp"
#include "math/math.hpp"

#include <string>