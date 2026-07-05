#include <stdlib.h>
#include <unistd.h>
#include <cstdlib>
#include <iostream>

using namespace std;

class Accelerator;
const int dummy = 0;

class Engine {
 private:
  virtual void acceleration_output() = 0;
  virtual void reduce_output() = 0;
  friend class Accelerator;
};

class IcEngine : public Engine {
 private:
  virtual void acceleration_output() = 0;
  virtual void reduce_output() = 0;
};

class GsEngine : public IcEngine {
 private:
  void acceleration_output() override { increasing_fuel(); };
  void reduce_output() override { decreasing_fuel(); };
  void increasing_fuel() { increasing_piston_speed(); };
  void decreasing_fuel() { decreasing_piston_speed(); };
  void increasing_piston_speed() { cout << "increasing_piston_speed" << endl; };
  void decreasing_piston_speed() { cout << "decreasing_piston_speed" << endl; };
};

class ElecEngine : public Engine {
 private:
  void acceleration_output() override { increasing_motor_speed(); }
  void reduce_output() override { decreasing_motor_speed(); };
  void increasing_motor_speed() { cout << "increasing_motor_speed" << endl; };
  void decreasing_motor_speed() { cout << "decreasing_motor_speed" << endl; };
};

class HydrogenEngine : public IcEngine {
private:
  void acceleration_output() override { increasing_hydro(); };
  void reduce_output() override { decreasing_hydro(); };
  void increasing_hydro() { increasing_piston_speed(); };
  void decreasing_hydro() { decreasing_piston_speed(); };
  void increasing_piston_speed() { cout << "increasing_piston_speed" << endl; };
  void decreasing_piston_speed() { cout << "decreasing_piston_speed" << endl; };
};

class BreakSystem {
 public:
  void pushing_break(Accelerator& accelerator_obj);
};

class Accelerator {
 public:
  Accelerator(Engine& engine) : my_engine(engine) {};
  void acceleration_output() { my_engine.acceleration_output(); };
  void set_engine(Engine& engine) { my_engine = engine; };

 private:
  Engine& my_engine;

  void reduce_output();
  friend void BreakSystem::pushing_break(Accelerator& accelerator_obj);
};

void BreakSystem::pushing_break(Accelerator& accelerator_obj) {
  accelerator_obj.reduce_output();
}

void Accelerator::reduce_output() {
  my_engine.reduce_output();
}

class Sensor {
 public:
  int inquiring_range() { return dummy; };
  int inquiring_current_speed() { return dummy; };
};

class CruiseController {
 public:
  CruiseController(Sensor& sensor,
                   Accelerator& accelerator,
                   BreakSystem& break_system)
      : my_sensor(sensor),
        my_accelerator(accelerator),
        my_break_system(break_system) {
    acceleration_adjusting_period = 1;
    user_target_speed = 0;
    keep_cruise = false;
  };

  void do_cruise();
  void stop_cruise() { keep_cruise = false; };
  void set_target_speed(int speed) { user_target_speed = speed; };

 private:
  int calculating_fit_speed(int range, int original_target_speed) {
    return dummy;
  };
  void acceleration_adjusting(int target_speed, int current_speed);

  Sensor& my_sensor;
  Accelerator& my_accelerator;
  BreakSystem& my_break_system;

  int user_target_speed;
  int acceleration_adjusting_period;
  bool keep_cruise;
};

void CruiseController::do_cruise() {
  int range = dummy, current_speed = dummy;
  keep_cruise = true;

  while (keep_cruise) {
    range = my_sensor.inquiring_range();
    current_speed = my_sensor.inquiring_current_speed();
    acceleration_adjusting(calculating_fit_speed(range, current_speed),
                           user_target_speed);
    sleep(acceleration_adjusting_period / 1000);
    keep_cruise = false;
  }
}

void CruiseController::acceleration_adjusting(int current_speed,
                                              int target_speed) {
  if (current_speed == target_speed) {
    return;
  }
  if (target_speed > current_speed) {
    my_accelerator.acceleration_output();
    return;
  }
  my_break_system.pushing_break(my_accelerator);
}

class Car {
 public:
  Car(Engine& engine,
      Sensor& sensor,
      BreakSystem& break_system,
      Accelerator& accelerator,
      CruiseController& cruise_contrller)
      : my_engine(engine),
        my_sensor(sensor),
        my_break_system(break_system),
        my_accelerator(accelerator),
        my_curise_controller(cruise_contrller) {};
  void do_cruise();
  void stop();

 private:
  Engine& my_engine;
  Sensor& my_sensor;
  BreakSystem& my_break_system;
  Accelerator& my_accelerator;
  CruiseController& my_curise_controller;
};

void Car::stop() {
  my_break_system.pushing_break(my_accelerator);
}

void Car::do_cruise() {
  my_curise_controller.set_target_speed(100);
  my_curise_controller.do_cruise();
}

int main(int argc, char** argv) {
  GsEngine my_engine;
  Sensor my_sensor;
  BreakSystem my_break_system;
  Accelerator my_accelerator(my_engine);
  CruiseController my_cruise_controller(my_sensor, my_accelerator,
                                        my_break_system);
  Car my_car(my_engine, my_sensor, my_break_system, my_accelerator,
             my_cruise_controller);

  my_car.do_cruise();
  return 0;
}