//
// Created by sloath on 06-Aug-26.
//

#include "include/Engine.h"
#include "include/Constants.h"
#include "include/Actor.h"
#include "include/SpriteComponent.h"
#include "include/InputSystem.h"
//#include "include/CameraComponent.h"
#include <SDL3/SDL_gpu.h>
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
		// create GPUDevice
		mDevice = SDL_CreateGPUDevice(
			SDL_GPU_SHADERFORMAT_SPIRV | SDL_GPU_SHADERFORMAT_DXIL | SDL_GPU_SHADERFORMAT_MSL,
			true,nullptr);
		if (mDevice == nullptr)
		{
			SDL_Log("Unable to create GPU device!");
			success = false;
		}
		else
		{
			mWindow = SDL_CreateWindow(
				windowTitle.c_str(),
				static_cast<int>(windowWidth), static_cast<int>(windowHeight),
				SDL_WINDOW_RESIZABLE);

			if (!mWindow)
			{
				SDL_Log("Unable to create Window and Renderer! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				if (!SDL_ClaimWindowForGPUDevice(mDevice, mWindow))
				{
					SDL_Log("Unable to claim Window for Device");
					success = false;
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

	// SDL_DestroyRenderer(mRenderer);
	// mRenderer = nullptr;

	SDL_DestroyGPUDevice(mDevice);
	mDevice = nullptr;

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

SDL_GPUShader* Engine::GetShader(const std::string& shaderFileName,
		const Uint32 samplerCount, const Uint32 storageTextureCount,
		const Uint32 storageBufferCount, const Uint32 uniformBufferCount)
{
	SDL_GPUShaderStage stage;
	if (SDL_strstr(shaderFileName.c_str(), ".vert"))
		stage = SDL_GPU_SHADERSTAGE_VERTEX;
	else if (SDL_strstr(shaderFileName.c_str(), "frag"))
		stage = SDL_GPU_SHADERSTAGE_FRAGMENT;
	else
	{
		SDL_Log("Invalid shader stage!");
		return nullptr;
	}

	char fullPath[256];
	const std::string filePath = "../../Game/" + shaderFileName;
	const SDL_GPUShaderFormat backendFormats = SDL_GetGPUShaderFormats(mDevice);
	SDL_GPUShaderFormat format = SDL_GPU_SHADERFORMAT_INVALID;
	const char* entryPoint;
	if (backendFormats & SDL_GPU_SHADERFORMAT_SPIRV)
	{
		SDL_snprintf(fullPath, sizeof(fullPath), "%s.spv", filePath.c_str());
		format = SDL_GPU_SHADERFORMAT_SPIRV;
		entryPoint = "main";
	}
	else if (backendFormats & SDL_GPU_SHADERFORMAT_MSL)
	{
		SDL_snprintf(fullPath, sizeof(fullPath), "%s.msl", filePath.c_str());
		format = SDL_GPU_SHADERFORMAT_MSL;
		entryPoint = "main0";
	}
	else if (backendFormats & SDL_GPU_SHADERFORMAT_DXIL)
	{
		SDL_snprintf(fullPath, sizeof(fullPath), "%s.dxil", filePath.c_str());
		format = SDL_GPU_SHADERFORMAT_DXIL;
		entryPoint = "main";
	}
	else
	{
		SDL_Log("Unrecognized backend shader format!");
		return nullptr;
	}
	size_t codeSize;
	void* code = SDL_LoadFile(fullPath, &codeSize);
	if (!code)
	{
		SDL_Log("Failed to load shader from disc! %s", fullPath);
		return nullptr;
	}
	const SDL_GPUShaderCreateInfo shaderInfo = {
		.code_size = codeSize,
		.code = static_cast<const Uint8*>(code),
		.entrypoint = entryPoint,
		.format = format,
		.stage = stage,
		.num_samplers = samplerCount,
		.num_storage_textures = storageTextureCount,
		.num_storage_buffers = storageBufferCount,
		.num_uniform_buffers = uniformBufferCount,
	};
	SDL_GPUShader* shader = SDL_CreateGPUShader(mDevice, &shaderInfo);
	if (!shader)
	{
		SDL_Log("Failed to create shader!");
		SDL_free(code);
		return nullptr;
	}
	SDL_free(code);
	mShaders.emplace(shaderFileName, shader);
	return shader;
}

SDL_Texture* Engine::GetTexture(const std::string& fileName)
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
			/*if (tex = SDL_CreateTextureFromSurface(mRenderer, surface); tex == nullptr)
			{
				SDL_Log("Failed to convert surface to texture: %s", filePath.c_str());
				return nullptr;
			}*/
			SDL_DestroySurface(surface);
		}
		mTextures.emplace(fileName, tex);
	}

	return tex;
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
		//SDL_SetRenderVSync(mRenderer, vSyncEnabled ? 1 : SDL_RENDERER_VSYNC_DISABLED);
	}

	mUpdatingActors = true;
	for (const auto actor : mActors)
		actor->ProcessInput(state);
	mUpdatingActors = false;
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
	SDL_GPUCommandBuffer* cmdBfr = SDL_AcquireGPUCommandBuffer(mDevice);
	if (!cmdBfr)
	{
		SDL_Log("AcquireGPUCommandBuffer failed - Error: %s", SDL_GetError());
		mIsRunning = false;
	}

	SDL_GPUTexture* swapchainTex;
	if (!SDL_WaitAndAcquireGPUSwapchainTexture(cmdBfr, mWindow, &swapchainTex, nullptr, nullptr))
	{
		SDL_Log("WaitAndAcquireGPUSwapchainTexture failed - Error: %s", SDL_GetError());
		mIsRunning = false;
	}

	if (swapchainTex)
	{
		SDL_GPUColorTargetInfo colorTarInfo = {.texture = nullptr};
		colorTarInfo.texture = swapchainTex;
		colorTarInfo.clear_color = (SDL_FColor){.r = 0.f, .g = 0.f, .b = 0.f, .a = 1.0f};
		colorTarInfo.load_op = SDL_GPU_LOADOP_CLEAR;
		colorTarInfo.store_op = SDL_GPU_STOREOP_STORE;
		SDL_GPURenderPass* renderPass = SDL_BeginGPURenderPass(cmdBfr, &colorTarInfo, 1, nullptr);
		SDL_EndGPURenderPass(renderPass);
	}

	SDL_SubmitGPUCommandBuffer(cmdBfr);

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

