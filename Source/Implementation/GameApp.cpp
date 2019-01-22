#include "stdafx.h"
#include "GameApp.h"

#include "Atomic/Atomic2D/Drawable2D.h"
#include "Atomic/Atomic2D/StaticSprite2D.h"
#include "Atomic/Core/StringUtils.h"
#include "Atomic/Engine/EngineDefs.h"
#include "Atomic/Graphics/Camera.h"
#include "Atomic/Graphics/Graphics.h"
#include "Atomic/Graphics/Renderer.h"
#include "Atomic/Graphics/Viewport.h"
#include "Atomic/IO/FileSystem.h"
#include "Atomic/Resource/ResourceCache.h"
#include "Atomic/Scene/Scene.h"
#include "Atomic/UI/UI.h"

#include "Interface/di/IGameAppDI.h"
#include "Interface/Environment/IWorldModule.h"

using namespace Atomic;

CGameApp::CGameApp(Context* context, UniquePtr<IGameAppDI> injector)
    : IGameApp(context, std::move(injector))
{
}

void CGameApp::Setup()
{
    Application::Setup();

    engineParameters_[EP_WINDOW_TITLE] = GetTypeName();
    engineParameters_[EP_WINDOW_WIDTH] = 1024;
    engineParameters_[EP_WINDOW_HEIGHT] = 1024;
    engineParameters_[EP_LOG_NAME] = GetSubsystem<FileSystem>()->GetAppPreferencesDir("atomic", "logs") + GetTypeName() + ".log";
    engineParameters_[EP_FULL_SCREEN] = false;
    engineParameters_[EP_HEADLESS] = false;
    engineParameters_[EP_SOUND] = false;
    engineParameters_[EP_RESOURCE_PATHS] = "Data;PlayerData;CoreData";

    if (!engineParameters_.Contains(EP_RESOURCE_PREFIX_PATHS))
    {
        String resourcePrefix = ToString("%s/Resources;%s/Submodules/AITactics_Game", ATOMIC_ROOT_SOURCE_DIR, ATOMIC_ROOT_SOURCE_DIR);
        engineParameters_[EP_RESOURCE_PREFIX_PATHS] = resourcePrefix;
    }
}

void CGameApp::Start()
{
    Application::Start();

    InitializeSubsystem<IWorldModule>(m_injector->MakeInjector());

    // camera
    {
        auto scene = GetSubsystem<IWorldModule>()->GetScene();
        auto cameraNode = scene->CreateChild("Camera");
        cameraNode->SetPosition({0.0f, 0.0f, -10.0f});
        auto camera = cameraNode->CreateComponent<Camera>();
        camera->SetOrthographic(true);

        auto graphics = GetSubsystem<Graphics>();
        camera->SetOrthoSize((float)graphics->GetHeight() * PIXEL_SIZE);

        Renderer* renderer = GetSubsystem<Renderer>();

        // Set up a viewport to the Renderer subsystem so that the 3D scene can be seen
        SharedPtr<Viewport> viewport(new Viewport(context_, scene, camera));
        renderer->SetViewport(0, viewport);
    }

    // UI
    {
        UI* ui = GetSubsystem<UI>();
        assert(ui);
        ui->Initialize("DefaultUI/language/lng_en.tb.txt");
        ui->LoadDefaultPlayerSkin();
        ui->ToggleDebugHud();
    }
}

void CGameApp::Stop()
{
    ShutdownSubsystem<IWorldModule>();
}