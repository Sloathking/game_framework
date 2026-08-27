//
// Created by sloath on 06-Aug-26.
//
#include "../include/Game.h"
#include "../include/Constants.h"
#include "../include/Actor.h"
#include "../include/SpriteComponent.h"
#include "../include/InputSystem.h"
#include <random>
#include <algorithm>

#include "../../Game/Dot.h"
#include "../../Game/Ship.h"

Game::Game() = default;

// initialize the game
bool Game::Initialize()
{
	bool success{ true };

	// init SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD) == false)
	{
		SDL_Log("Unable to initialize SDL! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		// create window with renderer
		if (SDL_CreateWindowAndRenderer(windowTitle.c_str(),static_cast<int>(windowWidth), static_cast<int>(windowHeight), 0, &mWindow, &mRenderer) == false)
		{
			SDL_Log("Unable to create Window and Renderer! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			// enable VSync
			if (SDL_SetRenderVSync(mRenderer, vSyncEnabled ? 1 : SDL_RENDERER_VSYNC_DISABLED) == false)
			{
				SDL_Log("Could not enable VSync! SDL Error: %s", SDL_GetError());
				success = false;
			}
		}
	}

	mInputSystem = new InputSystem();
	if (!mInputSystem->Initialize(this))
	{
		SDL_Log("Failed to initialize InputSystem");
		success = false;
	}

	LoadData();

	mTicksCount = SDL_GetTicksNS();

	return success;
}

// run the game loop until the game is over
void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

// shutdown the game
void Game::Shutdown()
{
	UnloadData();

	mInputSystem->Shutdown();
	delete mInputSystem;

	SDL_DestroyRenderer(mRenderer);
	mRenderer = nullptr;

	SDL_DestroyWindow(mWindow);
	mWindow = nullptr;

	SDL_Quit();
}

void Game::AddActor(Actor* actor)
{
	if (mUpdatingActors)
		mPendingActors.emplace_back(actor);
	else
		mActors.emplace_back(actor);
}

void Game::RemoveActor(const Actor* actor)
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

void Game::AddSprite(SpriteComponent* sprite)
{
	// find insertion point in sorted vector (first element with drawOrder higher)
	const int drawOrder = sprite->GetDrawOder();
	auto iter = mSprites.begin();
	for (; iter != mSprites.end(); ++iter)
		if (drawOrder < (*iter)->GetDrawOder())
			break;
	mSprites.insert(iter, sprite);
}

void Game::RemoveSprite(const SpriteComponent* sprite)
{
	if (const auto iter = std::find(mSprites.begin(), mSprites.end(), sprite); iter != mSprites.end())
		mSprites.erase(iter);
}

SDL_Texture* Game::GetTexture(const std::string& fileName)
{
	SDL_Texture* tex{ nullptr };
	const std::string filePath = "../../Game/" + fileName;

	// is texture already in map
	if (const auto iter = mTextures.find(fileName); iter != mTextures.end()) tex = iter->second;
	else
	{
		// load from file
		if (SDL_Surface* surface = IMG_Load(filePath.c_str()); surface == nullptr)
		{
			SDL_Log("Failed to load texture: %s", filePath.c_str());
			return nullptr;
		}
		else
		{
			if (tex = SDL_CreateTextureFromSurface(mRenderer, surface); tex == nullptr)
			{
				SDL_Log("Failed to convert surface to texture: %s", filePath.c_str());
				return nullptr;
			}
			SDL_DestroySurface(surface);
		}
		mTextures.emplace(fileName, tex);
	}

	return tex;
}

void Game::ProcessInput()
{
	mInputSystem->PrepareForUpdate();

	SDL_Event event;
	SDL_zero(event);

	// while there are events - process
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_EVENT_QUIT:
			mIsRunning = false;
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

	// process any keys here as desired...
	if (state.Keyboard.GetKeyState(SDL_SCANCODE_ESCAPE) == EPressed)
		mIsRunning = false;
	if (state.Keyboard.GetKeyState(SDL_SCANCODE_F1) == EPressed)
		logFPSandVSYNC = !logFPSandVSYNC;
	if (state.Keyboard.GetKeyState(SDL_SCANCODE_F2) == EPressed)
		fpsCapEnabled = !fpsCapEnabled;
	if (state.Keyboard.GetKeyState(SDL_SCANCODE_F3) == EPressed)
	{
		vSyncEnabled = !vSyncEnabled;
		SDL_SetRenderVSync(mRenderer, vSyncEnabled ? 1 : SDL_RENDERER_VSYNC_DISABLED);
	}

	mUpdatingActors = true;
	for (const auto actor : mActors)
		actor->ProcessInput(state);
	mUpdatingActors = false;
}

void Game::UpdateGame()
{
	// if time remaining in frame
	while (fpsCapEnabled and SDL_GetTicksNS() < mTicksCount + 16000000) {}

	// difference in ticks from last frame
	float deltaTime = (SDL_GetTicksNS() - mTicksCount) / static_cast<float>(SDL_NS_PER_SECOND);
	if (deltaTime > 0.05f) deltaTime = 0.05f;
	mTicksCount = SDL_GetTicksNS();

	// update all Actors
	mUpdatingActors = true;
	for (const auto actor : mActors)
		actor->Update(deltaTime);
	mUpdatingActors = false;

	// move any pending Actors to mActors
	for (auto pending : mPendingActors)
		mActors.emplace_back(pending);
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

	if (logFPSandVSYNC)
		SDL_Log("Delta Time: %f | FPS Capped: %c | VSync: %c", deltaTime, fpsCapEnabled ? 'T' : 'F', vSyncEnabled ? 'T' : 'F');
}

void Game::GenerateOutput() const
{
	SDL_SetRenderDrawColor(mRenderer, 100, 100, 100, 255);
	SDL_RenderClear(mRenderer);

	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
	for (int x = 0; x <= 10000; x += 100)
		SDL_RenderLine(mRenderer, x, -10000, x, 10000);
	for (int y = 0; y <= 10000; y += 100)
		SDL_RenderLine(mRenderer, -10000, y, 10000, y);

	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
	constexpr SDL_FRect center{.x = -5, .y = -5, .w = 10, .h = 10};
	SDL_RenderFillRect(mRenderer, &center);

	for (const auto sprite : mSprites)
		sprite->Draw(mRenderer, nullptr, -1, -1);

	const Vector2 dotPos = mDot->GetPosition();
	const Vector2 dotFrd = mDot->GetForward() * 50;
	const SDL_FRect dotRect{.x = dotPos.x - 1, .y = dotPos.y - 1, .w = 2, .h = 2};
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
	SDL_RenderLine(mRenderer, dotPos.x, dotPos.y, dotPos.x + dotFrd.x, dotPos.y + dotFrd.y);
	SDL_RenderFillRect(mRenderer, &dotRect);

	SDL_RenderPresent(mRenderer);
}

void Game::LoadData()
{
	mDot = new Dot(this);
	mDot->SetPosition(Vector2(100, 200));
}

void Game::UnloadData()
{
	// delete actors
	while (!mActors.empty())
		delete mActors.back();

	// destroy textures
	for (const auto& i : mTextures)
		SDL_DestroyTexture(i.second);
}
