//
// Created by sloath on 06-Aug-26.
//
#include "../include/Game.h"
#include "../include/Constants.h"
#include "../include/Actor.h"
#include "../include/SpriteComponent.h"
#include "../include/BGSpriteComponent.h"
#include "../../Game/Skeleton.h"

#include <random>
#include <ranges>

Game::Game() : mWindow{ nullptr }, mRenderer{ nullptr }, mIsRunning{ true }, mTicksCount{ 0 }, mUpdatingActors{ false }
{

}

// initialize the game
bool Game::Initialize()
{
	bool success{ true };

	// init SDL
	if (SDL_Init(SDL_INIT_VIDEO) == false)
	{
		SDL_Log("Unable to initialize SDL! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		// create window with renderer
		if (SDL_CreateWindowAndRenderer(windowTitle.c_str(), windowWidth, windowHeight, 0, &mWindow, &mRenderer) == false)
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

void Game::RemoveActor(Actor* actor)
{
	// is actor Pending?
	auto iter = std::ranges::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end())
	{
		std::iter_swap(mPendingActors.end(), iter);
		mPendingActors.pop_back();
	}

	// is Actor Active?
	iter = std::ranges::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		std::iter_swap(mActors.end() - 1, iter);
		mActors.pop_back();
	}
}

void Game::AddSprite(SpriteComponent* sprite)
{
	// find insertion point in sorted vector
	// (first element with drawOrder higher)
	const int drawOrder = sprite->GetDrawOder();
	auto iter = mSprites.begin();
	for (; iter != mSprites.end(); ++iter)
		if (drawOrder < (*iter)->GetDrawOder())
			break;
	mSprites.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
	const auto iter = std::ranges::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}

SDL_Texture* Game::GetTexture(const std::string& fileName)
{
	SDL_Texture* tex{ nullptr };
	const std::string filePath = "../../Game/" + fileName;
	// is texture already in map
	if (const auto iter = mTextures.find(filePath); iter != mTextures.end()) tex = iter->second;
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

// helper functions for the game loop
void Game::ProcessInput()
{
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
		case SDL_EVENT_KEY_DOWN:
			switch (event.key.key)
			{
			case SDLK_ESCAPE:
				mIsRunning = false;
				break;
			case SDLK_F1:
				logFPSandVSYNC = !logFPSandVSYNC;
				break;
			case SDLK_F2:
				fpsCapEnabled = !fpsCapEnabled;
				break;
			case SDLK_F3:
				vSyncEnabled = !vSyncEnabled;
				SDL_SetRenderVSync(mRenderer, vSyncEnabled ? 1 : SDL_RENDERER_VSYNC_DISABLED);
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		mSkeleton->HandleEvent(event);
	}
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
	for (const auto actor : deadActors)
		delete actor;

	if (logFPSandVSYNC)
		SDL_Log("Delta Time: %f | FPS Capped: %c | VSync: %c", deltaTime, fpsCapEnabled ? 'T' : 'F', vSyncEnabled ? 'T' : 'F');
}

void Game::GenerateOutput() const
{
	SDL_SetRenderDrawColor(mRenderer, 245, 245, 245, 255);
	SDL_RenderClear(mRenderer);

	for (const auto sprite : mSprites)
		sprite->Draw(mRenderer);

	SDL_RenderPresent(mRenderer);
}

void Game::LoadData()
{
	// skeleton
	mSkeleton = new Skeleton(this);
	mSkeleton->SetPosition(Vector2(windowWidth * 0.5f, windowHeight * 0.5f));
	mSkeleton->SetScale(2.0f);

	/*// create actor for background
	auto* temp = new Actor(this);
	temp->SetPosition(Vector2(windowWidth * 0.5f, windowHeight * 0.5f));

	// create the 'far back' background
	auto* bg = new BGSpriteComponent(temp);
	bg->SetScreenSize(Vector2(windowWidth, windowHeight));
	std::vector<SDL_Texture*> bgtexs{
		GetTexture("Assets/FarBack01.png"),
		GetTexture("Assets/FarBack02.png"),
	};
	bg->SetBGTextures(bgtexs);
	bg->SetScrollSpeed(-50.0f);

	// creat the closer bg
	bg = new BGSpriteComponent(temp, 50);
	bg->SetScreenSize(Vector2(windowWidth, windowHeight));
	bgtexs = {
		GetTexture("Assets/Stars.png"),
		GetTexture("Assets/Stars.png"),
	};
	bg->SetBGTextures(bgtexs);
	bg->SetScrollSpeed(-100.0f);*/
}

void Game::UnloadData() const
{
	// delete actors
	while (!mActors.empty())
		delete mActors.back();

	// destroy textures
	for (const auto& val : mTextures | std::views::values)
		SDL_DestroyTexture(val);
}
