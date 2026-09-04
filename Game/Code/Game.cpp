//
// Created by sloath on 03-Sep-26.
//

#include "Game.h"
#include <Engine/include/Actor.h>

Game::Game() = default;

Game::~Game() = default;

void Game::LoadData()
{
    vertShader = GetShader("Shaders/TexturedQuad.vert.spv", 0, 0, 0, 0);
    fragShader = GetShader("Shaders/TexturedQuad.frag.spv", 0, 0, 0, 0);
    if (!fragShader or !vertShader)
    {
        SDL_Log("Failed to load shader!");
        mIsRunning = false;
        return;
    }

    // Create the pipeline
    SDL_GPUGraphicsPipelineCreateInfo pipelineCreateInfo = {
        .vertex_shader = vertShader,
        .fragment_shader = fragShader,
        .vertex_input_state = (SDL_GPUVertexInputState){
            .vertex_buffer_descriptions = (SDL_GPUVertexBufferDescription[]){{
                .slot = 0,
                .input_rate = SDL_GPU_VERTEXINPUTRATE_VERTEX,
                .instance_step_rate = 0,
                //.pitch = sizeof(PositionTextureVertex)
            }},
            .num_vertex_buffers = 1,
            .vertex_attributes = (SDL_GPUVertexAttribute[]){{
                .location = 0,
                .buffer_slot = 0,
                .format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3,
                .offset = 0
            }, {
                .location = 1,
                .buffer_slot = 0,
                .format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT2,
                .offset = sizeof(float) * 3
            }},
            .num_vertex_attributes = 2
        },
        .primitive_type = SDL_GPU_PRIMITIVETYPE_TRIANGLELIST,
        .target_info = {
            .color_target_descriptions = (SDL_GPUColorTargetDescription[]){{
                .format = SDL_GetGPUSwapchainTextureFormat(mDevice, mWindow)
            }},
            .num_color_targets = 1,
        }
    };

    mPipeline = SDL_CreateGPUGraphicsPipeline(mDevice, &pipelineCreateInfo);
    if (!mPipeline)
    {
        SDL_Log("Failed to create fill pipeline");
        mIsRunning = false;
    }

    SDL_ReleaseGPUShader(mDevice, vertShader);
    SDL_ReleaseGPUShader(mDevice, fragShader);
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
