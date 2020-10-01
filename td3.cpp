#include <iostream>
#include "td3.hpp"
#include "support.hpp"
#include <stdlib.h>
#include <math.h>       // sin, cos

using namespace std;

using namespace support;

double* extend_array(double* array, int length, int new_size) {
  // IMPLEMENT YOUR FUNCTION HERE
    double* new_arr = new double[new_size];
    for (int i = 0; i<new_size; i++){
        if (i<length){
           new_arr[i] = *(array + i);
        } else {
            new_arr[i] = 0;
        }

    }

    delete array;

    return new_arr;


}

double* shrink_array(double* array, int length, int new_size) {
  // IMPLEMENT YOUR FUNCTION HERE+

  double* small_arr = new double[new_size];
  for(int i = 0; i<new_size;i++){
      small_arr[i] = *(array + i);
  }
  delete [] array;
  return small_arr;
}

double* append_to_array(double element,
                        double* array,
                        int &current_size,
                        int &max_size) {
  // IMPLEMENT YOUR FUNCTION HERE

  if (current_size == max_size){
      // Here we need to extend the array
      double* bigger_arr;
      bigger_arr = extend_array(array, current_size, current_size+5);
      max_size += 5;
      *(bigger_arr + current_size) = element;
      current_size += 1;
      return bigger_arr;
  } else {
      // In this case there is no need to extend the array
      // so we only add the element
      *(array + current_size) = element;
      current_size += 1;
      return array;
  }

  return NULL; // YOU CAN CHANGE THIS
}

double* remove_from_array(double* array,
                          int &total_elements,
                          int &array_size) {
  // IMPLEMENT YOUR FUNCTION HERE
    if(total_elements==0){
        return array;
    }
    total_elements -= 1;
    if (array_size-total_elements >= 5){
        // Here we need to shring the array
        double* smaller_array;
        smaller_array = shrink_array(array,total_elements,array_size-5);
        array_size -= 5;
        return smaller_array;
    } else {
        // In this case there is no need to shrink the array
        // so we only change the total_elements
        return array;
    }
}

bool simulate_projectile(const double magnitude, const double angle,
                         const double simulation_interval,
                         double *targets, int &tot_targets,
                         int *obstacles, int tot_obstacles,
                         double* &telemetry,
                         int &telemetry_current_size,
                         int &telemetry_max_size) {
  // YOU CAN MODIFY THIS FUNCTION TO RECORD THE TELEMETRY

  bool hit_target, hit_obstacle;
  double v0_x, v0_y, x, y, t;
  double PI = 3.14159265;
  double g = 9.8;

  v0_x = magnitude * cos(angle * PI / 180);
  v0_y = magnitude * sin(angle * PI / 180);

  t = 0;
  x = 0;
  y = 0;

  hit_target = false;
  hit_obstacle = false;
  while (y >= 0 && (! hit_target) && (! hit_obstacle)) {
    double * target_coordinates = find_collision(x, y, targets, tot_targets);
    if (target_coordinates != NULL) {
      remove_target(targets, tot_targets, target_coordinates);
      hit_target = true;
    } else if (find_collision(x, y, obstacles, tot_obstacles) != NULL) {
      hit_obstacle = true;
    } else {
      t = t + simulation_interval;
      y = v0_y * t  - 0.5 * g * t * t;
      x = v0_x * t;
    }
  }

  return hit_target;
}

void merge_telemetry(double **telemetries,
                     int tot_telemetries,
                     int *telemetries_sizes,
                     double* &telemetry,
                     int &telemetry_current_size,
                     int &telemetry_max_size) {
  // IMPLEMENT YOUR FUNCTION HERE
}
