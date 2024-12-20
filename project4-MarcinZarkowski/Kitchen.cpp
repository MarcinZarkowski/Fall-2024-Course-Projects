/**
 * @file Dish.cpp
 * @brief This file contains the implementation of the Kitchen class in a virtual bistro simulation.
 * 
 *The Kitchen class implements the ArrayBag class to store dishes in the "Kitchen".
 *The Kitchen class uses multiple inherited methods from ArrayBag to modify the Kitchen's Dishes. 
 * It provides constructors, accessor and mutator functions, and a display function to manage and present
 * the details of a Kitchen. The Paramaterized contructor initializes the Kitchen by reading dishes from the CSV file and stores them as pointers in array bag. 
 * 
 * @date [10/25/2024]
 * @author [Marcin Zarkowski]
 */

#include "Kitchen.hpp"
#include <fstream>
#include <memory>
#include <sstream>
#include "Appetizer.hpp"
#include "Dessert.hpp"
#include "MainCourse.hpp"
/**
* Parameterized constructor.
* @param filename The name of the input CSV file containing dish
information.
* @pre The CSV file must be properly formatted.
* @post Initializes the kitchen by reading dishes from the CSV file and
storing them as `Dish*`.
*/
// Constructor that initializes the kitchen by reading dishes from the CSV file
Kitchen::Kitchen(const std::string& filename): total_prep_time_(0), count_elaborate_(0) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::invalid_argument("Could not open file: " + filename);
    }

    std::string line;
    std::getline(file, line);  // Skip the first line

    //for each line in the file read the line and split it into segments and create appropriate dish
    while (std::getline(file, line)) {
        std::string type, name, segment;
        std::vector<std::string> ingredients, attributes;
        int preparationTime = 0;
        float price = 0.0;
        Dish::CuisineType cuisine;
        std::stringstream ss(line);
        int counter = 0;

        //for each segment in the line ( counter keeps track which segment is being read) and split the line into variables 
        while (std::getline(ss, segment, ',')) {
            switch (counter) {
                case 0: type = segment; break;
                case 1: name = segment; break;
                case 2: {
                    std::stringstream ss2(segment);
                    std::string ingredient;
                    while (std::getline(ss2, ingredient, ';')) {//loops through ingredients seperated by ; in this line segment and saves it into variable
                        ingredients.push_back(ingredient);
                    }
                    break;
                }
                case 3: preparationTime = std::stoi(segment); break; //segment 3 is always a preparation time
                case 4: price = std::stof(segment); break; //segment 4 is always a price
                case 5: {//segment 5 is always a cuisine type, so we need to check which one it is
                    if (segment == "ITALIAN") cuisine = Dish::CuisineType::ITALIAN;
                    else if (segment == "MEXICAN") cuisine = Dish::CuisineType::MEXICAN;
                    else if (segment == "CHINESE") cuisine = Dish::CuisineType::CHINESE;
                    else if (segment == "INDIAN") cuisine = Dish::CuisineType::INDIAN;
                    else if (segment == "AMERICAN") cuisine = Dish::CuisineType::AMERICAN;
                    else if (segment == "FRENCH") cuisine = Dish::CuisineType::FRENCH;
                    else cuisine = Dish::CuisineType::OTHER;
                    break;
                }
                case 6: {//segment 6 is always attributes, so we loop through it getting strings seperated by ; and store it in a vector 
                    std::stringstream ss3(segment);
                    std::string attribute;
                    while (std::getline(ss3, attribute, ';')) {
                        attributes.push_back(attribute);
                    }
                    break;
                }
            }
            counter++;//itterate counter 
        }
        //std::cout<<"type: "<<type<<"name: "<<name<<"ingredients: ";
        //for (int i=0; i<ingredients.size(); i++){
         //   std::cout<<ingredients[i];
        //}
        
        //std::cout<<"prep time: "<<preparationTime<<"price: "<<price<<"cuisine: "<<cuisine<<"attributes: ";
        //for (int i=0; i<attributes.size(); i++){
        //    std::cout<<attributes[i];
        //}


        // Create the appropriate dish type and store it
        //This section uses previously set variables from the csv file to appropriatly create the dish and pointer to dish for each line in the csv file
        //attributes is a vector that varies depending on the dish type, so it is handled differently depending on the dish type
        Dish* dish = nullptr;
        if (type == "APPETIZER") {

            //if the dish is an appetizer, attributes[0] holds the serving style
            //uses inline if statements to create the appropriate Appetizer style
            Appetizer::ServingStyle style = 
                (attributes[0] == "BUFFET") ? Appetizer::ServingStyle::BUFFET :
                (attributes[0] == "FAMILY_STYLE") ? Appetizer::ServingStyle::FAMILY_STYLE : 
                Appetizer::ServingStyle::PLATED;

            bool vegetarian = (attributes[2] == "true");
            dish = new Appetizer(name, ingredients, preparationTime, price, cuisine, style, std::stoi(attributes[1]), vegetarian);//create pointer to Appetizer 

        } else if (type == "MAINCOURSE") {

            //if the dish is a main course, attributes[0] holds the cooking method
            MainCourse::CookingMethod cookingMethod = 
                (attributes[0] == "BOILED") ? MainCourse::CookingMethod::BOILED :
                (attributes[0] == "BAKED") ? MainCourse::CookingMethod::BAKED :
                (attributes[0] == "FRIED") ? MainCourse::CookingMethod::FRIED :
                (attributes[0] == "STEAMED") ? MainCourse::CookingMethod::STEAMED :
                (attributes[0] == "RAW") ? MainCourse::CookingMethod::RAW :
                MainCourse::CookingMethod::GRILLED;

            std::string protein = attributes[1];//if the dish is a main course, attributes[1] holds the protein type
            std::stringstream ss4(attributes[2]);//if the dish is a main course, attributes[2] holds the number of portions
            std::string side;
            std::vector<MainCourse::SideDish> sideDishes;

            //loop through the side dishes seperated by | and store them in a vector 
            while (std::getline(ss4, side, '|')) {
                std::stringstream ss5(side);
                std::string sideName, sideCategory;
                std::getline(ss5, sideName, ':');
                std::getline(ss5, sideCategory, ':');

                MainCourse::Category category =
                    (sideCategory == "VEGETABLE") ? MainCourse::Category::VEGETABLE :
                    (sideCategory == "PASTA") ? MainCourse::Category::PASTA :
                    (sideCategory == "LEGUME") ? MainCourse::Category::LEGUME :
                    (sideCategory == "BREAD") ? MainCourse::Category::BREAD :
                    (sideCategory == "SALAD") ? MainCourse::Category::SALAD :
                    (sideCategory == "SOUP") ? MainCourse::Category::SOUP :
                    (sideCategory == "STARCHES") ? MainCourse::Category::STARCHES :
                    MainCourse::Category::GRAIN;

                MainCourse::SideDish sideDish;
                sideDish.name = sideName;
                sideDish.category = category;
                sideDishes.push_back(sideDish);
            }

            bool glutenFree = (attributes[3] == "true");//if the dish is a main course, attributes[3] holds the gluten free boolean
            dish = new MainCourse(name, ingredients, preparationTime, price, cuisine, cookingMethod, protein, sideDishes, glutenFree);//create pointer to MainCourse 

        } else if (type == "DESSERT") {
            //if the dish is a dessert, attributes[0] holds the flavor profile
            Dessert::FlavorProfile flavorProfile = 
                (attributes[0] == "UMAMI") ? Dessert::FlavorProfile::UMAMI :
                (attributes[0] == "BITTER") ? Dessert::FlavorProfile::BITTER :
                (attributes[0] == "SOUR") ? Dessert::FlavorProfile::SOUR :
                (attributes[0] == "SALTY") ? Dessert::FlavorProfile::SALTY :
                Dessert::FlavorProfile::SWEET;

            bool has_nuts = (attributes[2] == "true");//if the dish is a dessert, attributes[2] holds the nuts boolean
            dish = new Dessert(name, ingredients, preparationTime, price, cuisine, flavorProfile, std::stoi(attributes[1]), has_nuts);//create pointer to Dessert
        }

       

        
        if (dish) {
            newOrder(dish); // Pass the pointer to the newOrder function
            
        }
    }
}


// Default constructor
Kitchen::Kitchen() : total_prep_time_(0), count_elaborate_(0) {}

/**
* Destructor.
* @post Deallocates all dynamically allocated dishes to prevent memory
leaks.
*/
Kitchen::~Kitchen() {
    // Delete all dynamically allocated Dish objects
    for (int i = 0; i < item_count_; ++i) {
        delete items_[i];     // Delete the Dish object
        items_[i] = nullptr;   // Set the slot to nullptr
    }
    // Use clear() to reset item count and clean up the ArrayBag's state
    clear();
}

bool Kitchen::newOrder(Dish* new_dish) {
    if (add(new_dish)) // Use pointer directly
    {
        total_prep_time_ += new_dish->getPrepTime(); // Use -> to access members
        
        if (new_dish->getIngredients().size() >= 5 && new_dish->getPrepTime() >= 60) {
            count_elaborate_++;
        }
        return true;
    }
    return false;
}
bool Kitchen::serveDish(Dish* dish_to_remove) {
    if (getCurrentSize() == 0) {
        return false;
    }
    if (remove(dish_to_remove)) {
        total_prep_time_ -= dish_to_remove->getPrepTime();
        if (dish_to_remove->getIngredients().size() >= 5 && dish_to_remove->getPrepTime() >= 60) {
            count_elaborate_--;
        }
        return true;
    }
    return false;
}
int Kitchen::getPrepTimeSum() const
{
    if (getCurrentSize() == 0)
    {
        return 0;
    }
    return total_prep_time_;
}
int Kitchen::calculateAvgPrepTime() const
{
    if (getCurrentSize() == 0)
    {
        return 0;
    }
    double total_prep_time_ = 0;
    for (int i = 0; i < getCurrentSize(); i++)
    {
        total_prep_time_ += items_[i]->getPrepTime();
    }
    total_prep_time_ = total_prep_time_ / getCurrentSize();
    // std::cout<< "Total prep time: "<<total_prep_time_ << std::endl;
    // std::cout<<"rounded: "<<round(total_prep_time_)<<std::endl;
    return round(total_prep_time_);
}
int Kitchen::elaborateDishCount() const
{
    if (getCurrentSize() == 0 || count_elaborate_ == 0)
    {
        return 0;
    }
    return count_elaborate_;
}
double Kitchen::calculateElaboratePercentage() const
{
    // //Computes the percentage of vegetarian dishes in the kitchen rounded up to 2 decimal places.
    // double elaborate_dish = count_elaborate_;
    // std::cout << elaborate_dish << std::endl;

    // double total_dish = getCurrentSize();
    // std::cout << total_dish << std::endl;

    // double percentage = (elaborate_dish / total_dish) * 10000;
    // std::cout << percentage << std::endl;
    // percentage = round(percentage);
    // std::cout << percentage << std::endl;
    // percentage = percentage / 100;
    // std::cout << percentage << std::endl;

    // return percentage;
    if (getCurrentSize() == 0 || count_elaborate_ == 0)
    {
        return 0;
    }
    return round(double(count_elaborate_) / double(getCurrentSize()) * 10000)/100;

    //return count_elaborate_ / getCurrentSize();
}
int Kitchen::tallyCuisineTypes(const std::string& cuisine_type) const{
    int count = 0;
    for (int i = 0; i < getCurrentSize(); i++)
    {
        if (items_[i]->getCuisineType() == cuisine_type)
        {
            count++;
        }
    }
    return count;
}
int Kitchen::releaseDishesBelowPrepTime(const int& prep_time)
{
    int count = 0;
    int num= getCurrentSize();
    for (int i = 0; i < num; i++)
    {
        if (items_[i]->getPrepTime() < prep_time)
        {
            count++;
            serveDish(items_[i]);
        }
    }
    return count;
}

int Kitchen::releaseDishesOfCuisineType(const std::string& cuisine_type)
{
    int count = 0;
    for (int i = 0; i < getCurrentSize(); i++)
    {
        if (items_[i]->getCuisineType() == cuisine_type)
        {
            count++;
            serveDish(items_[i]);
        }
    }
    return count;
}
void Kitchen::kitchenReport() const
{
    std::cout << "ITALIAN: " << tallyCuisineTypes("ITALIAN") << std::endl;
    std::cout << "MEXICAN: " << tallyCuisineTypes("MEXICAN") << std::endl;
    std::cout << "CHINESE: " << tallyCuisineTypes("CHINESE") << std::endl;
    std::cout << "INDIAN: " << tallyCuisineTypes("INDIAN") << std::endl;
    std::cout << "AMERICAN: " << tallyCuisineTypes("AMERICAN") << std::endl;
    std::cout << "FRENCH: " << tallyCuisineTypes("FRENCH") << std::endl;
    std::cout << "OTHER: " << tallyCuisineTypes("OTHER") << std::endl<<std::endl;
    std::cout << "AVERAGE PREP TIME: " << calculateAvgPrepTime() << std::endl;
    std::cout << "ELABORATE DISHES: " << calculateElaboratePercentage() << "%" << std::endl;
}

// Other methods remain unchanged...

/**
* Adjusts all dishes in the kitchen based on the specified dietary accommodation.
* @param request A DietaryRequest structure specifying the dietary accommodations.
* @post Calls the `dietaryAccommodations()` method on each dish in the kitchen to adjust them accordingly.
*/
void Kitchen::dietaryAdjustment(Dish::DietaryRequest request) {
    //bool elaborate;
    for (int i = 0; i < getCurrentSize(); i++) {
        //if (items_[i]->getIngredients().size() >= 5 && items_[i]->getPrepTime() >= 60) {
        //    elaborate = true;
        //}
        //else{
        //    elaborate = false;
        //}

        items_[i]->dietaryAccommodations(request);
        
        //if ((elaborate == true) && (items_[i]->getIngredients().size() < 5 || items_[i]->getPrepTime() < 60)) {
        //   count_elaborate_--;
        // }
       
    }
}

/**
* Displays all dishes currently in the kitchen along with their details.
* @post Iterates over all dishes in the kitchen and displays their details.
*/
void Kitchen::displayMenu() const {
    for (int i = 0; i < getCurrentSize(); i++) {
        items_[i]->display(); 
         
        
    }
    //std::cout<<getCurrentSize()<<" dishes in the kitchen."<<std::endl;
    //std::cout<<count_elaborate_<<" dishes are elaborate."<<std::endl;
}
