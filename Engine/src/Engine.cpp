//
// Created by sloath on 06-Aug-26.
//

#include "include/Engine.h"
#include "include/Constants.h"
#include "include/Renderer.h"
#include "include/Renderer2D.h"
#include "include/Renderer3D.h"
#include "include/UIScreen.h"
#include "include/InputSystem.h"
#include "include/Actor.h"
#include "include/Actor3D.h"
#include "include/Font.h"
#include <algorithm>

Engine::Engine() = default;

Engine::~Engine() = default;

// initialize the game
bool Engine::Initialize(const RendererType rendererType)
{
	bool success{ true };

	// init SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMEPAD) == false)
	{
		SDL_Log("Unable to initialize SDL! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		switch (rendererType)
		{
			case TwoD:
				mRenderer = new Renderer2D(this);
				break;
			case ThreeD:
				mRenderer = new Renderer3D(this);
				break;
			default:
				SDL_Log("Invalid Renderer Type");
				break;
		}

		if (!mRenderer->Initialize(gWindowWidth, gWindowHeight))
		{
			SDL_Log("Unable to init Renderer");
			delete mRenderer;
			mRenderer = nullptr;
			success = false;
		}
		else
		{
		    if (!TTF_Init())
		    {
		        SDL_Log("SDL_ttf could not be initialized! SDL_ttf error: %s", SDL_GetError());
		        success = false;
		    }
		    else
		    {
		        mInputSystem = new InputSystem();
		        if (!mInputSystem->Initialize(this))
		        {
		            SDL_Log("Failed to initialize InputSystem");
		            success = false;
		        }
		        else
		        {
		            LoadData();
		            mTicksCount = SDL_GetTicksNS();
		        }
		    }
		}
	}

	return success;
}

// run the game loop until the game is over
void Engine::RunLoop()
{
	while (mGameState != EQuit)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

// shutdown the game
void Engine::Shutdown()
{
	UnloadData();

	mRenderer->Shutdown();
    delete mRenderer;
	mRenderer = nullptr;

	mInputSystem->Shutdown();
	delete mInputSystem;
    mInputSystem = nullptr;

	SDL_Quit();
}

void Engine::AddActor(Actor* actor)
{
	if (mUpdatingActors)
		mPendingActors.emplace_back(actor);
	else
		mActors.emplace_back(actor);
}

void Engine::RemoveActor(const Actor* actor)
{
	// is actor Pending?
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end())
	{
		std::iter_swap(mPendingActors.end() - 1, iter);
		mPendingActors.pop_back();
	}

	// is Actor Active?
	iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		std::iter_swap(mActors.end() - 1, iter);
		mActors.pop_back();
	}
}

[[nodiscard]] Font* Engine::GetFont(const std::string& fileName)
{
    auto it =  mFonts.find(fileName);
    if (it != mFonts.end()) return it->second;

    auto font = new Font(this);
    if (font->Load(fileName)) mFonts.emplace(fileName, font);
    else
    {
        font->Unload();
        delete font;
        font = nullptr;
    }
    return font;
}

void Engine::SetRelativeMouseMode(const bool value) const
{
	mInputSystem->SetRelativeMouseMode(value);
}

void Engine::UpdateGame()
{
	// if time remaining in frame
	while (fpsCapEnabled and SDL_GetTicksNS() < mTicksCount + 16000000) {}

	// difference in ticks from last frame
	float deltaTime = (SDL_GetTicksNS() - mTicksCount) / static_cast<float>(SDL_NS_PER_SECOND);
	if (deltaTime > 0.05f) deltaTime = 0.05f;
	mTicksCount = SDL_GetTicksNS();

    if (mGameState == EGameplay)
    {
        // update all Actors
        mUpdatingActors = true;

        for (const auto actor : mActors)
            actor->Update(deltaTime);
        mUpdatingActors = false;

        // move any pending Actors to mActors
        for (auto pending : mPendingActors)
        {
            if (const auto pendingCast = dynamic_cast<Actor3D*>(pending); pendingCast)
                pendingCast->ComputeWorldTransform();
            mActors.emplace_back(pending);
        }
        mPendingActors.clear();

        // add any dead Actors to a temp vector
        std::vector<Actor*> deadActors;
        for (auto actor : mActors)
            if (actor->GetState() == Actor::EDead)
                deadActors.emplace_back(actor);

        // delete dead Actors (which removes them from mActors)
        for (auto actor : deadActors)
        {
            delete actor;
            actor = nullptr;
        }
    }

    // update UI screens
    for (const auto ui : mUIStack)
        if (ui->GetState() == UIScreen::EActive)
            ui->Update(deltaTime);

    // remove any closing UI screens
    auto it = mUIStack.begin();
    while (it != mUIStack.end())
    {
        if ((*it)->GetState() == UIScreen::EClosing)
        {
            delete *it;
            it = mUIStack.erase(it);
        }
        else ++it;
    }

	if (logFPSandVSYNC)
		SDL_Log("Delta Time: %f | FPS Capped: %c | VSync: %c", deltaTime, fpsCapEnabled ? 'T' : 'F', vSyncEnabled ? 'T' : 'F');
}

void Engine::ProcessInput()
{
    mInputSystem->PrepareForUpdate();

    SDL_Event event;
    SDL_zero(event);

    // while there are events - process
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        // case SDL_EVENT_QUIT:
        //     mGameState = EQuit;
        //     break;
        case SDL_EVENT_WINDOW_RESIZED:
            mRenderer->ProcessEvent(event);
            break;
        case SDL_EVENT_MOUSE_WHEEL:
        case SDL_EVENT_GAMEPAD_ADDED:
        case SDL_EVENT_GAMEPAD_REMOVED:
            mInputSystem->ProcessEvent(event);
            break;
        default:
            break;
        }
    }

    mInputSystem->Update();
    const InputState& state = mInputSystem->GetState();
    std::vector<SDL_Scancode> inputEventsHandled{};

    // process any keys here as desired...
    // if (state.Keyboard.GetKeyState(SDL_SCANCODE_ESCAPE) == EPressed)
    //     mGameState = EQuit;
    if (state.Keyboard.GetKeyState(SDL_SCANCODE_F1) == EPressed)
        logFPSandVSYNC = !logFPSandVSYNC;
    if (state.Keyboard.GetKeyState(SDL_SCANCODE_F2) == EPressed)
        fpsCapEnabled = !fpsCapEnabled;
    if (state.Keyboard.GetKeyState(SDL_SCANCODE_F3) == EPressed)
    {
        vSyncEnabled = !vSyncEnabled;
        mRenderer->SetVSync();
    }
    if (state.Keyboard.GetKeyState(SDL_SCANCODE_P) == EPressed)
    {
        if (mGameState == EGameplay) mGameState = EPaused;
        else if (mGameState == EPaused) mGameState = EGameplay;
    }

    if (mGameState == EGameplay)
    {
        mUpdatingActors = true;
        for (const auto actor : mActors)
            actor->ProcessInput(state);
        mUpdatingActors = false;
    }
    else if (!mUIStack.empty())
        mUIStack.back()->ProcessInput(state);
}

void Engine::GenerateOutput() const
{
	mRenderer->Draw();
}

void Engine::UnloadData()
{
    // delete actors
    while (!mActors.empty())
        delete mActors.back();

    // clear UI stack
    while (!mUIStack.empty())
    {
        delete mUIStack.back();
        mUIStack.pop_back();
    }

    mRenderer->UnloadData();
}