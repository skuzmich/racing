#include "Predecls.h"
#include "Event.h"
#include "Graphics.h"

int main() {
  Graphics *gr = Graphics::Create(640, 480);
  
  struct car_control_keys tmp;
  Event my_event;
  
  while(my_event.running()) {
    
    my_event.CheckEvents();
    if(my_event.fullscreen()) {
      printf("Should be fullscreen mode\n");
    } else {
        printf("Should be window mode\n");
      }
    tmp = my_event.control_keys_state();
    printf("%d %d %d %d\n", tmp.up, tmp.down, tmp.right, tmp.left);
    SDL_Delay(100);
  }

  return 0;
}

