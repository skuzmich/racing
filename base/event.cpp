// Copyright (C) 2011 Horoshenkih Sergey
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "./event.h"

Event::Event() {
  running_ = true;
  fullscreen_ = false;

  control_keys_state_.up = false;
  control_keys_state_.down = false;
  control_keys_state_.left = false;
  control_keys_state_.right = false;
}

Event::~Event() {
}

void Event::CheckEvents() {
  while (SDL_PollEvent(&event_)) {
    OnEvent();
  }
}

void Event::OnEvent() {
  switch (event_.type) {
    case SDL_ACTIVEEVENT: {
      switch (event_.active.state) {
        case SDL_APPMOUSEFOCUS: {
          if (event_.active.gain)
            OnMouseFocus();
          else
            OnMouseBlur();

          break;
        }
        case SDL_APPINPUTFOCUS: {
          if (event_.active.gain)
            OnInputFocus();
          else
            OnInputBlur();

          break;
        }
        case SDL_APPACTIVE: {
          if (event_.active.gain)
            OnRestore();
          else
            OnMinimize();

          break;
        }
      }
      break;
    }

    case SDL_KEYDOWN: {
      OnKeyDown(event_.key.keysym.sym,
                event_.key.keysym.mod,
                event_.key.keysym.unicode);
      break;
    }

    case SDL_KEYUP: {
      OnKeyUp(event_.key.keysym.sym,
              event_.key.keysym.mod,
              event_.key.keysym.unicode);
      break;
    }

    case SDL_MOUSEMOTION: {
      OnMouseMove(event_.motion.x,
                  event_.motion.y,
                  event_.motion.xrel,
                  event_.motion.yrel,
                  event_.motion.state&SDL_BUTTON(SDL_BUTTON_LEFT)   != 0,
                  event_.motion.state&SDL_BUTTON(SDL_BUTTON_RIGHT)  != 0,
                  event_.motion.state&SDL_BUTTON(SDL_BUTTON_MIDDLE) != 0);
      break;
    }

    case SDL_MOUSEBUTTONDOWN: {
      switch (event_.button.button) {
        case SDL_BUTTON_LEFT: {
          OnLButtonDown(event_.button.x, event_.button.y);
          break;
        }
        case SDL_BUTTON_RIGHT: {
          OnRButtonDown(event_.button.x, event_.button.y);
          break;
        }
        case SDL_BUTTON_MIDDLE: {
          OnMButtonDown(event_.button.x, event_.button.y);
          break;
        }
      }
      break;
    }

    case SDL_MOUSEBUTTONUP: {
      switch (event_.button.button) {
        case SDL_BUTTON_LEFT: {
          OnLButtonUp(event_.button.x, event_.button.y);
          break;
        }
        case SDL_BUTTON_RIGHT: {
          OnRButtonUp(event_.button.x, event_.button.y);
          break;
        }
        case SDL_BUTTON_MIDDLE: {
          OnMButtonUp(event_.button.x, event_.button.y);
          break;
        }
      }
      break;
    }

    case SDL_JOYAXISMOTION: {
      OnJoyAxis(event_.jaxis.which, event_.jaxis.axis, event_.jaxis.value);
      break;
    }

    case SDL_JOYBALLMOTION: {
      OnJoyBall(event_.jball.which,
                event_.jball.ball,
                event_.jball.xrel,
                event_.jball.yrel);
      break;
    }

    case SDL_JOYHATMOTION: {
      OnJoyHat(event_.jhat.which,
               event_.jhat.hat,
               event_.jhat.value);
      break;
    }
    case SDL_JOYBUTTONDOWN: {
      OnJoyButtonDown(event_.jbutton.which,
                      event_.jbutton.button);
      break;
    }

    case SDL_JOYBUTTONUP: {
      OnJoyButtonUp(event_.jbutton.which,
                    event_.jbutton.button);
      break;
    }

    case SDL_QUIT: {
      OnExit();
      break;
    }

    case SDL_SYSWMEVENT: {
      break;
    }

    case SDL_VIDEORESIZE: {
      OnResize(event_.resize.w,
               event_.resize.h);
      break;
    }

    case SDL_VIDEOEXPOSE: {
      OnExpose();
      break;
    }

    default: {
      OnUser(event_.user.type,
             event_.user.code,
             event_.user.data1,
             event_.user.data2);
      break;
    }
  }
}

void Event::SetControlKeysState() {
  switch (event_.type) {
    case SDL_KEYDOWN: {
      switch (event_.key.keysym.sym) {
        case SDLK_UP: control_keys_state_.up = true; break;
        case SDLK_DOWN: control_keys_state_.down = true; break;
        case SDLK_LEFT: control_keys_state_.left = true; break;
        case SDLK_RIGHT: control_keys_state_.right = true; break;
      }
      break;
    }

    case SDL_KEYUP: {
      switch (event_.key.keysym.sym) {
        case SDLK_UP: control_keys_state_.up = false; break;
        case SDLK_DOWN: control_keys_state_.down = false; break;
        case SDLK_LEFT: control_keys_state_.left = false; break;
        case SDLK_RIGHT: control_keys_state_.right = false; break;
      }
      break;
    }
  }
}

car_control_keys Event::ControlKeysState() {
  return control_keys_state_;
}

bool Event::fullscreen() {
  return fullscreen_;
}

bool Event::running() {
  return running_;
}

void Event::OnInputFocus() {
}

void Event::OnInputBlur() {
}

void Event::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {
  switch (sym) {
    case SDLK_UP: control_keys_state_.up = true; break;
    case SDLK_DOWN: control_keys_state_.down = true; break;
    case SDLK_LEFT: control_keys_state_.left = true; break;
    case SDLK_RIGHT: control_keys_state_.right = true; break;

    case SDLK_ESCAPE: OnExit(); break;
    case SDLK_F11: fullscreen_ = !fullscreen_;
  }
}

void Event::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) {
  switch (sym) {
    case SDLK_UP: control_keys_state_.up = false; break;
    case SDLK_DOWN: control_keys_state_.down = false; break;
    case SDLK_LEFT: control_keys_state_.left = false; break;
    case SDLK_RIGHT: control_keys_state_.right = false; break;
  }
}

void Event::OnMouseFocus() {
}

void Event::OnMouseBlur() {
}

void Event::OnMouseMove(int mX, int mY,
                        int relX, int relY,
                        bool Left, bool Right,
                        bool Middle) {
}

void Event::OnMouseWheel(bool Up, bool Down) {
}

void Event::OnLButtonDown(int mX, int mY) {
}

void Event::OnLButtonUp(int mX, int mY) {
}

void Event::OnRButtonDown(int mX, int mY) {
}

void Event::OnRButtonUp(int mX, int mY) {
}

void Event::OnMButtonDown(int mX, int mY) {
}

void Event::OnMButtonUp(int mX, int mY) {
}

void Event::OnJoyAxis(Uint8 which, Uint8 axis, Sint16 value) {
}

void Event::OnJoyButtonDown(Uint8 which, Uint8 button) {
}

void Event::OnJoyButtonUp(Uint8 which, Uint8 button) {
}

void Event::OnJoyHat(Uint8 which, Uint8 hat, Uint8 value) {
}

void Event::OnJoyBall(Uint8 which, Uint8 ball, Sint16 xrel, Sint16 yrel) {
}

void Event::OnMinimize() {
}

void Event::OnRestore() {
}

void Event::OnResize(int w, int h) {
}

void Event::OnExpose() {
}

void Event::OnExit() {
  running_ = false;
}

void Event::OnUser(Uint8 type, int code, void* data1, void* data2) {
}
