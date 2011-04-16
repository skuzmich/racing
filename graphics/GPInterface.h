#ifndef _GPINTERFACE_H_
  #define _GPINTERFACE_H_
class GPInterface {
 public:
  GPInterface();
  ~GPInterface();
  // gr_w - x-size of graphics coordinate system
  // gr_h - y-size of graphics coordinate system
  // ph_w - x-size of physics coordinate system
  // ph_h - y-size of physics coordinate system
  bool Init(int gr_w, int gr_h, int ph_w, int ph_h);
  
  // conversion from "physics" to "graphics" coordinates
  int gr_coordinate_x(float phys_coordinate_x);
  int gr_coordinate_y(float phys_coordinate_y);
  
 private:
  float scale_x_;
  float scale_y_;
  
};

#endif
