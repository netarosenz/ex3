/******************
Name: Neta Rosenzweig
ID: 323885582
Assignment: ex3
*******************/

#include <stdio.h>

#define NUM_OF_BRANDS 5
#define BRANDS_NAMES 15
#define NUM_OF_TYPES 4
#define TYPES_NAMES 10
#define DAYS_IN_YEAR 365
#define addOne  1
#define addAll  2
#define stats  3
#define print  4
#define insights  5
#define deltas  6
#define done  7

char brands[NUM_OF_BRANDS][BRANDS_NAMES] = {"Toyoga", "HyunNight", "Mazduh", "FolksVegan", "Key-Yuh"};
char types[NUM_OF_TYPES][TYPES_NAMES] = {"SUV", "Sedan", "Coupe", "GT"};

int fill_array(int count[NUM_OF_BRANDS]);
void brandsName(int index);
void typesName(int index);
void total_sales_sum(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day);
void most_sold_brand_amount(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day);
void most_sold_types_amount(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day);
void sort_sum_sales(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]);
void printBestBrand(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day);
void printBestType(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day);
void printBestDay(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day);
void printAverageDelta(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day);

    void printMenu() {
        printf("Welcome to the Cars Data Cube! What would you like to do?\n"
            "1.Enter Daily Data For A Brand\n"
            "2.Populate A Day Of Sales For All Brands\n"
            "3.Provide Daily Stats\n"
            "4.Print All Data\n"
            "5.Provide Overall (simple) Insights\n"
            "6.Provide Average Delta Metrics\n"
            "7.exit\n");
    }

    int main() {
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
    // Loop through each day.
    for (int i = 0; i < DAYS_IN_YEAR; i++) {
        // Loop through each brand.
        for (int j = 0; j < NUM_OF_BRANDS; j++) {
            // Loop through each type.
            for (int k = 0; k < NUM_OF_TYPES; k++) {
                // Initialize the cube array values to -1.
                cube[i][j][k] = -1;
            }
        }
    }
    // Initialize the day variable to 0.
    int day = 0;
    // Variable to save the user's choice from the menu.
    int choice;
    // Display the menu to the user.
    printMenu();
    // Read the user's choice.
    scanf("%d", &choice);
    while (choice != done) {
        switch (choice) {
            case addOne: {
                // Variable to store the selected brand.
                int brand;
                printf("Please enter a car brand and the daily sales sum for each car type:");
                // Clear the buffer
                scanf("%*[^\n]%*[\n]");
                // Read the selected brand.
                scanf("%d", &brand);
                // Check if the brand is invalid.
                if (brand < 0 || brand >= NUM_OF_BRANDS) {
                    printf("This brand is not valid\n");
                    break;
                }
                // Loop through each type.
                for (int i = 0; i < NUM_OF_TYPES; i++) {
                    // Read sales data for the selected brand and type.
                    scanf("%d", &cube[day][brand][i]);
                }
                // Move to the next available day
                day++;
                break;
            }
            case addAll: {
                // Variable to store the brand index.
                int brand_index;
                // Initialize an array to track which brands have data.
                int count[NUM_OF_BRANDS] = {0};
                while (1) {
                    // Display brands that do not have data yet.
                    printf("No data for brands ");
                    // Loop through each brand.
                    for (int i = 0; i < NUM_OF_BRANDS; i++) {
                        // Check if data for the brand is missing.
                        if (count[i] == 0) {
                            // Print the current index by the function brandName.
                            brandsName(i);
                            printf(" ");
                        }
                    }
                    printf("\nPlease complete the data\n");
                    // Clear the buffer
                    scanf("%*[^\n]%*[\n]");
                    // Read the brand index
                    scanf("%d", &brand_index);
                    while (brand_index < 0 || NUM_OF_BRANDS <= brand_index) {
                        // Validate the brand index.
                        printf("This brand is not valid\n");
                        printf("No data for brands ");
                        // Loop through each brand.
                        for (int i = 0; i < NUM_OF_BRANDS; i++) {
                            // Check if data for the brand is missing.
                            if (count[i] == 0) {
                                // Print the current index by the function brandName.
                                brandsName(i);
                                printf(" ");
                            }
                        }
                        printf("\nPlease complete the data\n");
                        // Clear the buffer
                        scanf("%*[^\n]%*[\n]");
                        // Read the brand index
                        scanf("%d", &brand_index);
                    }
                    for (int i = 0; i < NUM_OF_TYPES; i++) {
                        // Read sales data for the brand and type.
                        scanf("%d", &cube[day][brand_index][i]);
                    }
                    for (int i = 0; i < NUM_OF_BRANDS; i++) {
                        // Update the count for the current brand.
                        if (brand_index == i) {
                            count[i]++; // update the value of 'i'
                        }
                    }
                    // Check if all brands have data. If true, break the loop.
                    if (fill_array(count)) {
                        break;
                    }
                }
                // Move to the next day.
                day++;
                break;
            }
            case stats: {
                // Variable to save the day for analysis.
                int the_chosen_day;
                printf("What day would you like to analyze?\n");
                scanf("%d", &the_chosen_day);
                while (the_chosen_day < 0 || the_chosen_day >= DAYS_IN_YEAR || the_chosen_day > day) {
                    // Validate the chosen day.
                    printf("Please enter a valid day.\n");
                    printf("What day would you like to analyze?\n");
                    scanf("%d", &the_chosen_day);
                }
                printf("In day number %d:\n", the_chosen_day);
                // Adjust the day index for zero-based array.
                the_chosen_day--;
                // Call to the function total_sales_sum.
                total_sales_sum(cube, the_chosen_day);
                // Call to the function most_sold_brand_amount.
                most_sold_brand_amount(cube, (the_chosen_day));
                printf("\n");
                // Call to the function most_sold_types_amount.
                most_sold_types_amount(cube, (the_chosen_day));
                printf("\n");
                printf("\n");
                break;
            }
            case print: {
                printf("*****************************************\n");
                printf("\n");
                // Call to the function sort_sum_sales and display sales data by brand.
                sort_sum_sales(cube);
                printf("\n");
                printf("\n");
                printf("*****************************************\n");
                break;
            }
            case insights: {
                // Call to the function printBestBrand.
                printBestBrand(cube,day);
                // Call to the function printBestType.
                printBestType(cube, day);
                // Call to the function printBestDay.
                printBestDay(cube, day);
                break;
            }
            case deltas: {
                // Call to the function printAverageDelta.
                printAverageDelta(cube,day);
                break;
            }
            case done: {
                printf("Goodbye!\n");
                break;
            }
            default: {
                printf("Invalid input\n");
            }
        }
        printMenu();
        scanf("%d", &choice);
    }
    printf("Goodbye!\n");
    return 0;
}

//Function to check if the array contains data.
int fill_array(int count[NUM_OF_BRANDS]) {
    //Loop through each brand.
    for (int i = 0; i < NUM_OF_BRANDS; i++) {
        //If the count for the brand is 0.
        if (count[i] == 0) {
            return 0;
        }
    }
    //If all brands have data return 1.
    return 1;
}
//Function to print a brand name without returning a value.
void brandsName(int index) {
    //Loop through the characters of the brand name.
    for (int i = 0; i < BRANDS_NAMES; i++) {
        //Check if the character is printable by ASCII table.
        if (brands[index][i] >= 32 && brands[index][i] <= 126) {
            //Print the character.
            printf("%c", brands[index][i]);
        }
    }
}
//Function to print a type name without returning a value.
void typesName(int index) {
    //Loop through the characters of the type name.
    for (int i = 0; i < TYPES_NAMES; i++) {
        //Check if the character is printable by ASCII table.
        if (types[index][i] >= 32 && types[index][i] <= 126) {
            //Print the character.
            printf("%c", types[index][i]);
        }
    }
}
//Function to calculate and print the total sales for a specific day.
void total_sales_sum(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day) {
    //Initialize total sales to 0.
    int total = 0;
    //Loop through each brand.
    for (int i = 0; i < NUM_OF_BRANDS; i++) {
        //Loop through each type.
        for (int j = 0; j < NUM_OF_TYPES; j++) {
            //Check if sales data exists.
            if (cube[day][i][j] != -1) {
                //Add it to total data.
                total += cube[day][i][j];
            }
        }
    }
    printf("The sales total was %d\n",total); //Print the total sales for the day.
}
//Function to find and print the most sold brand for a specific day.
void most_sold_brand_amount(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day) {
    //Maximum sales for a brand.
    int maxBrand = 0;
    //Sum of sales for a brand.
    int sumBrand = 0;
    //Array to track brands with max sales.
    int brandIndex[NUM_OF_BRANDS] = {0};
    //Loop through each brand.
    for (int i = 0; i < NUM_OF_BRANDS; i++) {
        //Loop through each type.
        for (int j = 0; j < NUM_OF_TYPES; j++) {
            //Check if sales data exists.
            if (cube[day][i][j] != -1) {
                //Add sales for the type.
                sumBrand += cube[day][i][j];
            }
        }
        //Update maxBrand if current brand has more sales.
        if (sumBrand >= maxBrand) {
            maxBrand = sumBrand;
            brandIndex[i] = maxBrand;
        }
        //Reset sum for the next brand.
        sumBrand = 0;
    }
    //Print all brands with max sales.
    printf("The best sold brand with %d sales was ", maxBrand);
    //Loop through each brand.
    for (int i = 0; i < NUM_OF_BRANDS; i++) {
        //If current brand is equal to maxBrand.
        if (brandIndex[i] == maxBrand) {
            //Print the current index by the function brandName.
            brandsName(i);
            printf(" ");
        }
    }
}
// Function to find and print the most sold type for a specific day
void most_sold_types_amount(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day) {
    // Maximum sales for a type
    int maxType = 0;
    // Sum of sales for a type
    int sumType = 0;
    // Array to track types with max sales
    int typeIndex[NUM_OF_TYPES] = {0};
    // Loop through each type
    for (int i = 0; i < NUM_OF_TYPES; i++) {
        // Loop through each brand
        for (int j = 0; j < NUM_OF_BRANDS; j++) {
            // Add sales for the type
            sumType += cube[day][j][i];
        }
        // Update maxType if current type has more sales
        if (sumType >= maxType) {
            maxType = sumType;
            typeIndex[i] = maxType;
        }
        // Reset sum for the next type
        sumType = 0;
    }
    // Print all types with max sales
    printf("The best sold type with %d sales was ", maxType);
    // Loop through each type
    for (int i = 0; i < NUM_OF_TYPES; i++) {
        // If current type is equal to maxType
        if (typeIndex[i] == maxType) {
            // Print the current index by the function typesName
            typesName(i);
            printf(" ");
        }
    }
}
// Function to print sales data sorted by brand
void sort_sum_sales(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]) {
    // Loop through each brand
    for (int brand = 0; brand < NUM_OF_BRANDS; brand++) {
        // Print brand name
        printf("Sales for %s:\n", brands[brand]);
        // Check if brand has sales
        int brand_data_in = 0;
        // Loop through each day
        for (int day = 0; day < DAYS_IN_YEAR; day++) {
            // Check if day has sales
            int day_data_in = 0;
            // Loop through each type
            for (int type = 0; type < NUM_OF_TYPES; type++) {
                // Check if sales data exists
                if (cube[day][brand][type] != -1) {
                    day_data_in = 1;
                    break;
                }
            }
            // Skip if no sales for the day
            if (!day_data_in) {
                continue;
            }
            // Print sales for the day
            printf("Day %d-", day + 1);
            // Loop through types again to print sales
            for (int type = 0; type < NUM_OF_TYPES; type++) {
                // Check if sales data exists
                if (cube[day][brand][type] != -1) {
                    printf(" %s: %d", types[type], cube[day][brand][type]);
                }
            }
            printf("\n");
            brand_data_in = 1;
        }
        // Skip if no sales for the brand
        if (!brand_data_in) {
            continue;
        }
    }
}
// Function to find and print the overall best-selling brand
void printBestBrand(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day) {
    // Sum of sales for a brand
    int sumBrand = 0;
    // Maximum sales for a brand
    int maxBrand = 0;
    // Index of the best brand
    int brandIndex = 0;
    // Loop through each brand
    for (int i = 0; i < NUM_OF_BRANDS; i++) {
        // Loop through each day
        for (int j = 0; j < day; j++) {
            // Loop through each type
            for (int k = 0; k < NUM_OF_TYPES; k++) {

                // Add sales for the type
                sumBrand += cube[j][i][k];
            }
        }
        // Update maxBrand if current brand has more sales
        if (sumBrand > maxBrand) {
            maxBrand = sumBrand;
            brandIndex = i;
        }
        // Reset sum for the next brand
        sumBrand = 0;
    }
    // Print the index by brandName function
    printf("The best-selling brand overall is ");
    brandsName(brandIndex);
    // Print total sales
    printf(": %d$\n", maxBrand);
}
// Function to find and print the overall best-selling type
void printBestType(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day) {
    // Sum of sales for a type
    int sumType = 0;
    // Maximum sales for a type
    int maxType = 0;
    // Index of the best type
    int typeIndex = 0;
    // Loop through each type
    for (int i = 0; i < NUM_OF_TYPES; i++) {
        // Loop through each day
        for (int j = 0; j < day; j++) {
            // Loop through each brand
            for (int k = 0; k < NUM_OF_BRANDS; k++) {
                // Add sales for the type
                sumType += cube[j][k][i];
            }
        }
        // Update maxType if current type has more sales
        if (sumType > maxType) {
            maxType = sumType;
            typeIndex = i;
        }
        // Reset sum for the next type
        sumType = 0;
    }
    // Print the index by typesName function
    printf("The best-selling type of car is ");
    typesName(typeIndex);
    // Print total sales
    printf(": %d$\n", maxType);
}
// Function to find and print the most profitable day
void printBestDay(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day) {
    // Sum of sales for a single day
    int sumDay = 0;
    // Maximum sales recorded for any day
    int maxDay = 0;
    // Index of the most profitable day
    int dayIndex = 0;
    // Loop through each day
    for (int j = 0; j < day; j++) {
        // Loop through each brand
        for (int i = 0; i < NUM_OF_BRANDS; i++) {
            // Loop through each type
            for (int k = 0; k < NUM_OF_TYPES; k++) {
                // Add sales for the current type
                sumDay += cube[j][i][k];
            }
        }
        // Check if the current day's sales are the highest so far
        if (sumDay > maxDay) {
            // Update the maximum sales
            maxDay = sumDay;
            // Save the index of the most profitable day
            dayIndex = j;
        }
        // Reset the sum for the next day
        sumDay = 0;
    }
    // Print the most profitable day and its total sales
    printf("The most profitable day was day number %d: %d$\n", dayIndex + 1, maxDay);
}
// Function to calculate and print the average change in sales between days for each brand
void printAverageDelta(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day) {
    // Loop through each brand
    for (int i = 0; i < NUM_OF_BRANDS; i++) {
        // Sum of sales differences between days
        double sumDelta = 0.0;
        // Count of valid days with sales data
        int deltaCount = 0;
        // Loop through each day starting from the second day
        for (int j = 1; j < day; j++) {
            // Sum of sales for the current day
            int currentDaySum = 0;
            // Sum of sales for the previous day
            int previousDaySum = 0;
            // Loop through each type
            for (int k = 0; k < NUM_OF_TYPES; k++) {
                // Add sales for the current day if data exists
                if (cube[j][i][k] != -1) {
                    currentDaySum += cube[j][i][k];
                }
                // Add sales for the previous day if data exists
                if (cube[j - 1][i][k] != -1) {
                    previousDaySum += cube[j - 1][i][k];
                }
            }
            // Check if there is sales data for either the current or previous day
            if (currentDaySum > 0 || previousDaySum > 0) {
                // Add the difference to the total
                sumDelta += (currentDaySum - previousDaySum);
                // Increase the count of valid days
                deltaCount++;
            }
        }
        // Initialize the average change in sales
        double averageDelta = 0.0;
        // Calculate the average if there are valid days
        if (deltaCount > 0) {
            averageDelta = sumDelta / deltaCount;
        }
        // Print the brand's name and its average change in sales
        printf("Brand: %s, Average Delta: %.6f\n", brands[i], averageDelta);
    }
}


