#ifndef Easer_h
#define Easer_h

class Easer {
  float output = 0.0f;
  float delta = 0.0f;
  float easing = 0.1f;
  public:
    Easer();
    
    float Process(float input) {
      delta = input - output;
      output += delta * easing;
      return output;
    }

    void setFactor(float factor) {
      easing = min(max(0.00001f, factor), 1.0f);
    }
};

Easer::Easer() {

};

#endif