/**
 * @file Dish.cpp
 * @brief This file contains the definition of the Kitchen class in a virtual bistro simulation.
 * 
 *The Kitchen class implements the ArrayBag class to store dishes in the "Kitchen".
 *The Kitchen class uses multiple inherited methods from ArrayBag to modify the Kitchen's Dishes. 
 *It provides constructors, accessor and mutator functions, and a display function to manage and present
 * the details of a Kitchen.
 * 
 * 
 * @date [10/25/2024]
 * @author [Marcin Zarkowski]
 */

#ifndef KITCHEN_HPP
#define KITCHEN_HPP

#include "ArrayBag.hpp"
#include "Dish.hpp"
// for round
#include <cmath>

class Kitchen : public ArrayBag<Dish*> {
    public:
        /**
        * Parameterized constructor.
        * @param filename The name of the input CSV file containing dish
        information.
        * @pre The CSV file must be properly formatted.
        * @post Initializes the kitchen by reading dishes from the CSV file and
        storing them as `Dish*`.
        */
        Kitchen(const std::string& filename);
        Kitchen();

        /**
        * Adjusts all dishes in the kitchen based on the specified dietary
        accommodation.
        * @param request A DietaryRequest structure specifying the dietary
        accommodations.
        * @post Calls the `dietaryAccommodations()` method on each dish in the
        kitchen to adjust them accordingly.
        */
        void dietaryAdjustment(Dish::DietaryRequest request);

        /**
        * Displays all dishes currently in the kitchen.
        * @post Calls the `display()` method of each dish.
        */
        void displayMenu() const;

        bool newOrder(Dish* new_dish);
        bool serveDish(Dish* dish_to_remove);
        int getPrepTimeSum() const;
        int calculateAvgPrepTime() const;
        int elaborateDishCount() const;
        double calculateElaboratePercentage() const;
        int tallyCuisineTypes(const std::string& cuisine_type) const;
        int releaseDishesBelowPrepTime(const int& prep_time);
        int releaseDishesOfCuisineType(const std::string& cuisine_type);
        void kitchenReport() const;

        /**
        * Destructor.
        * @post Deallocates all dynamically allocated dishes to prevent memory
        leaks.
        */
        ~Kitchen();
    private:
        int total_prep_time_;
        int count_elaborate_;
    
};

#endif // KITCHEN_HPP