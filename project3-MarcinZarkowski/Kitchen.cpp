/**
 * @file Dish.cpp
 * @brief This file contains the implementation of the Kitchen class in a virtual bistro simulation.
 * 
 *The Kitchen class implements the ArrayBag class to store dishes in the "Kitchen".
 *The Kitchen class uses multiple inherited methods from ArrayBag to modify the Kitchen's Dishes. 
 * It provides constructors, accessor and mutator functions, and a display function to manage and present
 * the details of a Kitchen.
 * 
 * @date [10/8/2024]
 * @author [Marcin Zarkowski]
 */
#include "ArrayBag.hpp"
#include "Dish.hpp"
#include <string>
#include <iostream>
#include "Kitchen.hpp"
#include <vector>
#include <cmath>
/**
 * Default constructor.
 * Default-initializes all private members.
 */
Kitchen::Kitchen():ArrayBag(){
   totalprep_time=0;
   countelaborate=0;
}

/**
 * @param : A reference to a `Dish` being added to the kitchen.
 * @post : If the given `Dish` is not already in the kitchen, adds the
`Dish` to the kitchen and updates the preparation time sum and elaborate
dish count if the dish is elaborate.
* @return : Returns true if a `Dish` was successfully added to the
kitchen, false otherwise.
Hint: Use the above definition of equality to help determine if a
`Dish` is already in the kitchen.
*/
bool Kitchen::newOrder(const Dish& dish){
    bool ans = add(dish);
    if (ans){
        totalprep_time += dish.getPrepTime();
        if (dish.getIngredients().size()>=5 && dish.getPrepTime()>=60){
            countelaborate++;
        }
        return ans;
    }
    return ans;
}

/**
 * @param : A reference to a `Dish` leaving the kitchen.
 * @return : Returns true if a dish was successfully removed from the
kitchen (i.e.,
items_), false otherwise.
* @post : Removes the dish from the kitchen and updates the preparation
time sum.
If the `Dish` is elaborate, it also updates the elaborate count.
*/
bool Kitchen::serveDish(const Dish& dish){
    bool ans = remove(dish);
    if (ans){
        totalprep_time -= dish.getPrepTime();
       
        if (dish.getIngredients().size()>=5 && dish.getPrepTime()>=60){
            countelaborate--;
        }
        return ans;
    }
    return ans;
}

/**
 * @return : The integer sum of preparation times for all the dishes
currently in the kitchen.
*/
int Kitchen::getPrepTimeSum() const{
    return totalprep_time;
}

/**
 * @return : The average preparation time (int) of all the dishes in the
kitchen. The lowest possible average prep time should be 0.
* @post : Computes the average preparation time (double) of the kitchen
rounded to the NEAREST integer.
*/
int Kitchen::calculateAvgPrepTime() const{
    float total=0;
    if (getCurrentSize()==0){
        return 0;
    }

    for (int i=0; i<getCurrentSize(); i++){
        total += items_[i].getPrepTime();
    }  
    total = total/getCurrentSize();

    if (total-(int)total>=0.5){
        return (int)total+1;
    }
    
    return (int)round(total);
}

/**
 * @return : The integer count of the elaborate dishes in the kitchen.
*/
int Kitchen::elaborateDishCount() const{
    return countelaborate;
}

/**
 * @return : The percentage (double) of all the elaborate dishes in the
kitchen. The lowest possible percentage should be 0%.
* @post : Computes the percentage of elaborate dishes in the kitchen
rounded up to 2 decimal places.
*/
double Kitchen::calculateElaboratePercentage() const{
    if(getCurrentSize()==0){
        return 0.00;
    }
    double percentage = (double)countelaborate / getCurrentSize()* 100;

    return round(percentage * 100) / 100;
}

/**
 * @param : A reference to a string representing a cuisine type with a
value in
["ITALIAN", "MEXICAN", "CHINESE", "INDIAN", "AMERICAN",
"FRENCH", "OTHER"].
* @return : An integer tally of the number of dishes in the kitchen of the
given cuisine type.
If the argument string does not match one of the expected
cuisine types, the tally is zero.
NOTE: No pre-processing of the input string necessary, only
uppercase input will match.
*/
int Kitchen::tallyCuisineTypes(const std::string& cuisineType){
    std::vector<std::string> arr = {"ITALIAN", "MEXICAN", "CHINESE", "INDIAN", "AMERICAN", "FRENCH", "OTHER"};
    bool found = false;
    for (int i=0; i<arr.size(); i++){
        if (cuisineType == arr[i]){
            found = true;
            break;
        }
    }
    if (found == false){
        return 0;
    }
    //loop through and itterate count if is couisine type
    int count = 0;
    for (int i=0; i<getCurrentSize(); i++){
        if (items_[i].getCuisineType() == cuisineType){
            count++;
        }
    }
    return count;
    



}

/**
 * @param : A reference to an integer representing the preparation time
threshold of the dishes to be removed from the kitchen.
* @post : Removes all dishes from the kitchen whose preparation time is
less than the given time.
* @return : The number of dishes removed from the kitchen.
*/
int Kitchen::releaseDishesBelowPrepTime(const int& prep){
    int count = 0;
    int size=getCurrentSize();
    int pointer=0;
    while (pointer<size){
        if (items_[pointer].getPrepTime() < prep){
            remove(items_[pointer]);
            count++;
            size--;
        }
        else{
            pointer++;
        }    

    }
    return count;
}

/**
 * @param : A reference to a string representing a cuisine type with a
value in
["ITALIAN", "MEXICAN", "CHINESE", "INDIAN", "AMERICAN",
"FRENCH", "OTHER"].
* @post : Removes all dishes from the kitchen whose cuisine type matches
the given type.
* @return : The number of dishes removed from the kitchen.
NOTE: No pre-processing of the input string necessary, only
Testing
Although you will no longer submit your test file, you must continue to thoroughly and
methodically test your code.
Start by stubbing all expected functions. Have all function declarations in the .hpp file and
stubs for all functions in the .cpp file. When submitted as such, your program will compile,
although you will fail all tests, since you have not implemented any functions yet. If your
uppercase input will match.
If the input string does not match one of the expected cuisine
types, do not remove any dishes.
*/
int Kitchen::releaseDishesOfCuisineType(const std::string& cuisineType){
    std::vector<std::string> arr = {"ITALIAN", "MEXICAN", "CHINESE", "INDIAN", "AMERICAN", "FRENCH", "OTHER"};
    bool found = false;
    for (int i=0; i<arr.size(); i++){
        if (cuisineType == arr[i]){
            found = true;
            break;
        }
    }
    if (found == false){
        return 0;
    }
    int count = 0;
    int size=getCurrentSize();
    int pointer=0;

    //loop through, if is cuisine type, remove and increment count and decrease size ,
    //otherwise just increment pointer to search the next spot in the array 
    while (pointer<size){
        if (items_[pointer].getCuisineType() == cuisineType){
            remove(items_[pointer]);
            count++;
            size--;
        }
        else{
            pointer++;
        }    

    }
    return count;
    
}

/**
 * @post : Outputs a report of the dishes currently in the kitchen in the
form:
"ITALIAN: {x}\nMEXICAN: {x}\nCHINESE: {x}\nINDIAN:
{x}\nAMERICAN: {x}\nFRENCH: {x}\nOTHER: {x}\n\n
AVERAGE PREP TIME: {x}\ELABORATE: {x}%\n"
Note that the average preparation time should be rounded to the
NEAREST integer, and the
percentage of elaborate dishes in the kitchen should be rounded
to 2 decimal places.

Example output:
ITALIAN: 2
MEXICAN: 3
CHINESE: 2
INDIAN: 1
AMERICAN: 1
FRENCH: 2
OTHER: 2
AVERAGE PREP TIME: 62
ELABORATE DISHES: 53.85%
*/
void Kitchen::kitchenReport(){
    std::vector<std::string> arr = {"ITALIAN", "MEXICAN", "CHINESE", "INDIAN", "AMERICAN", "FRENCH", "OTHER"};

    for (int i=0; i<7; i++){
        std::cout << arr[i] << ": " << tallyCuisineTypes(arr[i]) << "\n";
    }
    std::cout << "AVERAGE PREP TIME: " << calculateAvgPrepTime() << "\n";
    std::cout << "ELABORATE DISHES: " << calculateElaboratePercentage()<< "%\n";
};
