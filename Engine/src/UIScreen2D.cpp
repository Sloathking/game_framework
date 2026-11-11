//
// Created by sloath on 10/28/26.
//

#include "include/UIScreen2D.h"
#include <utility>
#include "include/Engine.h"
#include "include/Renderer2D.h"
#include "include/Font.h"
#include "include/InputSystem.h"

UIScreen2D::UIScreen2D(Engine * game) : mGame(game)
{
    mGame->PushUI(this);
    mFont = mGame->GetFont("Assets/RobotoMono-VariableFont_wght.ttf");
    mButtonOn = static_cast<Renderer2D*>(mGame->GetRenderer())->GetTexture("Assets/ButtonYellow.png");
    mButtonOff = static_cast<Renderer2D*>(mGame->GetRenderer())->GetTexture("Assets/ButtonBlue.png");
}

UIScreen2D::~UIScreen2D()
{
    if (mTitle)
        SDL_DestroyTexture(mTitle);

    for (const auto b : mButtons)
        delete b;
    mButtons.clear();
}

// UIScreen subclasses can override these
void UIScreen2D::Update(float deltaTime)
{

}

void UIScreen2D::Draw(SDL_Renderer* renderer, const float scaleFactor)
{
    if (mBackground)
    {
        // SDL_SetRenderDrawColor(renderer, color);
        DrawTexture(renderer, mBackground, mBGPos, scaleFactor);
    }

    if (mTitle)
        DrawTexture(renderer, mTitle, mTitlePos, scaleFactor);

    for (const auto b : mButtons)
    {
        SDL_Texture* tex = b->GetHighlighted() ? mButtonOn : mButtonOff;
        DrawTexture(renderer, tex, b->GetPosition(), scaleFactor);
        int btnWidth = tex->w;
        const int textWidth = b->GetNameTex()->w;
        Vector2 offset = b->GetPosition();
        offset.x += static_cast<float>(btnWidth) * 0.5f - static_cast<float>(textWidth) * 0.5f;
        DrawTexture(renderer, b->GetNameTex(), offset, scaleFactor);
    }
}

void UIScreen2D::ProcessInput(const InputState & state)
{
    if (!mButtons.empty())
    {
        const Vector2 mousePos = state.Mouse.GetPosition();
        for (const auto b : mButtons)
            if (b->ContainsPoint(mousePos)) b->SetHighlighted(true);
            else b->SetHighlighted(false);
    }

    if (state.Mouse.GetButtonState(MouseState::Left) == EPressed)
    {
        for (const auto b : mButtons)
            if (b->GetHighlighted())
                b->OnClick();
    }
}

void UIScreen2D::SetTitle(const std::string& text, const Vector3& color, const float pointSize)
{
    if (mTitle)
    {
        SDL_DestroyTexture(mTitle);
        delete mTitle;
        mTitle = nullptr;
    }
    mTitle = mFont->RenderText(text, color, pointSize);
}

void UIScreen2D::AddButton(const std::string& name, std::function<void()> onClick)
{
    const Vector2 dims(static_cast<float>(mButtonOn->w), static_cast<float>(mButtonOn->h));
    auto* b = new Button(name, mFont, std::move(onClick), mNextButtonPos, dims);
    mButtons.emplace_back(b);

    // update position of next button, move down by height of button plus padding
    mNextButtonPos.y += static_cast<float>(mButtonOff->h) + 20.0f;
}

void UIScreen2D::DrawTexture(SDL_Renderer* renderer, SDL_Texture* texture, const Vector2 offset, const float scaleFactor)
{
    const SDL_FRect dstRect {
        .x = offset.x,
        .y = offset.y,
        .w = static_cast<float>(texture->w) * scaleFactor,
        .h = static_cast<float>(texture->h) * scaleFactor
    };

    SDL_RenderTextureRotated(
        renderer, texture,
        nullptr, &dstRect,
        0.0,
        nullptr,
        SDL_FLIP_NONE
        );
}

Button::Button(const std::string& name, Font * font, std::function<void()> onClick, const Vector2& pos, const Vector2& dims) : mOnClick(std::move(onClick)), mFont(font), mPosition(pos), mDimensions(dims)
{
    SetName(name);
}

Button::~Button()
{
    if (mNameTex)
    {
        SDL_DestroyTexture(mNameTex);
        // delete mNameTex;
    }
}

void Button::SetName(const std::string& name)
{
    mName = name;

    if (mNameTex)
    {
        SDL_DestroyTexture(mNameTex);
        delete mNameTex;
        mNameTex = nullptr;
    }
    mNameTex = mFont->RenderText(mName, Color::White);
}

[[nodiscard]] bool Button::ContainsPoint(const Vector2& pt) const
{
    const bool no = pt.x < mPosition.x or pt.x > mPosition.x + mDimensions.x
                    or pt.y < mPosition.y or pt.y > mPosition.y + mDimensions.y;
    return !no;
}

void Button::OnClick() const
{
    if (mOnClick)
        mOnClick();
}