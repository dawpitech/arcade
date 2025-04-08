/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** SDLRenderer.cpp
*/

#include <SDL2/SDL_scancode.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "SDLRenderer.hpp"
#include "ANAL/Events.hpp"
#include "ANAL/IModule.hpp"

arcade::SDLRenderer::SDLRenderer()
    : _window(nullptr)
    , _renderer(nullptr)
    , _events({})
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        throw Exception();
    
    if (TTF_Init() < 0)
        throw Exception();
        
    if (IMG_Init(IMG_INIT_PNG) == 0)
        throw Exception();
        
    this->_window = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                              WINDOW_SIZE * SCALE_FACTOR, WINDOW_SIZE * SCALE_FACTOR,
			      SDL_WINDOW_SHOWN);
    if (this->_window == nullptr)
        throw Exception();
        
    this->_renderer = SDL_CreateRenderer(this->_window, -1, SDL_RENDERER_ACCELERATED);
    if (this->_renderer == nullptr)
        throw Exception();
        
    std::cout << "SDL Init" << std::endl;
}

arcade::SDLRenderer::~SDLRenderer()
{
    if (this->_renderer != nullptr)
        SDL_DestroyRenderer(this->_renderer);
    if (this->_window != nullptr)
        SDL_DestroyWindow(this->_window);
        
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    
    std::cout << "SDL Destroyed" << std::endl;
}

void arcade::SDLRenderer::drawEntity(const ANAL::IEntity& entity)
{
    SDL_Surface* surface = IMG_Load(entity.getAsset().getTexturePath().c_str());
    if (surface == nullptr)
        throw Exception();
        
    SDL_Texture* texture = SDL_CreateTextureFromSurface(this->_renderer, surface);
    SDL_FreeSurface(surface);
    
    if (texture == nullptr)
        throw Exception();
        
    SDL_Rect destRect;
    destRect.x = entity.getPos().x * SCALE_FACTOR;
    destRect.y = entity.getPos().y * SCALE_FACTOR;
    destRect.w = SCALE_FACTOR;
    destRect.h = SCALE_FACTOR;
    
    SDL_RenderCopy(this->_renderer, texture, nullptr, &destRect);
    SDL_DestroyTexture(texture);
}

void arcade::SDLRenderer::drawText(const std::string& str, const ANAL::Vector2<int> pos)
{
    TTF_Font* font = TTF_OpenFont("./assets/fonts/Abordage-Regular.ttf", FONT_SIZE * SCALE_FACTOR);
    if (font == nullptr)
        throw Exception();
        
    SDL_Color color = {255, 255, 255, 255};
    SDL_Surface* surface = TTF_RenderText_Blended(font, str.c_str(), color);
    if (surface == nullptr) {
        TTF_CloseFont(font);
        throw Exception();
    }
    
    SDL_Texture* texture = SDL_CreateTextureFromSurface(this->_renderer, surface);
    SDL_FreeSurface(surface);
    
    if (texture == nullptr) {
        TTF_CloseFont(font);
        throw Exception();
    }
    
    SDL_Rect destRect;
    destRect.x = pos.x * SCALE_FACTOR;
    destRect.y = pos.y * SCALE_FACTOR;
    SDL_QueryTexture(texture, nullptr, nullptr, &destRect.w, &destRect.h);
    
    SDL_RenderCopy(this->_renderer, texture, nullptr, &destRect);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
}

void arcade::SDLRenderer::setWindowTitle(const std::string& title)
{
    SDL_SetWindowTitle(this->_window, title.c_str());
}

void arcade::SDLRenderer::render()
{
    SDL_RenderPresent(this->_renderer);
}

void arcade::SDLRenderer::clear()
{
    SDL_SetRenderDrawColor(this->_renderer, 0, 0, 0, 255);
    SDL_RenderClear(this->_renderer);
}

std::vector<ANAL::Event>& arcade::SDLRenderer::getEvents()
{
    SDL_Event event;
    this->_events.clear();
    
    while (SDL_PollEvent(&event)) {
        ANAL::Event ev;
        
        if (event.type == SDL_QUIT) {
            ev.type = ANAL::EventType::CLOSE;
            this->_events.insert(this->_events.end(), ev);
        } 
        else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
            ev.type = ANAL::EventType::KEYBOARD;
            ANAL::KeyEvent keyEvent;
            keyEvent.state = (event.type == SDL_KEYDOWN) ? ANAL::State::PRESSED : ANAL::State::RELEASED;

            switch (event.key.keysym.sym) {
                case SDLK_UP:
                    keyEvent.key = ANAL::Keys::ARROW_UP;
                    break;
                case SDLK_DOWN:
                    keyEvent.key = ANAL::Keys::ARROW_DOWN;
                    break;
                case SDLK_LEFT:
                    keyEvent.key = ANAL::Keys::ARROW_LEFT;
                    break;
                case SDLK_RIGHT:
                    keyEvent.key = ANAL::Keys::ARROW_RIGHT;
                    break;
                case SDLK_n:
                    keyEvent.key = ANAL::Keys::KEY_N;
                    break;
                case SDLK_b:
                    keyEvent.key = ANAL::Keys::KEY_B;
                    break;
                case SDLK_r:
                    keyEvent.key = ANAL::Keys::KEY_R;
                    break;
                default:
                    continue;
            }
            ev.keyEvent = keyEvent;
            this->_events.insert(this->_events.end(), ev);
        } 
        else if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
            ev.type = ANAL::EventType::MOUSE;
            ANAL::MouseEvent mouseEvent{{0, 0}, ANAL::MouseKeys::LEFT_CLICK, ANAL::State::PRESSED};
            mouseEvent.coords = { event.button.x / 16, event.button.y / 16};
            mouseEvent.state = (event.type == SDL_MOUSEBUTTONDOWN) ? ANAL::State::PRESSED : ANAL::State::RELEASED;

            switch (event.button.button) {
                case SDL_BUTTON_LEFT:
                    mouseEvent.key = ANAL::MouseKeys::LEFT_CLICK;
                    break;
                case SDL_BUTTON_MIDDLE:
                    mouseEvent.key = ANAL::MouseKeys::MIDDLE_CLICK;
                    break;
                case SDL_BUTTON_RIGHT:
                    mouseEvent.key = ANAL::MouseKeys::RIGHT_CLICK;
                    break;
                default:
                    continue;
            }
            ev.mouseEvent = mouseEvent;
            this->_events.insert(this->_events.end(), ev);
        }
    }

    return this->_events;
}

ANAL::ModuleVersion uwu_get_module_version()
    { return ANAL::ModuleVersion::V1_1_0; }

ANAL::ModuleType uwu_get_module_type()
    { return ANAL::ModuleType::RENDERER; }

extern "C" std::unique_ptr<ANAL::IRenderer> uwu_entrypoint_renderer()
    { return std::make_unique<arcade::SDLRenderer>(); }
