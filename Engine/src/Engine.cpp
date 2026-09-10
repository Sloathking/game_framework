//
// Created by sloath on 06-Aug-26.
//

#include "include/Engine.h"
#include <GL/glew.h>
#include "include/Constants.h"
#include "include/InputSystem.h"
#include "include/Actor.h"
#include "include/SpriteComponent.h"
#include "include/SpriteVertexArray.h"
#include "include/VertexArray.h"
#include "include/Shader.h"
#include "include/Texture.h"
#include "include/Mesh.h"
#include <random>
#include <algorithm>

Engine::Engine() = default;

Engine::~Engine() = default;

// initialize the game
bool Engine::Initialize()
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
		// set OpenGL attributes
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		/*-----------------*/
		// request a color buffer with 8-bits per RGBA channel
		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
		// enable double buffering
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

		mWindow = SDL_CreateWindow(
			windowTitle.c_str(),
			static_cast<int>(windowWidth), static_cast<int>(windowHeight),
			SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

		if (!mWindow)
		{
			SDL_Log("Unable to create Window and Renderer! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			// create context
			mContext = SDL_GL_CreateContext(mWindow);
			if (!mContext)
			{
				SDL_Log("Unable to create OpenGL context! SDL Error: %s", SDL_GetError());
				success = false;
			}
			else
			{
				// init GLEW
				glewExperimental = GL_TRUE;
				if (glewInit() != GLEW_OK)
				{
					SDL_Log("Error initializing GLEW!");
					success = false;
				}
				else
				{
					// use vsync
					if (!SDL_GL_SetSwapInterval(1))
						SDL_Log("Warning: Unable to set VSync! SDL Error: %s", SDL_GetError());
				}
			}
		}
	}

	mInputSystem = new InputSystem();
	if (!mInputSystem->Initialize(this))
	{
		SDL_Log("Failed to initialize InputSystem");
		success = false;
	}

	if (!LoadShaders("Sprite.vert","Sprite.frag"))
	{
		SDL_Log("Failed to load shaders!");
		success = false;
	}

	CreateSpriteVerts();

	LoadData();

	mTicksCount = SDL_GetTicksNS();

	return success;
}

// run the game loop until the game is over
void Engine::RunLoop()
{
	while (mIsRunning)
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

	mInputSystem->Shutdown();
	delete mInputSystem;

	SDL_GL_DestroyContext(mContext);

	SDL_DestroyWindow(mWindow);
	mWindow = nullptr;

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

void Engine::AddSprite(SpriteComponent* sprite)
{
	// find insertion point in sorted vector (first element with drawOrder higher)
	const int drawOrder = sprite->GetDrawOder();
	auto iter = mSprites.begin();
	for (; iter != mSprites.end(); ++iter)
		if (drawOrder < (*iter)->GetDrawOder())
			break;
	mSprites.insert(iter, sprite);
}

void Engine::RemoveSprite(const SpriteComponent* sprite)
{
	if (const auto iter = std::find(mSprites.begin(), mSprites.end(), sprite); iter != mSprites.end())
		mSprites.erase(iter);
}

Texture* Engine::GetTexture(const std::string& fileName)
{
	Texture* tex{ nullptr };

	// is texture already in map
	if (const auto iter = mTextures.find(fileName); iter != mTextures.end()) tex = iter->second;
	else
	{
		// const std::string filePath = "../../Game/" + fileName;
		tex = new Texture();
		// load from file
		if (tex->Load(fileName))
		{
			mTextures.emplace(fileName, tex);
		}
		else
		{
			delete tex;
			tex = nullptr;
		}
	}
	return tex;
}

Mesh* Engine::GetMesh(const std::string& fileName)
{
	Mesh* mesh{nullptr};

	if (const auto iter = mMeshes.find(fileName); iter != mMeshes.end()) mesh = iter->second;
	else
	{
		mesh = new Mesh();
		if (mesh->Load(fileName, this))
			mMeshes.emplace(fileName, mesh);
		else
		{
			delete mesh;
			return nullptr;
		}
	}

	return mesh;
}

SDL_Surface* Engine::LoadImage(const std::string& fileName, const int numChannels)
{
	const std::string fullPath = "../../Game/" + fileName;
	SDL_PixelFormat format;
	SDL_Surface* res = SDL_LoadBMP(fullPath.c_str());
	if (!res)
	{
		SDL_Log("Failed to load BMP: %s", SDL_GetError());
		return nullptr;
	}

	if (numChannels == 4)
	{
		format = SDL_PIXELFORMAT_ABGR8888;
	}
	else
	{
		SDL_assert(!"Unexpected numChannels");
		SDL_DestroySurface(res);
		return nullptr;
	}
	if (res->format != format)
	{
		SDL_Surface *next = SDL_ConvertSurface(res, format);
		SDL_DestroySurface(res);
		res = next;
	}

	return res;
}

bool Engine::LoadShaders(const std::string& vertName, const std::string& fragName)
{
	const Matrix4 viewProj = Matrix4::CreateSimpleViewProj(1920.0f, 1080.0f);
	mSpriteShader = new Shader();
	if (!mSpriteShader->Load(vertName, fragName))
		return false;
	mSpriteShader->SetActive();
	mSpriteShader->SetMatrixUniform("uViewProj", viewProj);
	return true;
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
		case SDL_EVENT_QUIT:
			mIsRunning = false;
			break;
		case SDL_EVENT_WINDOW_RESIZED:
			{
				// int x, y;
				// if (!SDL_GetWindowSize(mWindow, &x, &y))
				// {
				// 	SDL_Log("SDL_EVENT_WINDOW_RESIZED - Error: %s", SDL_GetError());
				// 	mIsRunning = false;
				// 	break;
				// }
				// mCamera->SetWindowSize(Vector2(static_cast<float>(x), static_cast<float>(y)));
			}
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
		if (!SDL_GL_SetSwapInterval(vSyncEnabled))
			SDL_Log("Warning: Unable to set VSync! SDL Error: %s", SDL_GetError());
	}

	mUpdatingActors = true;
	for (const auto actor : mActors)
		actor->ProcessInput(state);
	mUpdatingActors = false;
}

void Engine::CreateSpriteVerts()
{
	static float vertexBuffer[] = {
		-0.5f,  0.5f,   0.0f,	0.0f,	0.0f,	0.0f,	0.0f,	0.0f,
		0.5f,   0.5f,   0.0f,	0.0f,	0.0f,	0.0f,	1.0f,	0.0f,
		0.5f,   -0.5f,  0.0f,	0.0f,	0.0f,	0.0f,	1.0f,	1.0f,
		-0.5f,  -0.5f,  0.0f,	0.0f,	0.0f,	0.0f,	0.0f,	1.0f
	};

	static unsigned int indexBuffer[] = {
		0, 1, 2,
		2, 3, 0
	};

	mSpriteVerts = new VertexArray(vertexBuffer, 4, indexBuffer, 6);
}

void Engine::UpdateGame()
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
	{
		pending->ComputeWorldTransform();
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

	if (logFPSandVSYNC)
		SDL_Log("Delta Time: %f | FPS Capped: %c | VSync: %c", deltaTime, fpsCapEnabled ? 'T' : 'F', vSyncEnabled ? 'T' : 'F');
}

// static bool IsInCamera(const Vector2 spritePos, const CameraComponent* camera)
// {
// 	const Vector2 camPos = camera->GetPosition();
// 	const Vector2 windowSize = camera->GetWindowSize();
// 	if (spritePos.x > camPos.x and spritePos.x < camPos.x + windowSize.x and spritePos.y > camPos.y and spritePos.y < camPos.y + windowSize.y)
// 		return true;
// 	return false;
// }

void Engine::GenerateOutput()
{
	// start of OpenGL stuff

	// set the clear color to gray
	glClearColor(0.50f, 0.50f, 0.50f, 1.0f);
	// clear the color buffer
	glClear(GL_COLOR_BUFFER_BIT);

	// TODO: draw scene
	// Set sprite shader and vertex array objs active
	mSpriteShader->SetActive();
	mSpriteVerts->SetActive();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// draw all sprites
	for (const auto sprite : mSprites)
		sprite->Draw(mSpriteShader);

	//swap buffers,
	SDL_GL_SwapWindow(mWindow);

#pragma region Old Render Code
	/*SDL_SetRenderDrawColor(mRenderer, 25, 25, 25, 255);
	SDL_RenderClear(mRenderer);

	Vector2 camPos = mCamera->GetPosition();
	camPos.x = -camPos.x;
	camPos.y = -camPos.y;

	for (const auto sprite : mSprites)
	{
		if (IsInCamera(sprite->GetOwner()->GetPosition(), mCamera))
			sprite->Draw(mRenderer, camPos, nullptr, -1, -1);
	}

	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
	const SDL_FRect dotRect{.x = mDot->GetPosition().x + camPos.x - 5, .y = mDot->GetPosition().y + camPos.y - 5, .w = 10, .h = 10};
	SDL_RenderFillRect(mRenderer, &dotRect);

	SDL_RenderPresent(mRenderer);*/
#pragma endregion
}
