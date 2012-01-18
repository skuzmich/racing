#include "predecls.h"
#include "fileparser.h"
#include "world.h"
#include "event.h"
#include "Graphics.h"


World::World(std::string config_file_path, Settings * settings, Renderer * renderer ) {
  _renderer = renderer;
  _settings = settings;

  std::ifstream fd(config_file_path.c_str());

  b2Vec2 gravity = Readb2Vec2(&fd);

  // TODO: Make configurable;
  bool do_sleep  = true;

  _world = new b2World(gravity, true);

  std::string track_config_path = GetLine(&fd);
  std::string track_image_path  = GetLine(&fd);
  
  std::cout << "Track config path: " << track_config_path << std::endl;
  std::cout << "Track image  path: " << track_image_path  << std::endl;

  _track = new Track(_world, track_config_path);

  int number_of_cars = ReadInt(&fd); 
  std::cout << "Number of cars: " << number_of_cars << std::endl;

  for (int i = 0; i < number_of_cars; i++) {
    std::string car_config_path = GetLine(&fd);
    std::string car_image_path = GetLine(&fd);

    int32 sprite_width = ReadInt(&fd);
    int32 sprite_height = ReadInt(&fd);

    std::cout << "  Car config path: " << car_config_path << std::endl;
    std::cout << "  Car image  path: " << car_image_path  << std::endl;
    std::cout << "  Car sprite size: " << sprite_width << ":"
              << sprite_height  << std::endl;
    _renderer->AddSprite(sprite_width, sprite_height, car_image_path);

    b2Vec2 pos = Readb2Vec2(&fd);
    _cars.push_back(new Car(_world, pos.x, pos.y, _track, car_config_path));

  }
  fd.close();
}

World::~World() {
  delete _world;
  delete _track;
}

void World::Update(Event *event) {
   
  if(event->fullscreen()) {
    _renderer->_graphics->FullscreenOn();
  } else {
    _renderer->_graphics->FullscreenOff();
  }

  for (int i = 0; i < _cars.size(); i++) {
    car_control_keys keys = event->ControlKeysState();
    _cars[i]->SetKeys(keys);
    _cars[i]->Loop();
  }

  _world->Step(_settings->GetTimeStep(), 
               _settings->GetVelIterations(), 
               _settings->GetPosIterations());

}

void World::Render() {
  for (int i = 0; i < _cars.size(); i++) {
    obj_coordinates coordinates = _cars[i]->GetCoordinates();
    _renderer->SetSpriteCoordinates(i,
                      coordinates.x+2,
                      coordinates.y,
                      coordinates.angle + 3.14);
  }
  _renderer->Render();

}
