#include "event.h"


void OnEvent(SDL_Event* Event) {
  switch(Event->type) {
    case SDL_ACTIVEEVENT: {
      switch(Event->active.state) {
        case SDL_APPMOUSEFOCUS: {
          if ( Event->active.gain )   OnMouseFocus();
          else        OnMouseBlur();

          break;
        }
        case SDL_APPINPUTFOCUS: {
          if ( Event->active.gain )   OnInputFocus();
          else        OnInputBlur();

          break;
        }
        case SDL_APPACTIVE: {
          if ( Event->active.gain )   OnRestore();
          else        OnMinimize();

          break;
        }
      }
      break;
    }

    case SDL_KEYDOWN: {
      OnKeyDown(Event->key.keysym.sym,Event->key.keysym.mod,Event->key.keysym.unicode);
      break;
    }

    case SDL_KEYUP: {
      OnKeyUp(Event->key.keysym.sym,Event->key.keysym.mod,Event->key.keysym.unicode);
      break;
    }

    case SDL_MOUSEMOTION: {
      OnMouseMove(Event->motion.x,Event->motion.y,Event->motion.xrel,Event->motion.yrel,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_LEFT))!=0,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_RIGHT))!=0,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_MIDDLE))!=0);
      break;
    }

    case SDL_MOUSEBUTTONDOWN: {
      switch(Event->button.button) {
        case SDL_BUTTON_LEFT: {
          OnLButtonDown(Event->button.x,Event->button.y);
          break;
        }
        case SDL_BUTTON_RIGHT: {
          OnRButtonDown(Event->button.x,Event->button.y);
          break;
        }
        case SDL_BUTTON_MIDDLE: {
          OnMButtonDown(Event->button.x,Event->button.y);
          break;
        }
      }
      break;
    }

    case SDL_MOUSEBUTTONUP: {
      switch(Event->button.button) {
        case SDL_BUTTON_LEFT: {
          OnLButtonUp(Event->button.x,Event->button.y);
          break;
        }
        case SDL_BUTTON_RIGHT: {
          OnRButtonUp(Event->button.x,Event->button.y);
          break;
        }
        case SDL_BUTTON_MIDDLE: {
          OnMButtonUp(Event->button.x,Event->button.y);
          break;
        }
      }
      break;
    }

    case SDL_JOYAXISMOTION: {
      OnJoyAxis(Event->jaxis.which,Event->jaxis.axis,Event->jaxis.value);
      break;
    }

    case SDL_JOYBALLMOTION: {
      OnJoyBall(Event->jball.which,Event->jball.ball,Event->jball.xrel,Event->jball.yrel);
      break;
    }

    case SDL_JOYHATMOTION: {
      OnJoyHat(Event->jhat.which,Event->jhat.hat,Event->jhat.value);
      break;
    }
    case SDL_JOYBUTTONDOWN: {
      OnJoyButtonDown(Event->jbutton.which,Event->jbutton.button);
      break;
    }

    case SDL_JOYBUTTONUP: {
      OnJoyButtonUp(Event->jbutton.which,Event->jbutton.button);
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
      OnResize(Event->resize.w,Event->resize.h);
      break;
    }

    case SDL_VIDEOEXPOSE: {
      OnExpose();
      break;
    }

    default: {
      OnUser(Event->user.type,Event->user.code,Event->user.data1,Event->user.data2);
      break;
    }
  }
}

///////////////////////////////////////////

struct car_control_keys GetKeyboardState() {
  SDL_Event Event;
  static car_control_keys ret;
  while(SDL_PollEvent(&Event)) {
    switch(Event.type) {
        
      case SDL_KEYDOWN: {
        switch(Event.key.keysym.sym) {
          case SDLK_UP: ret.up = true; break;
          case SDLK_DOWN: ret.down = true; break;
          case SDLK_LEFT: ret.left = true; break;
          case SDLK_RIGHT: ret.right = true; break;
        }
        break;
      }

      case SDL_KEYUP: {
        switch(Event.key.keysym.sym) {
          case SDLK_UP: ret.up = false; break;
          case SDLK_DOWN: ret.down = false; break;
          case SDLK_LEFT: ret.left = false; break;
          case SDLK_RIGHT: ret.right = false; break;
        }
        break;
      }
      
    }
  }

  return ret;
}

////////////////////////////////////
void OnInputFocus() {
}

void OnInputBlur() {
}

void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {
}

void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) {
}

void OnMouseFocus() {
}

void OnMouseBlur() {
}

void OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle) {
}

void OnMouseWheel(bool Up, bool Down) {
}

void OnLButtonDown(int mX, int mY) {
}

void OnLButtonUp(int mX, int mY) {
}

void OnRButtonDown(int mX, int mY) {
}

void OnRButtonUp(int mX, int mY) {
}

void OnMButtonDown(int mX, int mY) {
}

void OnMButtonUp(int mX, int mY) {
}

void OnJoyAxis(Uint8 which,Uint8 axis,Sint16 value) {
}

void OnJoyButtonDown(Uint8 which,Uint8 button) {
}

void OnJoyButtonUp(Uint8 which,Uint8 button) {
}

void OnJoyHat(Uint8 which,Uint8 hat,Uint8 value) {
}

void OnJoyBall(Uint8 which,Uint8 ball,Sint16 xrel,Sint16 yrel) {
}

void OnMinimize() {
}

void OnRestore() {
}

void OnResize(int w,int h) {
}

void OnExpose() {
}

void OnExit() {
}

void OnUser(Uint8 type, int code, void* data1, void* data2) {
}
