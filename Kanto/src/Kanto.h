#pragma once

// For use by Kanto applications


#include <stdio.h>
#include "Kanto/Application.h"
#include "Kanto/Log.h"
#include "Kanto/Layer.h"
#include "Kanto/ImGui/ImGuiLayer.h"
#include "Kanto/Input.h"
#include "Kanto/KeyCodes.h"
#include "Kanto/MouseButtonCodes.h"

#include "Kanto/Core/Timestep.h"


// -Entrypoint-----
#include "Kanto/Entrypoint.h"
// ----------------

// ---Renderer------------------------
#include "Kanto/Renderer/Renderer.h"
#include "Kanto/Renderer/RenderCommand.h"

#include "Kanto/Renderer/Buffer.h"
#include "Kanto/Renderer/Shader.h"
#include "Kanto/Renderer/VertexArray.h"

#include "Kanto/Renderer/OrthographicCamera.h"
// -----------------------------------