#include "Predecls.h"
#include "Event.h"
#include "CGraphics.h"

int main() {
  CGraphics *gr = CGraphics::Create(640, 480);
  
  struct car_control_keys tmp;
  Event my_event;
  
  while(my_event.running()) {
    
    my_event.CheckEvents();
    tmp = my_event.control_keys_state();
    printf("%d %d %d %d\n", tmp.up, tmp.down, tmp.right, tmp.left);
    SDL_Delay(100);
  }

  return 0;
}

