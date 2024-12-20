/**
 * @file Dish.cpp
 * @brief This file contains the definition of the Kitchen class in a virtual bistro simulation.
 * 
 *This file tests the Kitchen class which inherits from ArrayBag. 
 * 
 * 
 * @date [10/8/2024]
 * @author [Marcin Zarkowski]
 */

#include "Kitchen.hpp"
#include <iostream>


int main(){


    Dish dish("pizza");
    dish.setPrepTime(10);
    Dish Poopie("poopie");
    Poopie.setPrepTime(11);
    std::cout << "Dish prep time: " << dish.getPrepTime()<<" "<<Poopie.getPrepTime() << std::endl;
    Kitchen kitchen;
    kitchen.add(dish);
    kitchen.add(Poopie);
    std::cout << "Current size: " << kitchen.getCurrentSize() << std::endl;
    std::cout << "Average prep time: "<< kitchen.calculateAvgPrepTime()<< std::endl;
    std::cout << std::endl;
    kitchen.kitchenReport();
}