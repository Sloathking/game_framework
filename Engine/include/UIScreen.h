//
// Created by sloath on 10/28/26.
//

#ifndef UISCREEN_H
#define UISCREEN_H

#include "Engine.h"
#include "Math.h"
#include <SDL3/SDL.h>
#include <functional>
#include <string>

class Button
{
public:
    Button(const std::string& name, Font * font, std::function<void()> onClick, const Vector2& pos, const Vector2& dims);
    ~Button();

    void SetName(const std::string& name);

    [[nodiscard]] SDL_Texture* GetNameTex() const { return mNameTex; }
    [[nodiscard]] const Vector2& GetPosition() const { return mPosition; }

    [[nodiscard]] bool GetHighlighted() const { return mHighlighted; }
    void SetHighlighted(const bool sel) { mHighlighted = sel; }

    [[nodiscard]] bool ContainsPoint(const Vector2& pt) const;

    void OnClick() const;

private:
    std::function<void()> mOnClick;
    std::string mName;
    SDL_Texture* mNameTex{nullptr};
    Font* mFont;
    Vector2 mPosition;
    Vector2 mDimensions;
    bool mHighlighted{false};
};

class UIScreen
{
public:
    enum UIState { EActive, EClosing };

    explicit UIScreen(Engine * game);
    virtual ~UIScreen();

    // UIScreen subclasses can override these
    virtual void Update(float deltaTime);
    virtual void Draw(SDL_Renderer* renderer, float scaleFactor);
    virtual void ProcessInput(const struct InputState& state);

    void Close() { mState = EClosing; }

    // getters / setters
    [[nodiscard]] UIState GetState() const { return mState; }

    void SetTitle(const std::string& text, const Vector3& color = Color::White, float pointSize = 40.f);

    void AddButton(const std::string& name, std::function<void()> onClick);

protected:
    static void DrawTexture(SDL_Renderer* renderer, SDL_Texture* texture, Vector2 offset, float scaleFactor);
    void SetRelativeMouseMode(const bool relative) const { mGame->SetRelativeMouseMode(relative); }

    Engine* mGame{};
    Font* mFont{};
    SDL_Texture* mBackground{};
    SDL_Texture* mTitle{};
    SDL_Texture* mButtonOn{};
    SDL_Texture* mButtonOff{};

    Vector2 mTitlePos{};
    Vector2 mNextButtonPos{};
    Vector2 mBGPos{};

    UIState mState{};

    std::vector<Button *> mButtons{};
};

#endif // UISCREEN_H
