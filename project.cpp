#pragma GCC diagnostic ignored "-Wwrite-strings"// In order to remove warnings of Concerting string to wide String
#pragma GCC diagnostic ignored "-Wreturn-type" // Remove Return warnings

#define _WIN32_WINNT 0x0A00 // set Windows version 10 to support Windows 10 API
#include <iostream>
#include <string>
#include <fstream> // library used for filing
#include <sstream> // takes data as data Stream 
#include <iomanip>
#include <ctime> // library to use time structure and functions
#include <chrono> // library to use time structure and functions
#include <vector> 
#include <map>
#include <Windows.h> // library to use Windows Api
#include <conio.h> // to use getche() function
#include "console.h"
#include "font.h"
#include "position.h"

using namespace std;

// Remove area by printing ' ' from one point to another
void cleanArea(int _x1, int _y1, int _x2, int _y2);

// print message at bottom of the screen
template<class T> void setMessage(T message);

// set the Title of the Interface
void setTitle(string message); 

//calls cleanArea  function and system Pause
void setContinue(); 

// show all cuisine in Order Food Menu
void showCuisine(int _index); 

// classes declared
class FOOD;
class PIZZA;
class BURGER;
class SANDWICHE;
class FASTFOOD;
class BARBQ;
class PAKISTANI;
class CHINESE;
class INTERNATIONAL;
class SEAFOOD;
class DESSERT;
class CAKE;
class BEVERAGE;
class CUSTOMER;
class RESTAURANT;
class ADMINISTRATOR;
class ORDER;
class TAXDEPARTMENT;
class TIMENOW;

//Cuisine vector which contains food menu 
vector<string> cuisineTitle{"Pizza","Burgers","Sandwiches","Fast Food","Bar.B.Q","Pakistani","Chinese","International","Seafood","Desserts","Cakes & Bakery","Beverage"};

//2D Vector containing cities with areas
vector<vector<string>> cities{{"Islamabad", "Area 1"},
                              {"Karachi", "Area 1", "Area 2", "Area 3", "Area 4", "Area 5"},
                              {"Lahore", "Area 1", "Area 2", "Area 3", "Area 4"},
                              {"Peshawar", "Area 1", "Area 2", "Area 3"},
                              {"Queta", "Area 1", "Area 2"}};

//3D vector containing distance of areas
vector<vector<vector<int>>> tDistance {{{5}},
                                      {{5,15,25,25,15},{15,5,15,25,25},{25,15,5,15,25},{25,25,15,5,15},{15,25,25,15,5}},
                                      {{5,15,25,15},{15,5,15,25},{25,15,5,15},{15,25,15,5}},
                                      {{5,15,15},{15,5,15},{15,15,5}},
                                      {{5,15},{15,5}}};

// vector of Days
vector<string> days{"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// Vector of Menu which is used to show and implement the interface accordingly
vector<vector<string>> menu{{"MAIN  MENU", "Administrator", "Restaurant Manager", "Customer", "EXIT"}, //0
                            {"ADMINISTRATOR", "Show Details", "Restaurant Management", "Customer Management", "Vouchers Management", "Go Back"}, //1
                            {"ADMINISTRATOR > Show Details", "Summary", "Show Restaurants", "Show Customers", "Go Back"}, //2
                            {"ADMINISTRATOR > Show Details > Show Restaurants", "Show All", "By Cuisine", "By Location", "Go Back"}, //3
                            {"ADMINISTRATOR > Restaurant Management", "Add New", "Close", "Re-Open", "Find", "Receive Revenue", "Go Back"}, //4
                            {"ADMINISTRATOR > Customer Management", "Add New", "Block", "Unblock", "Find", "Go Back"}, //5
                            {"ADMINISTRATOR > Voucher Management", "Add New", "Block", "Send", "Show", "Go Back"}, //6
                            {"RESTAURANT MANAGER", "Show Details", "Change Password", "Open/Close Restaurant", "Set Opening Days/Timings", "Modify Details", "Menu Management", "Order Management", "Go Back"}, //7
                            {"RESTAURANT MANAGER > Menu Management", "Add Item", "Modify Item Details", "Delete Item", "Show Details", "Go Back"}, //8
                            {"RESTAURANT MANAGER > Order Management", "Show Details", "Go Back"}, //9
                            {"CUSTOMER", "New User", "Sign In", "Go Back"}, //10
                            {"CUSTOMER > Signed In", "Show Details", "Modify Details", "Order Food", "Order Details", "Voucher Management", "Go Back"}, //11
                            {"CUSTOMER > Signed In > Voucher Management", "Show Details", "Use Voucher", "Go Back"}, //12
                            {"ADMINISTRATOR > Show Details > Show Customers", "Show All", "By Location", "Go Back"}, //13
                            {"RESTAURANT MANAGER > Menu Management > Show Details", "Show All", "Show by Cuisine", "Show by Code", "Go Back"}, //14
                            {"CUSTOMER > Signed In > Order Food", "Show Restaurants", "Show Restaurant Menu (Order Food)", "Go Back"}, //15
                            {"CUSTOMER > Signed In > Order Food > Show Restaurants", "Show All", "By Cuisine", "By Location", "Go Back"}}; //16

// Function that returns date and time details in structured data type 
tm newTime1(){
    auto nowTime = chrono::system_clock::now();
    time_t sleepTime = chrono::system_clock::to_time_t(nowTime);
    tm myLocalTime = *localtime(&sleepTime);
    return myLocalTime;
}


// FOOD class that is inherited to cuisines  
class FOOD{
private:

protected:
    double price;
    string itemCode; // RRRCCNNN (R = Restaurant Code, C = Cuisine Code, N = Item Number "index+1")
    const int cuisine;
    string foodTitle;
    string foodDescription;
    int prepTime;
    double discount;
    int stock;
    int limit;

public:
    /*Copy Constructor
        FOOD(const FOOD &f2){
            cuisine = f2.cuisine
            foodTitle = f2.title;
            foodDescription = f2.description;
            stock = f2.stock;
            limit = f2.limit;
            prepTime = f2.time;
            discount = f2.discount;
        }
    */
    FOOD(int _cuisine):cuisine(_cuisine){}

// getter functions
    string getItemCode(){return itemCode;}
    int getCuisine(){return cuisine;}
    string getTitle(){return foodTitle;}
    string getDescription(){return foodDescription;}
    int getStock(){return stock;}
    int getLimit(){return limit;}
    double getPrice(){return price;}
    double getDiscount(){return discount*100;}
    double getValue(){return (price * (1 + discount));}
    int getPrepTime(){return prepTime;}

// setter functions
    void setItemCode(string _itemCode){itemCode = _itemCode;}
    void setTitle(string _title){foodTitle = _title;}
    void setDescription(string _description){foodDescription = _description;}
    void setStock(int _stock){stock = _stock;}
    void setLimit(int _limit){limit = _limit;}
    void setPrice(double _price){price = _price;}
    void setDiscount(double _discount){discount = _discount/100;}
    void setPrepTime(int _time){prepTime = _time;}
};


// OrderItem of a single cuisine item
class ORDERITEM{
    string code; // RRRCCNNN (same as Food itemCode)
    int cuisine;
    string title;
    string description; // only for pizza sinc pizza has multiple sizes
    double price;
    double discount;
    int prepTime;
    int quantity;

public:
// Constructor Overloading
    ORDERITEM(int _cuisine, string _code, string _title, string _description, double _price, double _discount, int _prepTime, int _quantity){
        code = _code;
        title = _title;
        cuisine = _cuisine;
        description = _description;
        price = _price;
        discount = _discount/100;
        prepTime = _prepTime;
        quantity = _quantity;
    }

    ORDERITEM(){}

    /*Copy constructor
    ORDERITEM(const ORDERITEM &oi){
        code = oi.code;
        title = oi.title;
        cuisine = oi.cuisine;
        description = oi.description;
        price = oi.price;
        discount = oi.discount/100;
        prepTime = oi.prepTime;
        quantity = oi.quantity;
    }
    */
// We assume that the Price we are getting is already discounted (Price = 100,value = 111.11, where discount = 10%)   
// getter functions
    string getCode(){return code;}
    int getCuisine(){return cuisine;}
    string getTitle(){return title;}
    string getDescription(){return description;}
    double getPriceTotal(){return (price * quantity);}
    double getPriceTotalValue(){return ((price * quantity)/(1-discount));}
    double getPrice(){return price;}
    double getDiscountPercent(){return discount*100;}
    double getDiscountValue(){return (((price)/(1-discount)) - price);}
    double getDiscountValueTotal(){return (getPriceTotalValue() - getPriceTotal());}
    int getPrepTime(){return prepTime;}
    int getQuantity(){return quantity;}

// setter functions
    void setCode(string _code){code = _code;}
    void setTitle(string _title){title = _title;}
    void setDescription(string _description){description = _description;}
    void setPrice(double _price){price = _price;}
    void setDiscountPercent(double _discount){discount = _discount/100;}
    void setPrepTime(int _time){prepTime = _time;}
    void setQuantity(int _quantity){quantity = _quantity;}
    void addQuantity(int _quantity){quantity += _quantity;}
};


class PIZZA : public FOOD{
    vector<double> price; // since a pizza can have multiple sizes so each size will have different prices
    vector<string> size;

public:
// Constructor Overloading

    PIZZA(string _title, string _description, int _stock, int _limit, int _time, double _discount, vector<double> _price, vector<string> _size):FOOD(0){
        foodTitle = _title;
        foodDescription = _description;
        stock = _stock;
        limit = _limit;
        prepTime = _time;
        discount = _discount/100;
        price = _price;
        size = _size;
    }

    PIZZA():FOOD(0){}

// getter function
    double getPrice(int _index){return price[_index];}
    double getValue(int _index){return (price[_index]/(1 - discount));}
    vector<double> getPrice(){return price;}
    string getSize(int _index){return size[_index];}
    vector<string> getSize(){return size;}
    int getSizeLength(){return size.size();}
    void setPrice(vector<double> _price){
        price = _price;
    }
    void setSize(vector<string> _size){
        size = _size;
    }
};


class BURGER : public FOOD{
public:
    BURGER(string _title, string _description, int _stock, int _limit, int _time, double _discount, double _price):FOOD(1){
        foodTitle = _title;
        foodDescription = _description;
        stock = _stock;
        limit = _limit;
        prepTime = _time;
        discount = _discount/100;
        price = _price;
    }
};


class SANDWICHE : public FOOD{
public:
    SANDWICHE(string _title, string _description, int _stock, int _limit, int _time, double _discount, double _price):FOOD(2){
        foodTitle = _title;
        foodDescription = _description;
        stock = _stock;
        limit = _limit;
        prepTime = _time;
        discount = _discount/100;
        price = _price;
    }
};


class FASTFOOD : public FOOD{
public:
    FASTFOOD(string _title, string _description, int _stock, int _limit, int _time, double _discount, double _price):FOOD(3){
        foodTitle = _title;
        foodDescription = _description;
        stock = _stock;
        limit = _limit;
        prepTime = _time;
        discount = _discount/100;
        price = _price;
    }
};


class BARBQ : public FOOD{
public:
    BARBQ(string _title, string _description, int _stock, int _limit, int _time, double _discount, double _price):FOOD(4){
        foodTitle = _title;
        foodDescription = _description;
        stock = _stock;
        limit = _limit;
        prepTime = _time;
        discount = _discount/100;
        price = _price;
    }
};


class PAKISTANI : public FOOD{
public:
    PAKISTANI(string _title, string _description, int _stock, int _limit, int _time, double _discount, double _price):FOOD(5){
        foodTitle = _title;
        foodDescription = _description;
        stock = _stock;
        limit = _limit;
        prepTime = _time;
        discount = _discount/100;
        price = _price;
    }
};


class CHINESE : public FOOD{
public:
    CHINESE(string _title, string _description, int _stock, int _limit, int _time, double _discount, double _price):FOOD(6){
        foodTitle = _title;
        foodDescription = _description;
        stock = _stock;
        limit = _limit;
        prepTime = _time;
        discount = _discount/100;
        price = _price;
    }
};


class INTERNATIONAL : public FOOD{
public:
    INTERNATIONAL(string _title, string _description, int _stock, int _limit, int _time, double _discount, double _price):FOOD(7){
        foodTitle = _title;
        foodDescription = _description;
        stock = _stock;
        limit = _limit;
        prepTime = _time;
        discount = _discount/100;
        price = _price;
    }
};


class SEAFOOD : public FOOD{
public:
    SEAFOOD(string _title, string _description, int _stock, int _limit, int _time, double _discount, double _price):FOOD(8){
        foodTitle = _title;
        foodDescription = _description;
        stock = _stock;
        limit = _limit;
        prepTime = _time;
        discount = _discount/100;
        price = _price;
    }
};


class DESSERT : public FOOD{
public:
    DESSERT(string _title, string _description, int _stock, int _limit, int _time, double _discount, double _price):FOOD(9){
        foodTitle = _title;
        foodDescription = _description;
        stock = _stock;
        limit = _limit;
        prepTime = _time;
        discount = _discount/100;
        price = _price;
    }
};


class CAKE : public FOOD{

public:

    CAKE(string _title, string _description, int _stock, int _limit, int _time, double _discount, double _price):FOOD(10){
        foodTitle = _title;
        foodDescription = _description;
        stock = _stock;
        limit = _limit;
        prepTime = _time;
        discount = _discount/100;
        price = _price;
    }
};


class BEVERAGE : public FOOD{
public:
    BEVERAGE(string _title, string _description, int _stock, int _limit, int _time, double _discount, double _price):FOOD(11){
        foodTitle = _title;
        foodDescription = _description;
        stock = _stock;
        limit = _limit;
        prepTime = _time;
        discount = _discount/100;
        price = _price;
    }
};


// ORDER class is the class through which food items are ordered 
class ORDER{
    string orderNumber; // RRRCCCCNNN (R = Restaurant Code, C = Customer Code, N = Order Index of Customer since order is initiated by customer)
    tm orderTime;   // time when order is placed
    vector<ORDERITEM> orderItems; // details of ordered food items
    int deliveryTime; // duration when ordered may be delivered
    double deliveryCharges; // calculated as required by the restaurant
    bool isPaid; // if order is paid by customer
    bool isApproved; // if order has been approved

public:
// Getter functions
    int getDeliveryTime(){return deliveryTime;}
    string getOrderNumber(){return orderNumber;}
    string getDate(){return (to_string(orderTime.tm_mday) + "/" + to_string(orderTime.tm_mon + 1) + "/" + to_string(orderTime.tm_year + 1900));} // dd/mm/yyyy
    string getTime(){return (to_string(orderTime.tm_hour) + ":" + to_string(orderTime.tm_min) + ":" + to_string(orderTime.tm_sec));} // hh:mm:ss
    bool getIsPaid(){return isPaid;}
    bool getIsApproved(){return isApproved;}
    int getOrderItemsSize(){return orderItems.size();}
    int getDeliveryCharges(){return deliveryCharges;}
    vector<ORDERITEM> getOrderItems(){return orderItems;}
    ORDERITEM getOrderItems(int _index){return orderItems[_index];}
    tm getOrderTime(){return orderTime;}

// Setter Functions
    void setOrderTime(tm _orderTime){
        orderTime = _orderTime;
    }

    void setDeliveryCharges(int _amount){deliveryCharges = _amount;}

    void setIsPaid(bool _bool){
        isPaid = _bool;
    }

    void setIsApproved(bool _bool){
        isApproved = _bool;
    }

    void setOrderNumber(string _orderNumber){orderNumber = _orderNumber;}

// gets Delivery time as mentioned in 3D vector of tDistance
    void setDeliveryTime(int _city, int _cArea, int _rArea){
        deliveryTime = tDistance[_city][_cArea-1][_rArea-1]; // Since in interface we are getting city and Area from 1 however it starts from 0 so -1
    }
 
// when customer is adding items to order 
    void addOrderItem(ORDERITEM _order){
        for(int i = 0; i < orderItems.size(); i++){
            if(_order.getCode() == orderItems[i].getCode() && _order.getPrice() == orderItems[i].getPrice()){
                orderItems[i].addQuantity(_order.getQuantity());
                return;
            }
        }
        orderItems.push_back(_order);
    }

// returns total price of all items vector * quantity
    double getBill(){
        double amount = 0;
        for(int i = 0; i < orderItems.size(); i++){
            amount += orderItems[i].getPriceTotal();
        }
        return amount;
    }

// Return the max preparaton time of all orderitems
    int getPrepTime(){
        int duration = 0;
        for(int i =0; i < orderItems.size(); i++){
            if(duration < orderItems[i].getPrepTime()){
                duration = orderItems[i].getPrepTime();
            }
        }
        return duration;
    }

// Adds delivery time to preparation time
    int getDeliveryTimeTotal(){return (deliveryTime + getPrepTime());}

// show all OrderItems within an Order in Table form
    void showAllOrderItems(){
        int title[9] = {9, 20, 10, 11, 7, 8, 8, 8, 8};
        cout << "\t" << char(218);
        for(int i = 0; i < 9; i++){
            cout << string(title[i], char(196)) << char(194);
        }
        cout << "\b" << char(191) << "\n\t" << char(179) << setw(title[0]) << "CODE " << char(179) << setw(title[1]) << "TITLE " << char(179) << setw(title[2]) << "TYPE " << char(179) << setw(title[3]) << "PREP TIME" << char(179) << setw(title[4]) << "PRICE " << char(179) << setw(title[5]) << "QUANTITY" << char(179) << setw(title[6]) << "TOTAL " << char(179) << setw(title[7]) << "DISCOUNT" << char(179) << setw(title[8]) << "VALUE " << char(179);
        cout << "\n\t" << char(195);
        for(int i = 0; i < 9; i++){
            cout << string(title[i], char(196)) << char(197);
        }
        cout << "\b" << char(180);
        for(int i = 0; i < orderItems.size(); i++){
            cout << "\n\t" << char(179) << setw(title[0]) << orderItems[i].getCode() << char(179) << setw(title[1]) << orderItems[i].getTitle() << char(179) << setw(title[2]) << orderItems[i].getDescription() << char(179) << setw(title[3] - 8) << orderItems[i].getPrepTime() << " Minutes" << char(179) << setw(title[4]) << orderItems[i].getPrice() << char(179) << setw(title[5]) << orderItems[i].getQuantity() << char(179) << setw(title[6]) << orderItems[i].getPriceTotal() << char(179) << setw(title[7] - 1) << orderItems[i].getDiscountPercent() << "%" << char(179) << setw(title[8]) << orderItems[i].getPriceTotalValue() << char(179);
            // in case order items exceeds 32 items
            if((i % 32) == 0 && i != 0 && i != (orderItems.size() - 1)){
                cout << "\n\t" << char(192);
                for(int i = 0; i < 10; i++){
                    cout << string(title[i], char(196)) << char(193);
                }
                cout << "\b" << char(217) << endl;
                setMessage("More....");
                setContinue();
                cleanArea(2, 10, 143, 44);
                gotoxy(2, 9);
            }
        }
        cout << "\n\t" << char(192);
        for(int i = 0; i < 9; i++){
            cout << string(title[i], char(196)) << char(193);
        }
        cout << "\b" << char(217);
    }

    void showOrder(){
        showAllOrderItems();
    }

// only shows orderDetails
    void showOrderDetails(char _type){
        int titleSizeR[9] = {13, 15, 13, 15, 12, 12, 6, 10, 15};
        int titleSizeC[9] = {13, 15, 13, 15, 12, 12, 6, 10, 17};
        int titleSize[9];
        string _code;
        if(_type == 'R'){
            swap(titleSize, titleSizeR);
            _code = orderNumber.substr(3, 4);
        } else if(_type == 'C'){
            swap(titleSize, titleSizeC);
            _code = orderNumber.substr(0, 3);
        }
        cout << "\n\t" << char(179) << setw(titleSize[0]) << orderNumber << char(179) << setw(titleSize[1]) << orderItems.size() << char(179) << setw(titleSize[2]) << (getBill() + deliveryCharges) << char(179) << setw(titleSize[3]) << (to_string(getDeliveryTimeTotal()) + " Minutes") << char(179) << setw(titleSize[4]) << getDate() << char(179) << setw(titleSize[5]) << getTime() << char(179) << setw(titleSize[6]) << isPaid << char(179) << setw(titleSize[7]) << isApproved << char(179) << setw(titleSize[8]) << _code << char(179);
    }
};


// Restaurant class containing manager and restaurant details
class RESTAURANT{
    string managerID;
    string managerPassword;
    string restaurantCode;
    bool isRestActive; // only Admin will have access
    bool isRestOpen; // accesible by manager
    int openTime; // Time Restaurant Opens
    int closeTime; // Time Restaurant closes
    bool * daysOpen = new bool[7]{false}; // by default restaurant closed all seven days
    string title; 
    string description;
    string contactNumber;
    string address;
    int area;
    int city;
    double restRevenue;
    double restTax;
    int ordersPending;
    int ordersCompleted;
    int ordersCancelled;
    bool freeDelivery;
    int minimumOrder;
    double deliveryCharges;
    static double adminFee;
    vector<PIZZA> pizzas;
    vector<BURGER> burgers;
    vector<SANDWICHE> sandwiches;
    vector<FASTFOOD> fastfoods;
    vector<BARBQ> barbqs;
    vector<PAKISTANI> pakistanis;
    vector<CHINESE> chineses;
    vector<INTERNATIONAL> internationals;
    vector<SEAFOOD> seafoods;
    vector<DESSERT> desserts;
    vector<CAKE> cakes;
    vector<BEVERAGE> beverages;
    vector<ORDER> restOrders;
    double restDiscount;

public:
    RESTAURANT(string _managerID, string _managerPassword, int _openTime, int _closeTime, string _title, string _description, string _contactNumber, string _address, int _area, int _city, bool _freeDelivery, int _minimumOrder, double _deliveryCharges, double _restDiscount){
        managerID = _managerID;
        managerPassword = _managerPassword;
        isRestActive = true;
        isRestOpen = false;
        openTime = _openTime;
        closeTime = _closeTime - 1;
        if(closeTime == -1){
            closeTime = 23;
        }
        title = _title;
        description = _description;
        contactNumber = _contactNumber;
        address = _address;
        area = _area;
        city = _city;
        restRevenue = restTax = 0.0;
        ordersPending = ordersCompleted = ordersCancelled = 0;
        freeDelivery = _freeDelivery;
        if(freeDelivery == true){
            minimumOrder = _minimumOrder;
        }
        else{
            minimumOrder = 0;
        }
        deliveryCharges = _deliveryCharges;
        restDiscount = (_restDiscount/100);
    }

    RESTAURANT(){}

// getter functions
    string getCode(){return restaurantCode;}
    string getTitle(){return title;}
    string getAddress(){return address;}
    string getCity(){return cities[city][0];}
    string getArea(){return cities[city][area];}
    int getCityInt(){return city;}
    int getAreaInt(){return area;}
    string getManagerID(){return managerID;}
    string getManagerPassword(){return managerPassword;}
    string getTime(){return (to_string(openTime) + " - " + to_string(closeTime));}
    bool getIsRestActive(){return isRestActive;}
    bool getIsRestOpenR(){return isRestOpen;}
    int getPizzaSize(){pizzas.size();}
    int getBurgerSize(){burgers.size();}
    int getSandwicheSize(){sandwiches.size();}
    int getFastFoodSize(){fastfoods.size();}
    int getBarBQsize(){barbqs.size();}
    int getPakistaniSize(){pakistanis.size();}
    int getChineseSize(){chineses.size();}
    int getInternationalSize(){internationals.size();}
    int getSeaFoodSize(){seafoods.size();}
    int getDessertSize(){desserts.size();}
    int getCakeSize(){cakes.size();}
    int getBeveragesSize(){beverages.size();}
    int getOpenTime(){return openTime;}
    int getCloseTime(){return (closeTime + 1);}
    int getOrderSize(){return restOrders.size();}
// checks time and whether restaurant is OPen
    bool getIsRestOpen(){
        tm tempTime = newTime1();
        if(isRestActive == true && isRestOpen == true){
            if(openTime == closeTime && daysOpen[tempTime.tm_wday] == true){
                return true;
            } else if(openTime > closeTime){
                if((((tempTime.tm_hour >= openTime) && (tempTime.tm_hour > closeTime)) || ((tempTime.tm_hour < openTime) && (tempTime.tm_hour <= closeTime))) && daysOpen[tempTime.tm_wday] == true){
                    return true;
                } else{
                    return false;
                }
            } else{
                if(((tempTime.tm_hour >= openTime) && (tempTime.tm_hour <= closeTime)) && daysOpen[tempTime.tm_wday] == true){
                    return true;
                } else{
                    return false;
                }
            }
        } else{
            return false;
        }
    }

    static double getAdminFee(){
        double _amount = adminFee;
        adminFee = 0;
        return _amount;
    }

// checks each cuisine whether there is any 
    bool hasPizza(){
        if(pizzas.size() > 0){
            return true;
        }
        return false;
    }

    bool hasBurgers(){
        if(burgers.size() > 0){
            return true;
        }
        return false;
    }

    bool hasSandwiches(){
        if(sandwiches.size() > 0){
            return true;
        }
        return false;
    }

    bool hasFastfoods(){
        if(fastfoods.size() > 0){
            return true;
        }
        return false;
    }

    bool hasBarbqs(){
        if(barbqs.size() > 0){
            return true;
        }
        return false;
    }

    bool hasPakistanis(){
        if(pakistanis.size() > 0){
            return true;
        }
        return false;
    }

    bool hasChineses(){
        if(chineses.size() > 0){
            return true;
        }
        return false;
    }

    bool hasInternationals(){
        if(internationals.size() > 0){
            return true;
        }
        return false;
    }

    bool hasSeafoods(){
        if(seafoods.size() > 0){
            return true;
        }
        return false;
    }

    bool hasDesserts(){
        if(desserts.size() > 0){
            return true;
        }
        return false;
    }

    bool hasCakes(){
        if(cakes.size() > 0){
            return true;
        }
        return false;
    }

    bool hasBeverages(){
        if(beverages.size() > 0){
            return true;
        }
        return false;
    }

// checks cuisine using cuisine Name
    bool hasFood(string _cuisine){
        if((_cuisine == cuisineTitle[0]) && (hasPizza() == true)){
            return true;
        } else if((_cuisine == cuisineTitle[1]) && (hasBurgers() == true)){
            return true;
        } else if((_cuisine == cuisineTitle[2]) && (hasSandwiches() == true)){
            return true;
        } else if((_cuisine == cuisineTitle[3]) && (hasFastfoods() == true)){
            return true;
        } else if((_cuisine == cuisineTitle[4]) && (hasBarbqs() == true)){
            return true;
        } else if((_cuisine == cuisineTitle[5]) && (hasPakistanis() == true)){
            return true;
        } else if((_cuisine == cuisineTitle[6]) && (hasChineses() == true)){
            return true;
        } else if((_cuisine == cuisineTitle[7]) && (hasInternationals() == true)){
            return true;
        } else if((_cuisine == cuisineTitle[8]) && (hasSeafoods() == true)){
            return true;
        } else if((_cuisine == cuisineTitle[9]) && (hasDesserts() == true)){
            return true;
        } else if((_cuisine == cuisineTitle[10]) && (hasCakes() == true)){
            return true;
        } else if((_cuisine == cuisineTitle[11]) && (hasBeverages() == true)){
            return true;
        } else{
            return false;
        }
    }

// checks cuisine using cuisine index
    bool hasFood(int _cuisine){
        if((_cuisine == 0) && (hasPizza() == true)){
            return true;
        } else if((_cuisine == 1) && (hasBurgers() == true)){
            return true;
        } else if((_cuisine == 2) && (hasSandwiches() == true)){
            return true;
        } else if((_cuisine == 3) && (hasFastfoods() == true)){
            return true;
        } else if((_cuisine == 4) && (hasBarbqs() == true)){
            return true;
        } else if((_cuisine == 5) && (hasPakistanis() == true)){
            return true;
        } else if((_cuisine == 6) && (hasChineses() == true)){
            return true;
        } else if((_cuisine == 7) && (hasInternationals() == true)){
            return true;
        } else if((_cuisine == 8) && (hasSeafoods() == true)){
            return true;
        } else if((_cuisine == 9) && (hasDesserts() == true)){
            return true;
        } else if((_cuisine == 10) && (hasCakes() == true)){
            return true;
        } else if((_cuisine == 11) && (hasBeverages() == true)){
            return true;
        } else{
            return false;
        }
    }

    bool getDaysOpen(int _index){return daysOpen[_index];}
    double getRestDiscount(){return (restDiscount * 100);}
    string getContactNumber(){return contactNumber;}
    double getRestRevenue(){return restRevenue;}
    double getRestTax(){return restTax;}
    int getOrdersPending(){return ordersPending;}
    int getOrdersCompleted(){return ordersCompleted;}
    int getOrdersCancelled(){return ordersCancelled;}
    bool getFreeDelivery(){return freeDelivery;}
    int getMinimumOrder(){return minimumOrder;}
    double getDeliveryCharges(){return deliveryCharges;}
    string getDescription(){return description;}

// get total number of cuisines availabel in MENU
    int getMenuSize(){
        return (pizzas.size() + burgers.size() + sandwiches.size() + fastfoods.size() + barbqs.size() + pakistanis.size() + chineses.size() + internationals.size() + seafoods.size() + desserts.size() + cakes.size() + beverages.size());
    }

// Setter Functions
    void setCode(string _code){
        restaurantCode = _code;
    }
    void setManagerID(string _managerID){
        managerID = _managerID;
    }
    void setManagerPassword(string _managerPassword){
        managerPassword = _managerPassword;
    }
    void setIsRestActive(bool _isActive){
        isRestActive = _isActive;
    }
    void setIsRestOpen(bool _isOpen){
        isRestOpen = _isOpen;
    }
    void setOpenTime(int _opneTime){
        openTime = _opneTime;
    }
    void setCloseTime(int _closeTime){
        closeTime = _closeTime - 1;
        if(closeTime == -1){
            closeTime = 23;
        };
    }
    void setTitle(string _title){
        title = _title;
    }
    void setDescription(string _description){
        description = _description;
    }
    void setContactNumber(string _contact){
        contactNumber = _contact;
    }
    void setAddress(string _address){
        address = _address;
    }
    void setArea(int _area){
        area = _area;
    }
    void setCity(int _city){
        city = _city;
    }
    void setRestRevenue(double _restRevenue){
        restRevenue = _restRevenue;
    }
    void increaseRestRevenue(double _restRevenue){
        restRevenue = restRevenue + _restRevenue;
    }
    void setRestTax(double _restTax){
        restTax = _restTax;
    }
    void increaseRestTax(double _restTax){
        restTax = restTax + _restTax;
    }
    void setOrdersPending(int _ordersPending){
        ordersPending = _ordersPending;
    }
    void setDiscount(double _int){
        restDiscount = _int/100;
    }
    void setFreeDelivery(bool _bool){
        freeDelivery = _bool;
    }
    void setMininmumOrder(int _int){
        minimumOrder = _int;
    }
    void setDeliveryCharges(double _double){
        deliveryCharges = _double;
    }
    void IncreaseordersPending(int _oredersPending){
        ordersPending = _oredersPending;
    }

// Allows manage to access data if correct id and password
    bool managerLogin(string _managerID, string _password){
        if(managerID == _managerID && managerPassword == _password){
            cout << "Welcome " << managerID << " to " << title << endl;
            return true;
        }else{
            cout << "Bad Manager ID or Password!" << endl;
            return false;
        }
    }

    void setDayOpen(int _day){
        daysOpen[_day] = true;
    }

    void setDayClose(int _day){
        daysOpen[_day] = false;
    }

// Creates the ItemCode CCNNN (C = Cuisine, N = Number of item) Restaurant code is added in Additem function
    string createItemCode(int _cuisine, int _item){
        if(_cuisine < 10){
            if(_item < 10){
                return ("0" + to_string(_cuisine) + "00" + to_string(_item));
            } else if(_item < 100){
                return ("0" + to_string(_cuisine) + "0" + to_string(_item));
            } else{
                return ("0" + to_string(_cuisine) + to_string(_item));
            }
        } else{
            if(_item < 10){
                return (to_string(_cuisine) + "00" + to_string(_item));
            } else if(_item < 100){
                return (to_string(_cuisine) + "0" + to_string(_item));
            } else{
                return (to_string(_cuisine) + to_string(_item));
            }
        }
    }

// Restaurant Code is added to Cuisine Code
    void addItem(PIZZA _pizza){
        pizzas.push_back(_pizza);
        pizzas[pizzas.size()-1].setItemCode(restaurantCode + createItemCode(0, pizzas.size()));
    }

    void addItem(BURGER _burger){
        burgers.push_back(_burger);
        burgers[burgers.size()-1].setItemCode(restaurantCode + createItemCode(1, burgers.size()));
    }

    void addItem(SANDWICHE _sandwich){
        sandwiches.push_back(_sandwich);
        sandwiches[sandwiches.size()-1].setItemCode(restaurantCode + createItemCode(2, sandwiches.size()));
    }

    void addItem(FASTFOOD _fastFood){
        fastfoods.push_back(_fastFood);
        fastfoods[fastfoods.size()-1].setItemCode(restaurantCode + createItemCode(3, fastfoods.size()));
    }

    void addItem(BARBQ _barBQ){
        barbqs.push_back(_barBQ);
        barbqs[barbqs.size()-1].setItemCode(restaurantCode + createItemCode(4, barbqs.size()));
    }

    void addItem(PAKISTANI _pakistani){
        pakistanis.push_back(_pakistani);
        pakistanis[pakistanis.size()-1].setItemCode(restaurantCode + createItemCode(5, pakistanis.size()));
    }

    void addItem(CHINESE _chinese){
        chineses.push_back(_chinese);
        chineses[chineses.size()-1].setItemCode(restaurantCode + createItemCode(6, chineses.size()));
    }

    void addItem(INTERNATIONAL _international){
        internationals.push_back(_international);
        internationals[internationals.size()-1].setItemCode(restaurantCode + createItemCode(7, internationals.size()));
    }

    void addItem(SEAFOOD _seaFood){
        seafoods.push_back(_seaFood);
        seafoods[seafoods.size()-1].setItemCode(restaurantCode + createItemCode(8, seafoods.size()));
    }

    void addItem(DESSERT _dessert){
        desserts.push_back(_dessert);
        desserts[desserts.size()-1].setItemCode(restaurantCode + createItemCode(9, desserts.size()));
    }

    void addItem(CAKE _cake){
        cakes.push_back(_cake);
        cakes[cakes.size()-1].setItemCode(restaurantCode + createItemCode(10, cakes.size()));
    }

    void addItem(BEVERAGE _beverage){
        beverages.push_back(_beverage);
        beverages[beverages.size()-1].setItemCode(restaurantCode + createItemCode(11, beverages.size()));
    }

//Delete Item according to Item Code  
    string deleteItem(string _itemCode){
        int i;
        try{
            i = (stoi(_itemCode.substr(5, 3)) - 1);
        } catch(exception& e){
            return "Invalid Code Entered!";
        }
        if((_itemCode.substr(3, 2) == "00") && (i < pizzas.size())){
            pizzas[i].setStock(0);
            return ("Item Deletion Successful!");
        } else if((_itemCode.substr(3, 2) == "01") && (i < burgers.size())){
            burgers[i].setStock(0);
            return ("Item Deletion Successful!");
        } else if((_itemCode.substr(3, 2) == "02") && (i < sandwiches.size())){
            sandwiches[i].setStock(0);
            return ("Item Deletion Successful!");
        } else if((_itemCode.substr(3, 2) == "03") && (i < fastfoods.size())){
            fastfoods[i].setStock(0);
            return ("Item Deletion Successful!");
        } else if((_itemCode.substr(3, 2) == "04") && (i < barbqs.size())){
            barbqs[i].setStock(0);
            return ("Item Deletion Successful!");
        } else if((_itemCode.substr(3, 2) == "05") && (i < pakistanis.size())){
            pakistanis[i].setStock(0);
            return ("Item Deletion Successful!");
        } else if((_itemCode.substr(3, 2) == "06") && (i < chineses.size())){
            chineses[i].setStock(0);
            return ("Item Deletion Successful!");
        } else if((_itemCode.substr(3, 2) == "07") && (i < internationals.size())){
            internationals[i].setStock(0);
            return ("Item Deletion Successful!");
        } else if((_itemCode.substr(3, 2) == "08") && (i < seafoods.size())){
            seafoods[i].setStock(0);
            return ("Item Deletion Successful!");
        } else if((_itemCode.substr(3, 2) == "09") && (i < desserts.size())){
            desserts[i].setStock(0);
            return ("Item Deletion Successful!");
        } else if((_itemCode.substr(3, 2) == "10") && (i < cakes.size())){
            cakes[i].setStock(0);
            return ("Item Deletion Successful!");
        } else if((_itemCode.substr(3, 2) == "11") && (i < beverages.size())){
            beverages[i].setStock(0);
            return ("Item Deletion Successful!");
        } else{
            return ("Item Deletion Unsuccessful! Invalid Code!");
        }
    }

// Shows All MenuItems in a particular restaurant
    void showFood(int _type){
        int titleSize[9] = {8, 20, 30, 5, 5, 11, 17, 8, 17};
        cout << "\t" << char(218);
        for(int i = 0; i < 9; i++){
            cout << string(titleSize[i], char(196)) << char(194);
        }
        cout << "\b" << char(191) << "\n\t" << char(179) << setw(titleSize[0]) << "CODE " << char(179) << setw(titleSize[1]) << "TITLE " << char(179) << setw(titleSize[2]) << "DESCRIPTION " << char(179) << setw(titleSize[3]) << "STOCK" << char(179) << setw(titleSize[4]) << "LIMIT" << char(179) << setw(titleSize[5]) << "PREP TIME " << char(179) << setw(titleSize[6]) << "PRICE " << char(179) << setw(titleSize[7]) << "DISCOUNT" << char(179) << setw(titleSize[8]) << "VALUE " << char(179) << "\n\t" << char(192);
        for(int i = 0; i < 9; i++){
            cout << string(titleSize[i], char(196)) << char(193);
        }
        cout << "\b" << char(217);
        if(pizzas.size() > 0 && (_type == 12 || _type == 0)){
            cout << "\n\t" << cuisineTitle[0] << "\n\t" << char(218);
            for(int i = 0; i < 9; i++){
                cout << string(titleSize[i], char(196)) << char(194);
            }
            cout << "\b" << char(191);
            for(int i = 0; i < pizzas.size(); i++){
                cout << "\n\t" << char(179) << setw(titleSize[0]) << pizzas[i].getItemCode() << char(179) << setw(titleSize[1]) << pizzas[i].getTitle() << char(179) << setw(titleSize[2]) << pizzas[i].getDescription() << char(179) << setw(titleSize[3]) << pizzas[i].getStock() << char(179) << setw(titleSize[4]) << pizzas[i].getLimit() << char(179) << setw(titleSize[5]) << (to_string(pizzas[i].getPrepTime()) + " Minutes") << char(179) << setw(titleSize[6]) << setw(8) << pizzas[i].getPrice(0) << "-" << setw(8) << pizzas[i].getPrice(pizzas[i].getPrice().size()-1) << char(179) << setw(titleSize[7]) << pizzas[i].getDiscount() << char(179) << setw(titleSize[8]) << setw(8) << pizzas[i].getValue(0) << "-" << setw(8) << pizzas[i].getValue(pizzas[i].getPrice().size()-1) << char(179);
                if(i == (pizzas.size()-1)){
                    cout << "\n\t" << char(192);
                    for(int i = 0; i < 9; i++){
                        cout << string(titleSize[i], char(196)) << char(193);
                    }
                    cout << "\b" << char(217);
                }
            }
            setContinue();
            cleanArea(2, 10, 143, 44);
            gotoxy(2, 9);
        }
        if(burgers.size() > 0 && (_type == 12 || _type == 1)){
            cout << "\n\t" << cuisineTitle[1] << "\n\t" << char(218);
            for(int i = 0; i < 9; i++){
                cout << string(titleSize[i], char(196)) << char(194);
            }
            cout << "\b" << char(191);
            for(int i = 0; i < burgers.size(); i++){
                cout << "\n\t" << char(179) << setw(titleSize[0]) << burgers[i].getItemCode() << char(179) << setw(titleSize[1]) << burgers[i].getTitle() << char(179) << setw(titleSize[2]) << burgers[i].getDescription() << char(179) << setw(titleSize[3]) << burgers[i].getStock() << char(179) << setw(titleSize[4]) << burgers[i].getLimit() << char(179) << setw(titleSize[5]) << (to_string(burgers[i].getPrepTime()) + " Minutes") << char(179) << setw(titleSize[6]) << setw(8) << burgers[i].getPrice() << "-" << setw(8) << burgers[i].getPrice() << char(179) << setw(titleSize[7]) << burgers[i].getDiscount() << char(179) << setw(titleSize[8]) << setw(8) << burgers[i].getValue() << "-" << setw(8) << burgers[i].getValue() << char(179);
                if(i == (burgers.size()-1)){
                    cout << "\n\t" << char(192);
                    for(int i = 0; i < 9; i++){
                        cout << string(titleSize[i], char(196)) << char(193);
                    }
                    cout << "\b" << char(217);
                }
            }
            setContinue();
            cleanArea(2, 10, 143, 44);
            gotoxy(2, 9);
        }
        if(sandwiches.size() > 0 && (_type == 12 || _type == 2)){
            cout << "\n\t" << cuisineTitle[2] << "\n\t" << char(218);
            for(int i = 0; i < 9; i++){
                cout << string(titleSize[i], char(196)) << char(194);
            }
            cout << "\b" << char(191);
            for(int i = 0; i < sandwiches.size(); i++){
                cout << "\n\t" << char(179) << setw(titleSize[0]) << sandwiches[i].getItemCode() << char(179) << setw(titleSize[1]) << sandwiches[i].getTitle() << char(179) << setw(titleSize[2]) << sandwiches[i].getDescription() << char(179) << setw(titleSize[3]) << sandwiches[i].getStock() << char(179) << setw(titleSize[4]) << sandwiches[i].getLimit() << char(179) << setw(titleSize[5]) << (to_string(sandwiches[i].getPrepTime()) + " Minutes") << char(179) << setw(titleSize[6]) << setw(8) << sandwiches[i].getPrice() << "-" << setw(8) << sandwiches[i].getPrice() << char(179) << setw(titleSize[7]) << sandwiches[i].getDiscount() << char(179) << setw(titleSize[8]) << setw(8) << sandwiches[i].getValue() << "-" << setw(8) << sandwiches[i].getValue() << char(179);
                if(i == (sandwiches.size()-1)){
                    cout << "\n\t" << char(192);
                    for(int i = 0; i < 9; i++){
                        cout << string(titleSize[i], char(196)) << char(193);
                    }
                    cout << "\b" << char(217);
                }
            }
            setContinue();
            cleanArea(2, 10, 143, 44);
            gotoxy(2, 9);
        }
        if(fastfoods.size() > 0 && (_type == 12 || _type == 3)){
            cout << "\n\t" << cuisineTitle[3] << "\n\t" << char(218);
            for(int i = 0; i < 9; i++){
                cout << string(titleSize[i], char(196)) << char(194);
            }
            cout << "\b" << char(191);
            for(int i = 0; i < fastfoods.size(); i++){
                cout << "\n\t" << char(179) << setw(titleSize[0]) << fastfoods[i].getItemCode() << char(179) << setw(titleSize[1]) << fastfoods[i].getTitle() << char(179) << setw(titleSize[2]) << fastfoods[i].getDescription() << char(179) << setw(titleSize[3]) << fastfoods[i].getStock() << char(179) << setw(titleSize[4]) << fastfoods[i].getLimit() << char(179) << setw(titleSize[5]) << (to_string(fastfoods[i].getPrepTime()) + " Minutes") << char(179) << setw(titleSize[6]) << setw(8) << fastfoods[i].getPrice() << "-" << setw(8) << fastfoods[i].getPrice() << char(179) << setw(titleSize[7]) << fastfoods[i].getDiscount() << char(179) << setw(titleSize[8]) << setw(8) << fastfoods[i].getValue() << "-" << setw(8) << fastfoods[i].getValue() << char(179);
                if(i == (fastfoods.size()-1)){
                    cout << "\n\t" << char(192);
                    for(int i = 0; i < 9; i++){
                        cout << string(titleSize[i], char(196)) << char(193);
                    }
                    cout << "\b" << char(217);
                }
            }
            setContinue();
            cleanArea(2, 10, 143, 44);
            gotoxy(2, 9);
        }
        if(barbqs.size() > 0 && (_type == 12 || _type == 4)){
            cout << "\n\t" << cuisineTitle[4] << "\n\t" << char(218);
            for(int i = 0; i < 9; i++){
                cout << string(titleSize[i], char(196)) << char(194);
            }
            cout << "\b" << char(191);
            for(int i = 0; i < barbqs.size(); i++){
                cout << "\n\t" << char(179) << setw(titleSize[0]) << barbqs[i].getItemCode() << char(179) << setw(titleSize[1]) << barbqs[i].getTitle() << char(179) << setw(titleSize[2]) << barbqs[i].getDescription() << char(179) << setw(titleSize[3]) << barbqs[i].getStock() << char(179) << setw(titleSize[4]) << barbqs[i].getLimit() << char(179) << setw(titleSize[5]) << (to_string(barbqs[i].getPrepTime()) + " Minutes") << char(179) << setw(titleSize[6]) << setw(8) << barbqs[i].getPrice() << "-" << setw(8) << barbqs[i].getPrice() << char(179) << setw(titleSize[7]) << barbqs[i].getDiscount() << char(179) << setw(titleSize[8]) << setw(8) << barbqs[i].getValue() << "-" << setw(8) << barbqs[i].getValue() << char(179);
                if(i == (barbqs.size()-1)){
                    cout << "\n\t" << char(192);
                    for(int i = 0; i < 9; i++){
                        cout << string(titleSize[i], char(196)) << char(193);
                    }
                    cout << "\b" << char(217);
                }
            }
            setContinue();
            cleanArea(2, 10, 143, 44);
            gotoxy(2, 9);
        }
        if(pakistanis.size() > 0 && (_type == 12 || _type == 5)){
            cout << "\n\t" << cuisineTitle[5] << "\n\t" << char(218);
            for(int i = 0; i < 9; i++){
                cout << string(titleSize[i], char(196)) << char(194);
            }
            cout << "\b" << char(191);
            for(int i = 0; i < pakistanis.size(); i++){
                cout << "\n\t" << char(179) << setw(titleSize[0]) << pakistanis[i].getItemCode() << char(179) << setw(titleSize[1]) << pakistanis[i].getTitle() << char(179) << setw(titleSize[2]) << pakistanis[i].getDescription() << char(179) << setw(titleSize[3]) << pakistanis[i].getStock() << char(179) << setw(titleSize[4]) << pakistanis[i].getLimit() << char(179) << setw(titleSize[5]) << (to_string(pakistanis[i].getPrepTime()) + " Minutes") << char(179) << setw(titleSize[6]) << setw(8) << pakistanis[i].getPrice() << "-" << setw(8) << pakistanis[i].getPrice() << char(179) << setw(titleSize[7]) << pakistanis[i].getDiscount() << char(179) << setw(titleSize[8]) << setw(8) << pakistanis[i].getValue() << "-" << setw(8) << pakistanis[i].getValue() << char(179);
                if(i == (pakistanis.size()-1)){
                    cout << "\n\t" << char(192);
                    for(int i = 0; i < 9; i++){
                        cout << string(titleSize[i], char(196)) << char(193);
                    }
                    cout << "\b" << char(217);
                }
            }
            setContinue();
            cleanArea(2, 10, 143, 44);
            gotoxy(2, 9);
        }
        if(chineses.size() > 0 && (_type == 12 || _type == 6)){
            cout << "\n\t" << cuisineTitle[6] << "\n\t" << char(218);
            for(int i = 0; i < 9; i++){
                cout << string(titleSize[i], char(196)) << char(194);
            }
            cout << "\b" << char(191);
            for(int i = 0; i < chineses.size(); i++){
                cout << "\n\t" << char(179) << setw(titleSize[0]) << chineses[i].getItemCode() << char(179) << setw(titleSize[1]) << chineses[i].getTitle() << char(179) << setw(titleSize[2]) << chineses[i].getDescription() << char(179) << setw(titleSize[3]) << chineses[i].getStock() << char(179) << setw(titleSize[4]) << chineses[i].getLimit() << char(179) << setw(titleSize[5]) << (to_string(chineses[i].getPrepTime()) + " Minutes") << char(179) << setw(titleSize[6]) << setw(8) << chineses[i].getPrice() << "-" << setw(8) << chineses[i].getPrice() << char(179) << setw(titleSize[7]) << chineses[i].getDiscount() << char(179) << setw(titleSize[8]) << setw(8) << chineses[i].getValue() << "-" << setw(8) << chineses[i].getValue() << char(179);
                if(i == (chineses.size()-1)){
                    cout << "\n\t" << char(192);
                    for(int i = 0; i < 9; i++){
                        cout << string(titleSize[i], char(196)) << char(193);
                    }
                    cout << "\b" << char(217);
                }
            }
            setContinue();
            cleanArea(2, 10, 143, 44);
            gotoxy(2, 9);
        }
        if(internationals.size() > 0 && (_type == 12 || _type == 7)){
            cout << "\n\t" << cuisineTitle[7] << "\n\t" << char(218);
            for(int i = 0; i < 9; i++){
                cout << string(titleSize[i], char(196)) << char(194);
            }
            cout << "\b" << char(191);
            for(int i = 0; i < internationals.size(); i++){
                cout << "\n\t" << char(179) << setw(titleSize[0]) << internationals[i].getItemCode() << char(179) << setw(titleSize[1]) << internationals[i].getTitle() << char(179) << setw(titleSize[2]) << internationals[i].getDescription() << char(179) << setw(titleSize[3]) << internationals[i].getStock() << char(179) << setw(titleSize[4]) << internationals[i].getLimit() << char(179) << setw(titleSize[5]) << (to_string(internationals[i].getPrepTime()) + " Minutes") << char(179) << setw(titleSize[6]) << setw(8) << internationals[i].getPrice() << "-" << setw(8) << internationals[i].getPrice() << char(179) << setw(titleSize[7]) << internationals[i].getDiscount() << char(179) << setw(titleSize[8]) << setw(8) << internationals[i].getValue() << "-" << setw(8) << internationals[i].getValue() << char(179);
                if(i == (internationals.size()-1)){
                    cout << "\n\t" << char(192);
                    for(int i = 0; i < 9; i++){
                        cout << string(titleSize[i], char(196)) << char(193);
                    }
                    cout << "\b" << char(217);
                }
            }
            setContinue();
            cleanArea(2, 10, 143, 44);
            gotoxy(2, 9);
        }
        if(seafoods.size() > 0 && (_type == 12 || _type == 8)){
            cout << "\n\t" << cuisineTitle[8] << "\n\t" << char(218);
            for(int i = 0; i < 9; i++){
                cout << string(titleSize[i], char(196)) << char(194);
            }
            cout << "\b" << char(191);
            for(int i = 0; i < seafoods.size(); i++){
                cout << "\n\t" << char(179) << setw(titleSize[0]) << seafoods[i].getItemCode() << char(179) << setw(titleSize[1]) << seafoods[i].getTitle() << char(179) << setw(titleSize[2]) << seafoods[i].getDescription() << char(179) << setw(titleSize[3]) << seafoods[i].getStock() << char(179) << setw(titleSize[4]) << seafoods[i].getLimit() << char(179) << setw(titleSize[5]) << (to_string(seafoods[i].getPrepTime()) + " Minutes") << char(179) << setw(titleSize[6]) << setw(8) << seafoods[i].getPrice() << "-" << setw(8) << seafoods[i].getPrice() << char(179) << setw(titleSize[7]) << seafoods[i].getDiscount() << char(179) << setw(titleSize[8]) << setw(8) << seafoods[i].getValue() << "-" << setw(8) << seafoods[i].getValue() << char(179);
                if(i == (seafoods.size()-1)){
                    cout << "\n\t" << char(192);
                    for(int i = 0; i < 9; i++){
                        cout << string(titleSize[i], char(196)) << char(193);
                    }
                    cout << "\b" << char(217);
                }
            }
            setContinue();
            cleanArea(2, 10, 143, 44);
            gotoxy(2, 9);
        }
        if(desserts.size() > 0 && (_type == 12 || _type == 9)){
            cout << "\n\t" << cuisineTitle[9] << "\n\t" << char(218);
            for(int i = 0; i < 9; i++){
                cout << string(titleSize[i], char(196)) << char(194);
            }
            cout << "\b" << char(191);
            for(int i = 0; i < desserts.size(); i++){
                cout << "\n\t" << char(179) << setw(titleSize[0]) << desserts[i].getItemCode() << char(179) << setw(titleSize[1]) << desserts[i].getTitle() << char(179) << setw(titleSize[2]) << desserts[i].getDescription() << char(179) << setw(titleSize[3]) << desserts[i].getStock() << char(179) << setw(titleSize[4]) << desserts[i].getLimit() << char(179) << setw(titleSize[5]) << (to_string(desserts[i].getPrepTime()) + " Minutes") << char(179) << setw(titleSize[6]) << setw(8) << desserts[i].getPrice() << "-" << setw(8) << desserts[i].getPrice() << char(179) << setw(titleSize[7]) << desserts[i].getDiscount() << char(179) << setw(titleSize[8]) << setw(8) << desserts[i].getValue() << "-" << setw(8) << desserts[i].getValue() << char(179);
                if(i == (desserts.size()-1)){
                    cout << "\n\t" << char(192);
                    for(int i = 0; i < 9; i++){
                        cout << string(titleSize[i], char(196)) << char(193);
                    }
                    cout << "\b" << char(217);
                }
            }
            setContinue();
            cleanArea(2, 10, 143, 44);
            gotoxy(2, 9);
        }
        if(cakes.size() > 0 && (_type == 12 || _type == 10)){
            cout << "\n\t" << cuisineTitle[10] << "\n\t" << char(218);
            for(int i = 0; i < 9; i++){
                cout << string(titleSize[i], char(196)) << char(194);
            }
            cout << "\b" << char(191);
            for(int i = 0; i < cakes.size(); i++){
                cout << "\n\t" << char(179) << setw(titleSize[0]) << cakes[i].getItemCode() << char(179) << setw(titleSize[1]) << cakes[i].getTitle() << char(179) << setw(titleSize[2]) << cakes[i].getDescription() << char(179) << setw(titleSize[3]) << cakes[i].getStock() << char(179) << setw(titleSize[4]) << cakes[i].getLimit() << char(179) << setw(titleSize[5]) << (to_string(cakes[i].getPrepTime()) + " Minutes") << char(179) << setw(titleSize[6]) << setw(8) << cakes[i].getPrice() << "-" << setw(8) << cakes[i].getPrice() << char(179) << setw(titleSize[7]) << cakes[i].getDiscount() << char(179) << setw(titleSize[8]) << setw(8) << cakes[i].getValue() << "-" << setw(8) << cakes[i].getValue() << char(179);
                if(i == (cakes.size()-1)){
                    cout << "\n\t" << char(192);
                    for(int i = 0; i < 9; i++){
                        cout << string(titleSize[i], char(196)) << char(193);
                    }
                    cout << "\b" << char(217);
                }
            }
            setContinue();
            cleanArea(2, 10, 143, 44);
            gotoxy(2, 9);
        }
        if(beverages.size() > 0 && (_type == 12 || _type == 11)){
            cout << "\n\t" << cuisineTitle[11] << "\n\t" << char(218);
            for(int i = 0; i < 9; i++){
                cout << string(titleSize[i], char(196)) << char(194);
            }
            cout << "\b" << char(191);
            for(int i = 0; i < beverages.size(); i++){
                cout << "\n\t" << char(179) << setw(titleSize[0]) << beverages[i].getItemCode() << char(179) << setw(titleSize[1]) << beverages[i].getTitle() << char(179) << setw(titleSize[2]) << beverages[i].getDescription() << char(179) << setw(titleSize[3]) << beverages[i].getStock() << char(179) << setw(titleSize[4]) << beverages[i].getLimit() << char(179) << setw(titleSize[5]) << (to_string(beverages[i].getPrepTime()) + " Minutes") << char(179) << setw(titleSize[6]) << setw(8) << beverages[i].getPrice() << "-" << setw(8) << beverages[i].getPrice() << char(179) << setw(titleSize[7]) << beverages[i].getDiscount() << char(179) << setw(titleSize[8]) << setw(8) << beverages[i].getValue() << "-" << setw(8) << beverages[i].getValue() << char(179);
                if(i == (beverages.size()-1)){
                    cout << "\n\t" << char(192);
                    for(int i = 0; i < 9; i++){
                        cout << string(titleSize[i], char(196)) << char(193);
                    }
                    cout << "\b" << char(217);
                }
            }
            setContinue();
            cleanArea(2, 10, 143, 44);
            gotoxy(2, 9);
        }
    }

// using to display details of pizza using showFood function
    void showFoodItem(PIZZA _pizza){
        gotoxy(2, 7);
        cout << "\tItem Code:\t" << _pizza.getItemCode() << "\n\n\tTitle:\t" << _pizza.getTitle() << "\n\n\tDescription:\t" << _pizza.getDescription() << "\n\n\tCuisine:\t" << cuisineTitle[_pizza.getCuisine()] << "\n\n\tStock:\t" << _pizza.getStock() << "\n\n\tLimit:\t" << _pizza.getLimit() << "\n\n\tPrepration Time:\t" << _pizza.getPrepTime() << "\n\n\tSizes Available:";
        for(int i = 0; i < _pizza.getSizeLength(); i++){
            cout << "\n\t\t" << _pizza.getSize(i) << ":\t" << _pizza.getPrice(i);
        }
        cout << "\n\n\tDiscount Percentage:\t" << _pizza.getDiscount() << "%";
        setMessage("Item Found!");
    }

// using to display details of food using showFood function
    void showFoodItem(FOOD _food){
        gotoxy(2, 7);
        cout << "\tItem Code:\t\t" << _food.getItemCode() << "\n\n\tTitle:\t\t\t" << _food.getTitle() << "\n\n\tDescription:\t\t" << _food.getDescription() << "\n\n\tCuisine:\t\t" << cuisineTitle[_food.getCuisine()] << "\n\n\tStock:\t\t\t" << _food.getStock() << "\n\n\tLimit:\t\t\t" << _food.getLimit() << "\n\n\tPrepration Time:\t" << _food.getPrepTime() << "\n\n\tPrice:\t\t\t" << _food.getPrice() << "\n\n\tDiscount Percentage:\t" << _food.getDiscount() << "%";
        setMessage("Item Found!");
    }

// To show All Food details
    void showFood(string _code){
        int _index;
        try{
            _index = (stoi(_code.substr(5, 3)) - 1);
        } catch(exception& e){
            setMessage("Invalid Code Entered!");
            return;
        }
        if(_code.substr(3, 2) == "00"){
            if(pizzas.size() > _index){
                showFoodItem(pizzas[_index]);
            } else{
                setMessage("Invalid Code!");
            }
        } else if(_code.substr(3, 2) == "01"){
            if(burgers.size() > _index){
                showFoodItem(burgers[_index]);
            } else{
                setMessage("Invalid Code!");
            }
        } else if(_code.substr(3, 2) == "02"){
            if(sandwiches.size() > _index){
                showFoodItem(sandwiches[_index]);
            } else{
                setMessage("Invalid Code!");
            }
        } else if(_code.substr(3, 2) == "03"){
            if(fastfoods.size() > _index){
                showFoodItem(fastfoods[_index]);
            } else{
                setMessage("Invalid Code!");
            }
        } else if(_code.substr(3, 2) == "04"){
            if(barbqs.size() > _index){
                showFoodItem(barbqs[_index]);
            } else{
                setMessage("Invalid Code!");
            }
        } else if(_code.substr(3, 2) == "05"){
            if(pakistanis.size() > _index){
                showFoodItem(pakistanis[_index]);
            } else{
                setMessage("Invalid Code!");
            }
        } else if(_code.substr(3, 2) == "06"){
            if(chineses.size() > _index){
                showFoodItem(chineses[_index]);
            } else{
                setMessage("Invalid Code!");
            }
        } else if(_code.substr(3, 2) == "07"){
            if(internationals.size() > _index){
                showFoodItem(internationals[_index]);
            } else{
                setMessage("Invalid Code!");
            }
        } else if(_code.substr(3, 2) == "08"){
            if(seafoods.size() > _index){
                showFoodItem(seafoods[_index]);
            } else{
                setMessage("Invalid Code!");
            }
        } else if(_code.substr(3, 2) == "09"){
            if(desserts.size() > _index){
                showFoodItem(desserts[_index]);
            } else{
                setMessage("Invalid Code!");
            }
        } else if(_code.substr(3, 2) == "10"){
            if(cakes.size() > _index){
                showFoodItem(cakes[_index]);
            } else{
                setMessage("Invalid Code!");
            }
        } else if(_code.substr(3, 2) == "11"){
            if(beverages.size() > _index){
                showFoodItem(beverages[_index]);
            } else{
                setMessage("Invalid Code!");
            }
        } else{
            setMessage("Invalid Code!");
        }
    }

// Display Restaurants based on particular cuisine
    void displayRestMenu(int _cuisine){
        int title[6] = {10, 20, 30, 19, 8, 15};
        cout << "\t\t\t\t" << char(218);
        for(int i = 0; i < 6; i++){
            cout << string(title[i], char(196)) << char(194);
        }
        cout << "\b" << char(191) << "\n\t\t\t\t" << char(179) << setw(title[0]) << "ItemCode " << char(179) << setw(title[1]) << "TITLE " << char(179) << setw(title[2]) << "DESCRIPTION " << char(179) << setw(title[3]) << "PRICE " << char(179) << setw(title[4]) << "DISCOUNT" << char(179) << setw(title[5]) << "DELIVERY TIME " << char(179);
        cout << "\n\t\t\t\t" << char(195);
        for(int i = 0; i < 6; i++){
            cout << string(title[i], char(196)) << char(197);
        }
        cout << "\b" << char(180);
        switch (_cuisine){
        case 0:
            if(hasFood(cuisineTitle[_cuisine]) == true){
                for(int j = 0; j < pizzas.size(); j++){
                    cout << "\n\t\t\t\t" << char(179) << setw(title[0]) << pizzas[j].getItemCode() << char(179) << setw(title[1]) << pizzas[j].getTitle() << char(179) << setw(title[2]) << pizzas[j].getDescription() << char(179) << setw(8) << pizzas[j].getPrice(0) << " - " << setw(8) << pizzas[j].getPrice(pizzas[j].getSize().size()-1) << char(179) << setw(title[4]) << pizzas[j].getDiscount() << char(179) << setw(title[5]) << (to_string(pizzas[j].getPrepTime()) + " Minutes ") << char(179);
                }
            } else{
                cout << "\n\t\t\t\t" << char(179) << " No Item Available in Cuisine: " << cuisineTitle[_cuisine] << char(179);
            }
            break;

        case 1:
            if(hasFood(cuisineTitle[_cuisine]) == true){
                for(int j = 0; j < burgers.size(); j++){
                    cout << "\n\t\t\t\t" << char(179) << setw(title[0]) << burgers[j].getItemCode() << char(179) << setw(title[1]) << burgers[j].getTitle() << char(179) << setw(title[2]) << burgers[j].getDescription() << char(179) << setw(8) << burgers[j].getPrice() << " - " << setw(8) << burgers[j].getPrice() << char(179) << setw(title[4]) << burgers[j].getDiscount() << char(179) << setw(title[5]) << (to_string(burgers[j].getPrepTime()) + " Minutes ") << char(179);
                }
            } else{
                cout << "\n\t\t\t\t" << char(179) << " No Item Available in Cuisine: " << cuisineTitle[_cuisine] << char(179);
            }
            break;

        case 2:
            if(hasFood(cuisineTitle[_cuisine]) == true){
                for(int j = 0; j < sandwiches.size(); j++){
                    cout << "\n\t\t\t\t" << char(179) << setw(title[0]) << sandwiches[j].getItemCode() << char(179) << setw(title[1]) << sandwiches[j].getTitle() << char(179) << setw(title[2]) << sandwiches[j].getDescription() << char(179) << setw(8) << sandwiches[j].getPrice() << " - " << setw(8) << sandwiches[j].getPrice() << char(179) << setw(title[4]) << sandwiches[j].getDiscount() << char(179) << setw(title[5]) << (to_string(sandwiches[j].getPrepTime()) + " Minutes ") << char(179);
                }
            } else{
                cout << "\n\t\t\t\t" << char(179) << " No Item Available in Cuisine: " << cuisineTitle[_cuisine] << char(179);
            }
            break;

        case 3:
            if(hasFood(cuisineTitle[_cuisine]) == true){
                for(int j = 0; j < fastfoods.size(); j++){
                    cout << "\n\t\t\t\t" << char(179) << setw(title[0]) << fastfoods[j].getItemCode() << char(179) << setw(title[1]) << fastfoods[j].getTitle() << char(179) << setw(title[2]) << fastfoods[j].getDescription() << char(179) << setw(8) << fastfoods[j].getPrice() << " - " << setw(8) << fastfoods[j].getPrice() << char(179) << setw(title[4]) << fastfoods[j].getDiscount() << char(179) << setw(title[5]) << (to_string(fastfoods[j].getPrepTime()) + " Minutes ") << char(179);
                }
            } else{
                cout << "\n\t\t\t\t" << char(179) << " No Item Available in Cuisine: " << cuisineTitle[_cuisine] << char(179);
            }
            break;

        case 4:
            if(hasFood(cuisineTitle[_cuisine]) == true){
                for(int j = 0; j < barbqs.size(); j++){
                    cout << "\n\t\t\t\t" << char(179) << setw(title[0]) << barbqs[j].getItemCode() << char(179) << setw(title[1]) << barbqs[j].getTitle() << char(179) << setw(title[2]) << barbqs[j].getDescription() << char(179) << setw(8) << barbqs[j].getPrice() << " - " << setw(8) << barbqs[j].getPrice() << char(179) << setw(title[4]) << barbqs[j].getDiscount() << char(179) << setw(title[5]) << (to_string(barbqs[j].getPrepTime()) + " Minutes ") << char(179);
                }
            } else{
                cout << "\n\t\t\t\t" << char(179) << " No Item Available in Cuisine: " << cuisineTitle[_cuisine] << char(179);
            }
            break;

        case 5:
            if(hasFood(cuisineTitle[_cuisine]) == true){
                for(int j = 0; j < pakistanis.size(); j++){
                    cout << "\n\t\t\t\t" << char(179) << setw(title[0]) << pakistanis[j].getItemCode() << char(179) << setw(title[1]) << pakistanis[j].getTitle() << char(179) << setw(title[2]) << pakistanis[j].getDescription() << char(179) << setw(8) << pakistanis[j].getPrice() << " - " << setw(8) << pakistanis[j].getPrice() << char(179) << setw(title[4]) << pakistanis[j].getDiscount() << char(179) << setw(title[5]) << (to_string(pakistanis[j].getPrepTime()) + " Minutes ") << char(179);
                }
            } else{
                cout << "\n\t\t\t\t" << char(179) << " No Item Available in Cuisine: " << cuisineTitle[_cuisine] << char(179);
            }
            break;

        case 6:
            if(hasFood(cuisineTitle[_cuisine]) == true){
                for(int j = 0; j < chineses.size(); j++){
                    cout << "\n\t\t\t\t" << char(179) << setw(title[0]) << chineses[j].getItemCode() << char(179) << setw(title[1]) << chineses[j].getTitle() << char(179) << setw(title[2]) << chineses[j].getDescription() << char(179) << setw(8) << chineses[j].getPrice() << " - " << setw(8) << chineses[j].getPrice() << char(179) << setw(title[4]) << chineses[j].getDiscount() << char(179) << setw(title[5]) << (to_string(chineses[j].getPrepTime()) + " Minutes ") << char(179);
                }
            } else{
                cout << "\n\t\t\t\t" << char(179) << " No Item Available in Cuisine: " << cuisineTitle[_cuisine] << char(179);
            }
            break;

        case 7:
            if(hasFood(cuisineTitle[_cuisine]) == true){
                for(int j = 0; j < internationals.size(); j++){
                    cout << "\n\t\t\t\t" << char(179) << setw(title[0]) << internationals[j].getItemCode() << char(179) << setw(title[1]) << internationals[j].getTitle() << char(179) << setw(title[2]) << internationals[j].getDescription() << char(179) << setw(8) << internationals[j].getPrice() << " - " << setw(8) << internationals[j].getPrice() << char(179) << setw(title[4]) << internationals[j].getDiscount() << char(179) << setw(title[5]) << (to_string(internationals[j].getPrepTime()) + " Minutes ") << char(179);
                }
            } else{
                cout << "\n\t\t\t\t" << char(179) << " No Item Available in Cuisine: " << cuisineTitle[_cuisine] << char(179);
            }
            break;

        case 8:
            if(hasFood(cuisineTitle[_cuisine]) == true){
                for(int j = 0; j < seafoods.size(); j++){
                    cout << "\n\t\t\t\t" << char(179) << setw(title[0]) << seafoods[j].getItemCode() << char(179) << setw(title[1]) << seafoods[j].getTitle() << char(179) << setw(title[2]) << seafoods[j].getDescription() << char(179) << setw(8) << seafoods[j].getPrice() << " - " << setw(8) << seafoods[j].getPrice() << char(179) << setw(title[4]) << seafoods[j].getDiscount() << char(179) << setw(title[5]) << (to_string(seafoods[j].getPrepTime()) + " Minutes ") << char(179);
                }
            } else{
                cout << "\n\t\t\t\t" << char(179) << " No Item Available in Cuisine: " << cuisineTitle[_cuisine] << char(179);
            }
            break;

        case 9:
            if(hasFood(cuisineTitle[_cuisine]) == true){
                for(int j = 0; j < desserts.size(); j++){
                    cout << "\n\t\t\t\t" << char(179) << setw(title[0]) << desserts[j].getItemCode() << char(179) << setw(title[1]) << desserts[j].getTitle() << char(179) << setw(title[2]) << desserts[j].getDescription() << char(179) << setw(8) << desserts[j].getPrice() << " - " << setw(8) << desserts[j].getPrice() << char(179) << setw(title[4]) << desserts[j].getDiscount() << char(179) << setw(title[5]) << (to_string(desserts[j].getPrepTime()) + " Minutes ") << char(179);
                }
            } else{
                cout << "\n\t\t\t\t" << char(179) << " No Item Available in Cuisine: " << cuisineTitle[_cuisine] << char(179);
            }
            break;

        case 10:
            if(hasFood(cuisineTitle[_cuisine]) == true){
                for(int j = 0; j < cakes.size(); j++){
                    cout << "\n\t\t\t\t" << char(179) << setw(title[0]) << cakes[j].getItemCode() << char(179) << setw(title[1]) << cakes[j].getTitle() << char(179) << setw(title[2]) << cakes[j].getDescription() << char(179) << setw(8) << cakes[j].getPrice() << " - " << setw(8) << cakes[j].getPrice() << char(179) << setw(title[4]) << cakes[j].getDiscount() << char(179) << setw(title[5]) << (to_string(cakes[j].getPrepTime()) + " Minutes ") << char(179);
                }
            } else{
                cout << "\n\t\t\t\t" << char(179) << " No Item Available in Cuisine: " << cuisineTitle[_cuisine] << char(179);
            }
            break;

        case 11:
            if(hasFood(cuisineTitle[_cuisine]) == true){
                for(int j = 0; j < beverages.size(); j++){
                    cout << "\n\t\t\t\t" << char(179) << setw(title[0]) << beverages[j].getItemCode() << char(179) << setw(title[1]) << beverages[j].getTitle() << char(179) << setw(title[2]) << beverages[j].getDescription() << char(179) << setw(8) << beverages[j].getPrice() << " - " << setw(8) << beverages[j].getPrice() << char(179) << setw(title[4]) << beverages[j].getDiscount() << char(179) << setw(title[5]) << (to_string(beverages[j].getPrepTime()) + " Minutes ") << char(179);
                }
            } else{
                cout << "\n\t\t\t\t" << char(179) << " No Item Available in Cuisine: " << cuisineTitle[_cuisine] << char(179);
            }
            break;
        
        default:
            break;
        }
        cout << "\n\t\t\t\t" << char(192);
        for(int i = 0; i < 6; i++){
            cout << string(title[i], char(196)) << char(193);
        }
        cout << "\b" << char(217) << endl;
    }


// sends pointer object of  a particular food on index of particular cuisine 
    PIZZA * getPizza(int _index){
        if(_index < pizzas.size()){
            return &pizzas[_index];
        }
    }

    BURGER * getBurger(int _index){
        if(_index < burgers.size()){
            return &burgers[_index];
        }
    }

    SANDWICHE * getSandwich(int _index){
        if(_index < sandwiches.size()){
            return &sandwiches[_index];
        }
    }

    FASTFOOD * getFastFood(int _index){
        if(_index < fastfoods.size()){
            return &fastfoods[_index];
        }
    }

    BARBQ * getBarbq(int _index){
        if(_index < barbqs.size()){
            return &barbqs[_index];
        }
    }

    PAKISTANI * getPakistani(int _index){
        if(_index < pakistanis.size()){
            return &pakistanis[_index];
        }
    }

    CHINESE * getChinese(int _index){
        if(_index < chineses.size()){
            return &chineses[_index];
        }
    }

    INTERNATIONAL * getInternational(int _index){
        if(_index < internationals.size()){
            return &internationals[_index];
        }
    }

    SEAFOOD * getSeafood(int _index){
        if(_index < seafoods.size()){
            return &seafoods[_index];
        }
    }

    DESSERT * getDessert(int _index){
        if(_index < desserts.size()){
            return &desserts[_index];
        }
    }

    CAKE * getCake(int _index){
        if(_index < cakes.size()){
            return &cakes[_index];
        }
    }

    BEVERAGE * getBeverage(int _index){
        if(_index < beverages.size()){
            return &beverages[_index];
        }
    }

// returns size of Pizza
    int getPizzaItemSize(int _index){
        return pizzas[_index].getSizeLength(); // e.g small , medium , large
    }

// shows details of Restaurant
    void showDetails(){
        cout << "\tTitle:\t\t\t" << title << "\n\n\tDescription:\t\t" << description.substr(0, 100) << "\n\n\tManager ID:\t\t" << managerID << string(45 - managerID.length(), ' ') << "Code:\t\t" << restaurantCode << "\n\n\tContact Number:\t\t" << contactNumber << string(45 - contactNumber.length(), ' ') << "Address:\t\t" << address << "\n\n\tArea:\t\t\t" << getArea() << string(45 - getArea().length(), ' ') << "City:\t\t" << getCity() << "\n\n\tActive:\t\t\t" << setw(5) << isRestActive << string(40, ' ') << "Open:\t\t" << isRestOpen << "\n\n\tFree Delivery:\t\t" << setw(5) << freeDelivery << string(40, ' ') << "Minimum Order:\t" << minimumOrder << "\n\n\tDelivery Charges:\t" << deliveryCharges << string(49 - to_string(deliveryCharges).length(), ' ') << "Discount:\t\t" << (restDiscount * 100) << "%\n\n\tTotal Income:\t\t" << restRevenue << string(49 - to_string(restRevenue).length(), ' ') << "Tax:\t\t" << restTax << "\n\n\tOrders Pending:\t\t" << ordersPending << string(45 - to_string(ordersPending).length(), ' ') << "Orders Completed:\t" << ordersCompleted << "\n\n\tOrders Cancelled:\t" << ordersCancelled << string(45 - to_string(ordersCancelled).length(), ' ') << "Timings:\t\t" << openTime << " - " << (closeTime + 1);
        cout << "\n\n\n\tWORKING DAYS\n\t" << char(218);
        for(int i = 0; i < days.size(); i++){
            cout << string(days[i].length(), char(196)) << char(194);
        }
        cout << "\b" << char(191) << "\n\t" << char(179);
        for(int i = 0; i < days.size(); i++){
            cout << days[i] << char(179);
        }
        cout << "\n\t" << char(195);
        for(int i = 0; i < days.size(); i++){
            cout << string(days[i].length(), char(196)) << char(197);
        }
        cout << "\b" << char(180) << "\n\t" << char(179);
        for(int j = 0; j < days.size(); j++){
            if(daysOpen[j] == true){cout << " YES" << string((days[j].length() - 4), ' ') << char(179);} else{
            cout << " NO" << string((days[j].length() - 3), ' ') << char(179);}
        }
        cout << "\n\t" << char(192);
        for(int i = 0; i < days.size(); i++){
            cout << string(days[i].length(), char(196)) << char(193);
        }
        cout << "\b" << char(217);
        
        cout << "\n\n\n\tCUISINES AVAILABLE\n\t" << char(218);
        for(int i = 0; i < cuisineTitle.size(); i++){
            cout << string(cuisineTitle[i].length(), char(196)) << char(194);
        }
        cout << "\b" << char(191) << "\n\t" << char(179);
        for(int i = 0; i < cuisineTitle.size(); i++){
            cout << cuisineTitle[i] << char(179);
        }
        cout << "\n\t" << char(195);
        for(int i = 0; i < cuisineTitle.size(); i++){
            cout << string(cuisineTitle[i].length(), char(196)) << char(197);
        }
        cout << "\b" << char(180) << "\n\t" << char(179);

        for(int j = 0; j < cuisineTitle.size(); j++){
            if(hasFood(cuisineTitle[j]) == true){cout << " YES" << string((cuisineTitle[j].length() - 4), ' ') << char(179);} else{
            cout << " NO" << string((cuisineTitle[j].length() - 3), ' ') << char(179);}
        }
        
        cout << "\n\t" << char(192);
        for(int i = 0; i < cuisineTitle.size(); i++){
            cout << string(cuisineTitle[i].length(), char(196)) << char(193);
        }
        cout << "\b" << char(217) << "\n\t";
    }

// Displays days when restaurant is open/close 
    void displayDays(){
        cout << "\n\t" << char(218) << string(6, char(196));
        for(int i=0;i< days.size();i++){
            cout << char(194) << string(days[i].length(),char(196));
        }
        cout << char(191) << "\n\t" << char(179) << " CODE " << char(179);
        for(int i = 0; i < days.size();i++){
            cout << setw(days[i].length()-2) << i << "  " << char(179);
        }
        cout << "\n\t" << char(195) << string(6, char(196));
        for(int i=0;i< days.size();i++){
            cout << char(197) << string(days[i].length(),char(196));
        }
        cout << char(180) << "\n\t" << char(179) << " DAYS ";
        for(int i=0;i< days.size();i++){
            cout << char(179) << days[i];
        }
        cout << char(179) << "\n\t" << char(195) << string(6, char(196));
        for(int i=0;i< days.size();i++){
            cout << char(197) << string(days[i].length(),char(196));
        }
        cout << char(180) << "\n\t" << char(179) << "STATUS";
        for(int i=0;i< days.size();i++){
            cout << char(179);
            if(daysOpen[i]==true){
                cout << setw(days[i].length()) << "OPEN";
            } else{
                cout << setw(days[i].length()) << "CLOSE";
            }
        }
        cout << char(179) << "\n\t" << char(192) << string(6,char(196));
        for(int i=0;i< days.size();i++){
            cout << char(193) << string(days[i].length(),char(196));
        }
        cout << char(217);
    }

// to update stock after order has been completed for all cuisines 
    void changeStock(vector<ORDERITEM> orderItems){
        for(int i = 0; i < orderItems.size(); i++){
            int itemIndex = (stoi(orderItems[i].getCode().substr(5, 3)) - 1);
            switch(orderItems[i].getCuisine()){
            case 0:
                for(int j = 0; j < pizzas.size(); j++){
                    if(orderItems[i].getCode() == pizzas[j].getItemCode()){
                        pizzas[j].setStock(pizzas[j].getStock() - orderItems[i].getQuantity());
                    }
                }
                break;

            case 1:
                for(int j = 0; j < burgers.size(); j++){
                    if(orderItems[i].getCode() == burgers[j].getItemCode()){
                        burgers[j].setStock(burgers[j].getStock() - orderItems[i].getQuantity());
                    }
                }
                break;

            case 2:
                for(int j = 0; j < sandwiches.size(); j++){
                    if(orderItems[i].getCode() == sandwiches[j].getItemCode()){
                        sandwiches[j].setStock(sandwiches[j].getStock() - orderItems[i].getQuantity());
                    }
                }
                break;

            case 3:
                for(int j = 0; j < fastfoods.size(); j++){
                    if(orderItems[i].getCode() == fastfoods[j].getItemCode()){
                        fastfoods[j].setStock(fastfoods[j].getStock() - orderItems[i].getQuantity());
                    }
                }
                break;

            case 4:
                for(int j = 0; j < barbqs.size(); j++){
                    if(orderItems[i].getCode() == barbqs[j].getItemCode()){
                        barbqs[j].setStock(barbqs[j].getStock() - orderItems[i].getQuantity());
                    }
                }
                break;

            case 5:
                for(int j = 0; j < pakistanis.size(); j++){
                    if(orderItems[i].getCode() == pakistanis[j].getItemCode()){
                        pakistanis[j].setStock(pakistanis[j].getStock() - orderItems[i].getQuantity());
                    }
                }
                break;

            case 6:
                for(int j = 0; j < chineses.size(); j++){
                    if(orderItems[i].getCode() == chineses[j].getItemCode()){
                        chineses[j].setStock(chineses[j].getStock() - orderItems[i].getQuantity());
                    }
                }
                break;

            case 7:
                for(int j = 0; j < internationals.size(); j++){
                    if(orderItems[i].getCode() == internationals[j].getItemCode()){
                        internationals[j].setStock(internationals[j].getStock() - orderItems[i].getQuantity());
                    }
                }
                break;

            case 8:
                for(int j = 0; j < seafoods.size(); j++){
                    if(orderItems[i].getCode() == seafoods[j].getItemCode()){
                        seafoods[j].setStock(seafoods[j].getStock() - orderItems[i].getQuantity());
                    }
                }
                break;

            case 9:
                for(int j = 0; j < desserts.size(); j++){
                    if(orderItems[i].getCode() == desserts[j].getItemCode()){
                        desserts[j].setStock(desserts[j].getStock() - orderItems[i].getQuantity());
                    }
                }
                break;

            case 10:
                for(int j = 0; j < cakes.size(); j++){
                    if(orderItems[i].getCode() == cakes[j].getItemCode()){
                        cakes[j].setStock(cakes[j].getStock() - orderItems[i].getQuantity());
                    }
                }
                break;

            case 11:
                for(int j = 0; j < beverages.size(); j++){
                    if(orderItems[i].getCode() == beverages[j].getItemCode()){
                        beverages[j].setStock(beverages[j].getStock() - orderItems[i].getQuantity());
                    }
                }
                break;
            
            default:
                break;
            }
        }
    }

// limit and quantity are checked as well as stock is updated and revenue is generated
    double confirmOrder(ORDER &_order){
        vector<ORDERITEM> orderItems = _order.getOrderItems();
        for(int i = 0; i < orderItems.size(); i++){
            int foodIndex = (stoi(orderItems[i].getCode().substr(5, 3)) - 1);
            switch(orderItems[i].getCuisine()){
            case 0:
                if(orderItems[i].getQuantity() > pizzas[foodIndex].getLimit() || orderItems[i].getQuantity() > pizzas[foodIndex].getStock()){
                    return 0;
                }
                break;

            case 1:
                if(orderItems[i].getQuantity() > burgers[foodIndex].getLimit() || orderItems[i].getQuantity() > burgers[foodIndex].getStock()){
                    return 0;
                }
                break;

            case 2:
                if(orderItems[i].getQuantity() > sandwiches[foodIndex].getLimit() || orderItems[i].getQuantity() > sandwiches[foodIndex].getStock()){
                    return 0;
                }
                break;

            case 3:
                if(orderItems[i].getQuantity() > fastfoods[foodIndex].getLimit() || orderItems[i].getQuantity() > fastfoods[foodIndex].getStock()){
                    return 0;
                }
                break;

            case 4:
                if(orderItems[i].getQuantity() > barbqs[foodIndex].getLimit() || orderItems[i].getQuantity() > barbqs[foodIndex].getStock()){
                    return 0;
                }
                break;

            case 5:
                if(orderItems[i].getQuantity() > pakistanis[foodIndex].getLimit() || orderItems[i].getQuantity() > pakistanis[foodIndex].getStock()){
                    return 0;
                }
                break;

            case 6:
                if(orderItems[i].getQuantity() > chineses[foodIndex].getLimit() || orderItems[i].getQuantity() > chineses[foodIndex].getStock()){
                    return 0;
                }
                break;

            case 7:
                if(orderItems[i].getQuantity() > internationals[foodIndex].getLimit() || orderItems[i].getQuantity() > internationals[foodIndex].getStock()){
                    return 0;
                }
                break;

            case 8:
                if(orderItems[i].getQuantity() > seafoods[foodIndex].getLimit() || orderItems[i].getQuantity() > seafoods[foodIndex].getStock()){
                    return 0;
                }
                break;

            case 9:
                if(orderItems[i].getQuantity() > desserts[foodIndex].getLimit() || orderItems[i].getQuantity() > desserts[foodIndex].getStock()){
                    return 0;
                }
                break;

            case 10:
                if(orderItems[i].getQuantity() > cakes[foodIndex].getLimit() || orderItems[i].getQuantity() > cakes[foodIndex].getStock()){
                    return 0;
                }
                break;

            case 11:
                if(orderItems[i].getQuantity() > beverages[foodIndex].getLimit() || orderItems[i].getQuantity() > beverages[foodIndex].getStock()){
                    return 0;
                }
                break;
            
            default:
                break;
            }
        }
        _order.setIsApproved(true);
        changeStock(orderItems);
        tm _time = newTime1();
        _order.setOrderTime(_time);
        ordersCompleted++;
        if(freeDelivery == true && _order.getBill() <= minimumOrder){
            restRevenue += (_order.getBill() * 0.9);
            adminFee += (_order.getBill() * 0.1);
            _order.setDeliveryCharges(0);
            restOrders.push_back(_order);
            return (_order.getBill());
        } else{
            restRevenue += (_order.getBill() * 0.9);
            adminFee += ((_order.getBill() * 0.1) + deliveryCharges);
            _order.setDeliveryCharges(deliveryCharges);
            restOrders.push_back(_order);
            return (_order.getBill() + deliveryCharges);
        }
    }

// returns the max number of a particular cuisine that can be ordered by the customer     
    int getLimit(int _cuisine, int _index){
        switch (_cuisine){
        case 0:
            return pizzas[_index].getLimit();
            break;
        
        case 1:
            return burgers[_index].getLimit();
            break;
        
        case 2:
            return sandwiches[_index].getLimit();
            break;

        case 3:
            return fastfoods[_index].getLimit();
            break;

        case 4:
            return barbqs[_index].getLimit();
            break;

        case 5:
            return pakistanis[_index].getLimit();
            break;

        case 6:
            return chineses[_index].getLimit();
            break;

        case 7:
            return internationals[_index].getLimit();
            break;

        case 8:
            return seafoods[_index].getLimit();
            break;

        case 9:
            return desserts[_index].getLimit();
            break;

        case 10:
            return cakes[_index].getLimit();
            break;

        case 11:
            return beverages[_index].getLimit();
            break;
        
        default:
            break;
        }
    }

// returns the complete stock of a particular stock
    int getStock(int _cuisine, int _index){
        switch (_cuisine){
        case 0:
            return pizzas[_index].getStock();
            break;
        
        case 1:
            return burgers[_index].getStock();
            break;
        
        case 2:
            return sandwiches[_index].getStock();
            break;

        case 3:
            return fastfoods[_index].getStock();
            break;

        case 4:
            return barbqs[_index].getStock();
            break;

        case 5:
            return pakistanis[_index].getStock();
            break;

        case 6:
            return chineses[_index].getStock();
            break;

        case 7:
            return internationals[_index].getStock();
            break;

        case 8:
            return seafoods[_index].getStock();
            break;

        case 9:
            return desserts[_index].getStock();
            break;

        case 10:
            return cakes[_index].getStock();
            break;

        case 11:
            return beverages[_index].getStock();
            break;
        
        default:
            break;
        }
    }

// Shows All Orders does not how ordered items details
    void showAllOrders(){
        int titleSize[9] = {13, 15, 13, 15, 12, 12, 6, 10, 15};
        cout << "\t" << char(218);
        for(int i = 0; i < 9; i++){
            cout << string(titleSize[i], char(196)) << char(194);
        }
        cout << "\b" << char(191) << "\n\t" << char(179) << setw(titleSize[0]) << "ORDER NUMBER " << char(179) << setw(titleSize[1]) << "ITEMS ORDERED " << char(179) << setw(titleSize[2]) << "TOTAL PRICE " << char(179) << setw(titleSize[3]) << "DELIVERY TIME " << char(179) << setw(titleSize[4]) << "ORDER DATE" << char(179) << setw(titleSize[5]) << "ORDER TIME " << char(179) << setw(titleSize[6]) << "PAID " << char(179) << setw(titleSize[7]) << "APPROVED " << char(179) << setw(titleSize[8]) << "CUSTOMER CODE " << char(179) << "\n\t" << char(195);
        for(int i = 0; i < 9; i++){
            cout << string(titleSize[i], char(196)) << char(197);
        }
        cout << "\b" << char(180);
        for(int i = 0; i < restOrders.size(); i++){
            restOrders[i].showOrderDetails('R');
            if((i % 32) == 0 && i != 0 && i != (restOrders.size() - 1)){
                cout << "\n\t" << char(192);
                for(int i = 0; i < 10; i++){
                    cout << string(titleSize[i], char(196)) << char(193);
                }
                cout << "\b" << char(217) << endl;
                setMessage("More....");
                setContinue();
                cleanArea(2, 10, 143, 44);
                gotoxy(2, 9);
            }
        }
        cout << "\n\t" << char(192);
        for(int i = 0; i < 9; i++){
            cout << string(titleSize[i], char(196)) << char(193);
        }
        cout << "\b" << char(217);
    }

// Shows Details of a particular order based on order Number for all food items
    void showOrder(string _orderNumber){
        int titleSize[9] = {13, 15, 13, 15, 12, 12, 6, 10, 15};
        cout << "\t" << char(218);
        for(int i = 0; i < 9; i++){
            cout << string(titleSize[i], char(196)) << char(194);
        }
        cout << "\b" << char(191) << "\n\t" << char(179) << setw(titleSize[0]) << "ORDER NUMBER " << char(179) << setw(titleSize[1]) << "ITEMS ORDERED " << char(179) << setw(titleSize[2]) << "TOTAL PRICE " << char(179) << setw(titleSize[3]) << "DELIVERY TIME " << char(179) << setw(titleSize[4]) << "ORDER DATE" << char(179) << setw(titleSize[5]) << "ORDER TIME " << char(179) << setw(titleSize[6]) << "PAID " << char(179) << setw(titleSize[7]) << "APPROVED " << char(179) << setw(titleSize[8]) << "CUSTOMER CODE " << char(179) << "\n\t" << char(195);
        for(int i = 0; i < 9; i++){
            cout << string(titleSize[i], char(196)) << char(197);
        }
        cout << "\b" << char(180);
        for(int i = 0; i < restOrders.size(); i++){
            if(restOrders[i].getOrderNumber() == _orderNumber){
                restOrders[i].showOrderDetails('R');
                cout << "\n\t" << char(192);
                for(int j = 0; j < 9; j++){
                    cout << string(titleSize[j], char(196)) << char(193);
                }
                cout << "\b" << char(217) << endl;
                restOrders[i].showOrder();
            }
        }
    }

// Deletes last order in order vector
    void deleteLastOrder(){
        restOrders.pop_back();
        ordersCancelled--;
    }
};


class CUSTOMER{
    string firstName;
    string lastName;
    string customerCode; // 0000 - ####
    string custPassword;
    string emailAddress;
    string custContactNumber;
    string custAddress;
    bool isActive; 
    int custArea;
    int custCity;
    double walletAmount;
    vector<ORDER> custOrders;
    vector<string> vouchers;
    vector<string> pastVouchers;

public:
    CUSTOMER(string _firstName, string _lastName, string _passWord, string _emailAddress, string _contactNumber, string _address, int _area, int _city){
        firstName = _firstName;
        lastName = _lastName;
        custPassword = _passWord;
        emailAddress = _emailAddress;
        custContactNumber = _contactNumber;
        custAddress = _address;
        custArea = _area;
        custCity = _city;
        walletAmount = 1000;
        isActive = true;
    }

    CUSTOMER(){}

// setter  functions
    void setFirstName(string _first){
        firstName = _first;
    }
    void setLastName(string _last){
        lastName = _last;
    }
    void setCustomerCode(string _code){
        customerCode = _code;
    }
    void setCustPassword(string _password){
        custPassword = _password;
    }
    void setEmailAddress(string _emailAddress){
        emailAddress = _emailAddress;
    }
    void setCustContactNumber(string _contactNumber){
        custContactNumber = _contactNumber;
    }
    void setCustAddress(string _address){
        custAddress = _address;
    }
    void setCustArea(int _area){
        custArea = _area;
    }
    void setCustCity(int _city){
        custCity = _city;
    }
    void setWalletAmount(double _walletAmount){
        walletAmount = _walletAmount;
    }
    void setVoucher(string _voucher){
        vouchers.push_back(_voucher);
    }
    void setIsActive(bool _isActive){
        isActive = _isActive;
    }

// getter functions
    string getFirstName(){return firstName;}
    string getLastName(){return lastName;}
    string getCustomerCode(){return customerCode;}
    string getCustPassword(){return custPassword;}
    string getEmailAddress(){return emailAddress;}
    string getContactNumber(){return custContactNumber;} 
    string getAddress(){return custAddress;}
    int getAreaInt(){return custArea;}
    int getCityInt(){return custCity;}
    string getCity(){return cities[custCity][0];}
    string getArea(){return cities[custCity][custArea];}
    double getWalletAmount(){return walletAmount;}
    string getVoucherUsed(int _index){return pastVouchers[_index];}
    string getVoucher(int _index){return vouchers[_index];}
    vector<string> getVoucherUsed(){return pastVouchers;}
    vector<string> getVoucher(){return vouchers;}
    bool getIsActive(){return isActive;}
    int getOrderSize(){return custOrders.size();}

// Adds new voucher
    void addVoucher(string _voucher){
        vouchers.push_back(_voucher);
    }

// Recharges Wallet using vouchers sent by admin
    string chargeWallet(int _value, string _vCode){
        if(_value > 0){
            walletAmount += _value;
            for(int i = 0; i < vouchers.size(); i++){
                if(vouchers[i] == _vCode){
                    pastVouchers.push_back(vouchers[i]);
                    vouchers.erase(vouchers.begin() + i);
                    break;
                }
            }
            return ("Wallet ReCharge Successful! Amount is " + to_string(_value));
        } else if(_value < 0){
            return "Wallet ReCharge Unsuccessful! Voucher Expired!";
        } else{
            return "Wallet ReCharge Unsuccessful! Voucher Invalid!";
        }
    }


// For the customer to pay the order
    string payOrder(double _value){
        //walletAmount -= _value;
        if(_value > 0){
            if(_value > walletAmount){
                custOrders.pop_back();
                return "Insufficient Funds to Pay Delivery Charges!";
            } else if(_value <= walletAmount){
                tm _time = newTime1();
                custOrders[custOrders.size()-1].setIsApproved(true);
                custOrders[custOrders.size()-1].setOrderTime(_time);
                custOrders[custOrders.size() - 1].setDeliveryCharges(_value - custOrders[custOrders.size() - 1].getBill());
                walletAmount -= _value;
                return "Order Completed Successfully!";
            }
        } else if(_value == 0){
            custOrders.pop_back();
            //custOrders[custOrders.size()-1].setIsPaid(false);
            return "Insufficient Stock/Limit ";
        } else{
            return "Something went wrong!";
        }
    }

// Create Order Number
    string createOrderNumber(){
        if(custOrders.size() < 10){
            return ("00" + to_string(custOrders.size()));
        }else if(custOrders.size() < 100){
            return ("0" + to_string(custOrders.size()));
        }else{
            return to_string(custOrders.size());
        }
    }

// sets Order number using restaurant, customer and order code
    void addOrder(ORDER _order, string _restCode){
        _order.setOrderNumber(_restCode + customerCode + createOrderNumber());
        custOrders.push_back(_order);
    }

// Pointer functions that points to the last Order in order vector
    ORDER * getNewOrder(){
        return &custOrders[(custOrders.size() - 1)];
    }

    void deleteLastOrder(){
        custOrders.pop_back();
    }

// shows customer details 
    void showDetails(){
        cout << "\tName:\t\t\t" << firstName + " " + lastName << "\n\n\tCustomer Code:\t\t" << customerCode << string(45-customerCode.size(), ' ') << "Email Address:\t" << emailAddress << "\n\n\tContact Number:\t\t" << custContactNumber << string(45-custContactNumber.size(), ' ') << "Address:\t\t" << custAddress << "\n\n\tArea:\t\t\t" << cities[custCity][custArea] << string(45-cities[custCity][custArea].length(), ' ') << "City\t\t" << cities[custCity][0] << "\n\n\tActive:\t\t\t" << setw(5) << isActive << string(45-5, ' ') << "Wallet Amount:\t" << walletAmount << "\n\n\tUnused Vouchers:\t" << vouchers.size() << string(45-to_string(vouchers.size()).length(), ' ') << "Used Vouchers:\t" << pastVouchers.size() << "\n\n\tOrders Placed\t\t" << custOrders.size() << "\n\n\tLAST ORDER\n";
        if(custOrders.size() > 0){
            custOrders[custOrders.size()-1].showOrder();
        } else{
            cout << "\t\t No Order Found!";
        }
    }

// Displays all orders
    void showAllOrders(){
        int titleSize[9] = {13, 15, 13, 15, 12, 12, 6, 10, 17};
        cout << "\t" << char(218);
        for(int i = 0; i < 9; i++){
            cout << string(titleSize[i], char(196)) << char(194);
        }
        cout << "\b" << char(191) << "\n\t" << char(179) << setw(titleSize[0]) << "ORDER NUMBER " << char(179) << setw(titleSize[1]) << "ITEMS ORDERED " << char(179) << setw(titleSize[2]) << "TOTAL PRICE " << char(179) << setw(titleSize[3]) << "DELIVERY TIME " << char(179) << setw(titleSize[4]) << "ORDER DATE" << char(179) << setw(titleSize[5]) << "ORDER TIME " << char(179) << setw(titleSize[6]) << "PAID " << char(179) << setw(titleSize[7]) << "APPROVED " << char(179) << setw(titleSize[8]) << "RESTAURANT CODE " << char(179) << "\n\t" << char(195);
        for(int i = 0; i < 9; i++){
            cout << string(titleSize[i], char(196)) << char(197);
        }
        cout << "\b" << char(180);
        for(int i = 0; i < custOrders.size(); i++){
            custOrders[i].showOrderDetails('C');
            if((i % 32) == 0 && i != 0 && i != (custOrders.size() - 1)){
                cout << "\n\t" << char(192);
                for(int i = 0; i < 10; i++){
                    cout << string(titleSize[i], char(196)) << char(193);
                }
                cout << "\b" << char(217) << endl;
                setMessage("More....");
                setContinue();
                cleanArea(2, 10, 143, 44);
                gotoxy(2, 9);
            }
        }
        cout << "\n\t" << char(192);
        for(int i = 0; i < 9; i++){
            cout << string(titleSize[i], char(196)) << char(193);
        }
        cout << "\b" << char(217);
    }

// Show order for a single order and all its orderItems
    void showOrder(string _orderNumber){
        int titleSize[9] = {13, 15, 13, 15, 12, 12, 6, 10, 17};
        cout << "\t" << char(218);
        for(int i = 0; i < 9; i++){
            cout << string(titleSize[i], char(196)) << char(194);
        }
        cout << "\b" << char(191) << "\n\t" << char(179) << setw(titleSize[0]) << "ORDER NUMBER " << char(179) << setw(titleSize[1]) << "ITEMS ORDERED " << char(179) << setw(titleSize[2]) << "TOTAL PRICE " << char(179) << setw(titleSize[3]) << "DELIVERY TIME " << char(179) << setw(titleSize[4]) << "ORDER DATE" << char(179) << setw(titleSize[5]) << "ORDER TIME " << char(179) << setw(titleSize[6]) << "PAID " << char(179) << setw(titleSize[7]) << "APPROVED " << char(179) << setw(titleSize[8]) << "RESTAURANT CODE " << char(179) << "\n\t" << char(195);
        for(int i = 0; i < 9; i++){
            cout << string(titleSize[i], char(196)) << char(197);
        }
        cout << "\b" << char(180);
        for(int i = 0; i < custOrders.size(); i++){
            if(custOrders[i].getOrderNumber() == _orderNumber){
                custOrders[i].showOrderDetails('C');
                cout << "\n\t" << char(192);
                for(int j = 0; j < 9; j++){
                    cout << string(titleSize[j], char(196)) << char(193);
                }
                cout << "\b" << char(217) << endl;
                custOrders[i].showOrder();
            }
        }
    }
};


// Administrator Class is basically food panda class
class ADMINISTRATOR{
    const string userName;
    const string passWord;
    static double revenue;
    double tax;
    vector<string> vouchers;
    vector<RESTAURANT> restaurants;
    vector<CUSTOMER> customers;
    map <string, string> managerLink;
    map <string, string> custEmailLink; //(Email >> Code)
    map <string, string> custContactLink; //(Contact >> Email)
    map <string, double> voucherValueLink;

public:
    ADMINISTRATOR(string _userName, string _passWord) : userName(_userName), passWord(_passWord){
        revenue = 0;
        tax = 0;
    }

// Getter Function
    string getUserName(){return userName;}
    string getPassWord(){return passWord;}
    int getRestaurantSize(){return restaurants.size();}
    int getCustomerSize(){return customers.size();}
    string getRestPassword(int _index){return restaurants[_index].getManagerPassword();}

// Receives Revenue from Restaurants (10% + delivery charges)
    string static receiveRevenue(){
        double _amount = RESTAURANT::getAdminFee();
        if(_amount > 0){
            revenue += _amount;
            return "Admin Received " + to_string(_amount);
        } else if(_amount == 0){
            return "Restaurants have not generated any Revenue!";
        } else{
            return "Something is Wrong with Restaurant revenue";
        }
    }
    
    void setRestPassword(int _index, string _password){
        restaurants[_index].setManagerPassword(_password);
    }

    bool getRestStatus(int i){return restaurants[i].getIsRestOpen();}

// restaurant pointer which points to a particular restaurant based on index
    RESTAURANT * getRestaurant(int _index){return &restaurants[_index];}

// Customer pointer which points to a particular customer based on index
    CUSTOMER * getCustomer(int _index){return &customers[_index];}

// Checks whether Manager exist, suspended or does not exist 
    int checkManager(string _managerID){
        if(managerLink[_managerID].length() == 0){
            return -1;
        }else{
            if(managerLink[_managerID] == "000"){
                setMessage("Following Manager account is suspended!");
            }else{
                setMessage("Manager ID found!");
            }
            return stoi(managerLink[_managerID]);
        }
    }

// Checks Customer using email and contact Number for New User and Modifying
    int checkCustomer(string _email, string _contactNumber){
        if((custEmailLink[_email].length() == 0) && (custContactLink[_contactNumber].length() == 0)){
            return -1;
        } else if(custEmailLink[_email].length() == 0){
            setMessage("Contact Number " + _contactNumber + " is linked with another Email Address!");
        } else if(custContactLink[_contactNumber].length() == 0){
            setMessage("Email Address " + _email + " is linked with another Account!");
        } else{
            if(custEmailLink[_email] == "0000"){
                setMessage("Following Customer account is suspended!");
            }else{
                setMessage("Following Customer already own an Account!");
            }
            return stoi(custEmailLink[_email]);
        }
    }

// For sign In
    int checkCustomer(string _emailContact){
        if(custEmailLink[_emailContact].length() > 0){
            if(custEmailLink[_emailContact] != "0000"){
                return stoi(custEmailLink[_emailContact]);
            } else{
                return 0;
            }
        } else{
            if(custContactLink[_emailContact].length() > 0){
                if(custEmailLink[custContactLink[_emailContact]].length() > 0){
                    if(custEmailLink[custContactLink[_emailContact]] != "0000"){
                        return stoi(custEmailLink[custContactLink[_emailContact]]);
                    } else{
                        return 0;
                    }
                } else{
                    return -1;
                }
            }
        }
    }

// Restaurant code self generated
    string createRestCode(int _code){
        if(_code < 10){
            return ("00" + to_string(_code));
        }else if(_code < 100){
            return ("0" + to_string(_code));
        }else{
            return to_string(_code);
        }
    }

// Customer Code self generated
    string createCustCode(int _code){
        if(_code < 10){
            return ("000" + to_string(_code));
        }else if(_code < 100){
            return ("00" + to_string(_code));
        }else if(_code < 1000){
            return ("0" + to_string(_code));
        }else{
            return to_string(_code);
        }
    }

// Verifying Password
    string getCustPassword(int _index){return customers[_index].getCustPassword();}

// Restaurant added setting code, and create a managerLink 
    void addRestaurant(RESTAURANT _restaurant){
        restaurants.push_back(_restaurant);
        restaurants[restaurants.size() - 1].setCode(createRestCode(restaurants.size()));
        managerLink[restaurants[restaurants.size() - 1].getManagerID()] = restaurants[restaurants.size() - 1].getCode();
    }

// returns Restaurant index using managerID
    int searchRestByMangerID(string _managerID){
        for(int i = 0; i < restaurants.size(); i++){
            if(restaurants[i].getManagerID() == _managerID){
                return i;
            }else{
                if(i == (restaurants.size() - 1)){
                    return -1;
                }
                continue;
            }
        }
    }

// Remove restaurant by setting code to "000"
    string removeRestaurant(string _managerID){
        if(managerLink[_managerID] == "000"){
            return "Restaurant is already removed!";
        }else if(managerLink[_managerID].length() == 0){
            return "Restaurant does not exist!";
        }else{
            restaurants[stoi(managerLink[_managerID]) - 1].setIsRestActive(false);
            restaurants[stoi(managerLink[_managerID]) - 1].setIsRestOpen(false);
            managerLink[_managerID] = "000";
            return "Restaurant has been removed!";
        }
    }

// Restaurant is reopened by setting the code from restaurant vector and Activating restaurant 
    string reOpenRestaurant(string _managerID){
        if(managerLink[_managerID].length() == 0){
            return "Restaurant does not exist!";
        }else if(managerLink[_managerID] == "000"){
            int restIndex = searchRestByMangerID(_managerID);
            if(restIndex == -1){
                return "Restaurant does not exist!";
            }else{
                managerLink[_managerID] = restaurants[restIndex].getCode();
                restaurants[restIndex].setIsRestActive(true);
                return "Restaurant has been Re-Opened!";
            }
        } else{
            return "Restaurant is already Active!";
        }
    }

// Shows All Restaurants
    void showRestaurants(){
        int title[16] = {5, 16, 25, 10, 10, 12, 12, 6, 1, 1, 1, 1, 1, 1, 1, 8};
        cout << "\t" << char(218);
        for(int i = 0; i < 16; i++){
            cout << string(title[i], char(196)) << char(194);
        }
        cout << "\b" << char(191) << "\n\t" << char(179) << setw(title[0]) << "CODE " << char(179) << setw(title[1]) << "MANAGER ID " << char(179) << setw(title[2]) << "TITLE " << char(179) << setw(title[3]) << "CITY " << char(179) << setw(title[4]) << "AREA " << char(179) << setw(title[5]) << "INCOME " << char(179) << setw(title[6]) << "TAX " << char(179) << setw(title[7]) << "ACTIVE" << char(179) << setw(title[8]) << "S" << char(179) << setw(title[9]) << "M" << char(179) << setw(title[10]) << "T" << char(179) << setw(title[11]) << "W" << char(179) << setw(title[12]) << "T" << char(179) << setw(title[13]) << "F" << char(179) << setw(title[14]) << "S" << char(179) << setw(title[15]) << "TIMINGS" << char(179);
        cout << "\n\t" << char(195);
        for(int i = 0; i < 16; i++){
            cout << string(title[i], char(196)) << char(197);
        }
        cout << "\b" << char(180);
        for(int j = 0; j < restaurants.size(); j++){
            cout << "\n\t" << char(179) << setw(title[0]) << restaurants[j].getCode() << char(179) << setw(title[1]) << restaurants[j].getManagerID() << char(179) << setw(title[2]) << restaurants[j].getTitle() << char(179) << setw(title[3]) << restaurants[j].getCity() << char(179) << setw(title[4]) << restaurants[j].getArea() << char(179) << setw(title[5]) << restaurants[j].getRestRevenue() << char(179) << setw(title[6]) << restaurants[j].getRestTax() << char(179) << setw(title[7]) << restaurants[j].getIsRestActive() << char(179);
            for(int k = 0; k < 7; k++){
                if(restaurants[j].getDaysOpen(k) == true){
                    cout << char(254) << char(179);
                } else{
                    cout << " " << char(179);
                }
            }
            cout << setw(title[15]) << restaurants[j].getTime() << char(179);
            if((j % 32) == 0 && j != 0 && j != (restaurants.size() - 1)){
                cout << "\n\t" << char(192);
                for(int i = 0; i < 10; i++){
                    cout << string(title[i], char(196)) << char(193);
                }
                cout << "\b" << char(217) << endl;
                setMessage("More....");
                setContinue();
                cleanArea(2, 10, 143, 44);
                gotoxy(2, 9);
            }
        }
        cout << "\n\t" << char(192);
        for(int i = 0; i < 16; i++){
            cout << string(title[i], char(196)) << char(193);
        }
        cout << "\b" << char(217) << endl;
    }

// Searching Restaurants using Title as substring
    void showRestaurants(string _title){
        int recordCount = 0;
        int title[16] = {5, 16, 25, 10, 10, 12, 12, 6, 1, 1, 1, 1, 1, 1, 1, 8};
        cout << "\t" << char(218);
        for(int i = 0; i < 16; i++){
            cout << string(title[i], char(196)) << char(194);
        }
        cout << "\b" << char(191) << "\n\t" << char(179) << setw(title[0]) << "CODE " << char(179) << setw(title[1]) << "MANAGER ID " << char(179) << setw(title[2]) << "TITLE " << char(179) << setw(title[3]) << "CITY " << char(179) << setw(title[4]) << "AREA " << char(179) << setw(title[5]) << "INCOME " << char(179) << setw(title[6]) << "TAX " << char(179) << setw(title[7]) << "ACTIVE" << char(179) << setw(title[8]) << "S" << char(179) << setw(title[9]) << "M" << char(179) << setw(title[10]) << "T" << char(179) << setw(title[11]) << "W" << char(179) << setw(title[12]) << "T" << char(179) << setw(title[13]) << "F" << char(179) << setw(title[14]) << "S" << char(179) << setw(title[15]) << "TIMINGS" << char(179);
        cout << "\n\t" << char(195);
        for(int i = 0; i < 16; i++){
            cout << string(title[i], char(196)) << char(197);
        }
        cout << "\b" << char(180);

        for(int j = 0; j < restaurants.size(); j++){
            if(restaurants[j].getTitle().length() >= _title.length()){
                for(int i = 0; i <= (restaurants[j].getTitle().length() - _title.length()); i++){
                    if(restaurants[j].getTitle().substr(i, _title.length()) == _title){
                        cout << "\n\t" << char(179) << setw(title[0]) << restaurants[j].getCode() << char(179) << setw(title[1]) << restaurants[j].getManagerID() << char(179) << setw(title[2]) << restaurants[j].getTitle() << char(179) << setw(title[3]) << restaurants[j].getCity() << char(179) << setw(title[4]) << restaurants[j].getArea() << char(179) << setw(title[5]) << restaurants[j].getRestRevenue() << char(179) << setw(title[6]) << restaurants[j].getRestTax() << char(179) << setw(title[7]) << restaurants[j].getIsRestActive() << char(179);
                        for(int k = 0; k < 7; k++){
                            if(restaurants[j].getDaysOpen(k) == true){
                                cout << char(254) << char(179);
                            } else{
                                cout << " " << char(179);
                            }
                        }
                        cout << setw(title[15]) << restaurants[j].getTime() << char(179);
                        recordCount++;
                        if((recordCount % 32) == 0 && recordCount != 0){
                            cout << "\n\t" << char(192);
                            for(int i = 0; i < 10; i++){
                                cout << string(title[i], char(196)) << char(193);
                            }
                            cout << "\b" << char(217) << endl;
                            setMessage("More....");
                            setContinue();
                            cleanArea(2, 10, 143, 44);
                            gotoxy(2, 9);
                        }
                    }
                }
            }
        }
        cout << "\n\t" << char(192);
        for(int i = 0; i < 16; i++){
            cout << string(title[i], char(196)) << char(193);
        }
        cout << "\b" << char(217) << endl;
        if(recordCount == 0){
            setMessage("Restaurants with Title \"" + _title + "\" Not Found! ");
        } else{
            setMessage(to_string(recordCount) + " Restaurants Found with Title \"" + _title + "\" ");
        }
    }

// shows Restaurant using code 
    void showRestaurants(int i){
        gotoxy(2, 7);
        cout << "\tTitle:\t\t\t" << restaurants[i].getTitle() << "\n\n\tDescription:\t\t" << restaurants[i].getDescription().substr(0, 100) << "\n\n\tManager ID:\t\t" << restaurants[i].getManagerID() << setw(70-getX()) << "\t" << "Code:\t\t\t" << restaurants[i].getCode()  << "\n\n\tContact Number:\t\t" << restaurants[i].getContactNumber() << setw(70-getX()) << "\t" << "Address:\t\t" << restaurants[i].getAddress() << "\n\n\tArea:\t\t\t" << restaurants[i].getArea() << setw(70-getX()) << "\t" << "City:\t\t\t" << restaurants[i].getCity() << "\n\n\tActive:\t\t\t" << restaurants[i].getIsRestActive() << setw(70-getX()) << "\t" << "Open:\t\t\t" << restaurants[i].getIsRestOpen() << "\n\n\tFree Delivery:\t\t" << restaurants[i].getFreeDelivery() << setw(70-getX()) << "\t" << "Minimum Order:\t\t" << restaurants[i].getMinimumOrder() << "\n\n\tDelivery Charges:\t" << restaurants[i].getDeliveryCharges() << setw(70-getX()) << "\t" << "Discount:\t\t" << restaurants[i].getRestDiscount() << "%\n\n\tTotal Income:\t\t" << restaurants[i].getRestRevenue() << setw(70-getX()) << "\t" << "Tax:\t\t\t" << restaurants[i].getRestTax() << "\n\n\tOrders Pending:\t\t" << restaurants[i].getOrdersPending() << setw(70-getX()) << "\t" << "Orders Completed:\t" << restaurants[i].getOrdersCompleted() << "\n\n\tOrders Cancelled:\t" << restaurants[i].getOrdersCancelled() << setw(70-getX()) << "\t" << "Timings:\t\t" << restaurants[i].getOpenTime() << " - " << restaurants[i].getCloseTime();
        gotoxy(66, (getY() + 2));
        cout << "WORKING DAYS\n\t\t\t\t\t" << char(218);
        for(int i = 0; i < days.size(); i++){
            cout << string(days[i].length(), char(196)) << char(194);
        }
        cout << "\b" << char(191) << "\n\t\t\t\t\t" << char(179);
        for(int i = 0; i < days.size(); i++){
            cout << days[i] << char(179);
        }
        cout << "\n\t\t\t\t\t" << char(195);
        for(int i = 0; i < days.size(); i++){
            cout << string(days[i].length(), char(196)) << char(197);
        }
        cout << "\b" << char(180) << "\n\t\t\t\t\t" << char(179);
        for(int j = 0; j < days.size(); j++){
            if(restaurants[i].getDaysOpen(j) == true){cout << " YES" << string((days[j].length() - 4), ' ') << char(179);} else{
            cout << " NO" << string((days[j].length() - 3), ' ') << char(179);}
        }
        cout << "\n\t\t\t\t\t" << char(192);
        for(int i = 0; i < days.size(); i++){
            cout << string(days[i].length(), char(196)) << char(193);
        }
        cout << "\b" << char(217);
        
        gotoxy(63, (getY() + 2));
        cout << "CUISINES AVAILABLE\n\t" << char(218);
        for(int i = 0; i < cuisineTitle.size(); i++){
            cout << string(cuisineTitle[i].length(), char(196)) << char(194);
        }
        cout << "\b" << char(191) << "\n\t" << char(179);
        for(int i = 0; i < cuisineTitle.size(); i++){
            cout << cuisineTitle[i] << char(179);
        }
        cout << "\n\t" << char(195);
        for(int i = 0; i < cuisineTitle.size(); i++){
            cout << string(cuisineTitle[i].length(), char(196)) << char(197);
        }
        cout << "\b" << char(180) << "\n\t" << char(179);

        for(int j = 0; j < cuisineTitle.size(); j++){
            if(restaurants[i].hasFood(cuisineTitle[j]) == true){cout << " YES" << string((cuisineTitle[j].length() - 4), ' ') << char(179);} else{
            cout << " NO" << string((cuisineTitle[j].length() - 3), ' ') << char(179);}
        }
        cout << "\n\t" << char(192);
        for(int i = 0; i < cuisineTitle.size(); i++){
            cout << string(cuisineTitle[i].length(), char(196)) << char(193);
        }
        cout << "\b" << char(217);
    }

// shows Restaurant with cuisine availabel
    void showRestWithCuisine(string _cuisine){
        int recordCount = 0;
        int title[16] = {5, 16, 25, 10, 10, 12, 12, 6, 1, 1, 1, 1, 1, 1, 1, 8};
        cout << "\t" << char(218);
        for(int i = 0; i < 16; i++){
            cout << string(title[i], char(196)) << char(194);
        }
        cout << "\b" << char(191) << "\n\t" << char(179) << setw(title[0]) << "CODE " << char(179) << setw(title[1]) << "MANAGER ID " << char(179) << setw(title[2]) << "TITLE " << char(179) << setw(title[3]) << "CITY " << char(179) << setw(title[4]) << "AREA " << char(179) << setw(title[5]) << "INCOME " << char(179) << setw(title[6]) << "TAX " << char(179) << setw(title[7]) << "ACTIVE" << char(179) << setw(title[8]) << "S" << char(179) << setw(title[9]) << "M" << char(179) << setw(title[10]) << "T" << char(179) << setw(title[11]) << "W" << char(179) << setw(title[12]) << "T" << char(179) << setw(title[13]) << "F" << char(179) << setw(title[14]) << "S" << char(179) << setw(title[15]) << "TIMINGS" << char(179);
        cout << "\n\t" << char(195);
        for(int i = 0; i < 16; i++){
            cout << string(title[i], char(196)) << char(197);
        }
        cout << "\b" << char(180);
        for(int j = 0; j < restaurants.size(); j++){
            if(restaurants[j].hasFood(_cuisine) == true){
                cout << "\n\t" << char(179) << setw(title[0]) << restaurants[j].getCode() << char(179) << setw(title[1]) << restaurants[j].getManagerID() << char(179) << setw(title[2]) << restaurants[j].getTitle() << char(179) << setw(title[3]) << restaurants[j].getCity() << char(179) << setw(title[4]) << restaurants[j].getArea() << char(179) << setw(title[5]) << restaurants[j].getRestRevenue() << char(179) << setw(title[6]) << restaurants[j].getRestTax() << char(179) << setw(title[7]) << restaurants[j].getIsRestActive() << char(179);
                for(int k = 0; k < 7; k++){
                    if(restaurants[j].getDaysOpen(k) == true){
                        cout << char(254) << char(179);
                    } else{
                        cout << " " << char(179);
                    }
                }
                cout << setw(title[15]) << restaurants[j].getTime() << char(179);
                recordCount++;
                if((recordCount % 32) == 0 && recordCount != 0){
                    cout << "\n\t" << char(192);
                    for(int i = 0; i < 10; i++){
                        cout << string(title[i], char(196)) << char(193);
                    }
                    cout << "\b" << char(217) << endl;
                    setMessage("More....");
                    setContinue();
                    cleanArea(2, 10, 143, 44);
                    gotoxy(2, 9);
                }
            }
        }
        cout << "\n\t" << char(192);
        for(int i = 0; i < 16; i++){
            cout << string(title[i], char(196)) << char(193);
        }
        cout << "\b" << char(217) << endl;
        if(recordCount == 0){
            setMessage("Restaurants with Cuisine \"" + _cuisine + "\" Not Found!");
        } else{
            setMessage(to_string(recordCount) + " Restaurants Found with Cuisine \"" + _cuisine + "\"");
        }
    }

// Show Restaurant with Location
    void showRestOnLocation(int _city, int _area){
        int recordCount = 0;
        int title[16] = {5, 16, 25, 10, 10, 12, 12, 6, 1, 1, 1, 1, 1, 1, 1, 8};
        setTitle("RESTAURANTS @ " + cities[_city][0] + ": " + cities[_city][_area]);
        gotoxy(2, 7);
        cout << "\n\t" << char(218);
        for(int i = 0; i < 16; i++){
            cout << string(title[i], char(196)) << char(194);
        }
        cout << "\b" << char(191) << "\n\t" << char(179) << setw(title[0]) << "CODE " << char(179) << setw(title[1]) << "MANAGER ID " << char(179) << setw(title[2]) << "TITLE " << char(179) << setw(title[3]) << "CITY " << char(179) << setw(title[4]) << "AREA " << char(179) << setw(title[5]) << "INCOME " << char(179) << setw(title[6]) << "TAX " << char(179) << setw(title[7]) << "ACTIVE" << char(179) << setw(title[8]) << "S" << char(179) << setw(title[9]) << "M" << char(179) << setw(title[10]) << "T" << char(179) << setw(title[11]) << "W" << char(179) << setw(title[12]) << "T" << char(179) << setw(title[13]) << "F" << char(179) << setw(title[14]) << "S" << char(179) << setw(title[15]) << "TIMINGS" << char(179);
        cout << "\n\t" << char(195);
        for(int i = 0; i < 16; i++){
            cout << string(title[i], char(196)) << char(197);
        }
        cout << "\b" << char(180);
        for(int j = 0; j < restaurants.size(); j++){
            if((restaurants[j].getCity() == cities[_city][0]) && (restaurants[j].getArea() == cities[_city][_area])){
                cout << "\n\t" << char(179) << setw(title[0]) << restaurants[j].getCode() << char(179) << setw(title[1]) << restaurants[j].getManagerID() << char(179) << setw(title[2]) << restaurants[j].getTitle() << char(179) << setw(title[3]) << restaurants[j].getCity() << char(179) << setw(title[4]) << restaurants[j].getArea() << char(179) << setw(title[5]) << restaurants[j].getRestRevenue() << char(179) << setw(title[6]) << restaurants[j].getRestTax() << char(179) << setw(title[7]) << restaurants[j].getIsRestActive() << char(179);
                for(int k = 0; k < 7; k++){
                    if(restaurants[j].getDaysOpen(k) == true){
                        cout << char(254) << char(179);
                    } else{
                        cout << " " << char(179);
                    }
                }
                cout << setw(title[15]) << restaurants[j].getTime() << char(179);
                recordCount++;
                if((recordCount % 32) == 0 && recordCount != 0){
                    cout << "\n\t" << char(192);
                    for(int i = 0; i < 10; i++){
                        cout << string(title[i], char(196)) << char(193);
                    }
                    cout << "\b" << char(217) << endl;
                    setMessage("More....");
                    setContinue();
                    cleanArea(2, 10, 143, 44);
                    gotoxy(2, 9);
                }
            }
        }
        cout << "\n\t" << char(192);
        for(int i = 0; i < 16; i++){
            cout << string(title[i], char(196)) << char(193);
        }
        cout << "\b" << char(217) << endl;
        if(recordCount == 0){
            setMessage("Restaurants @ " + cities[_city][0] + ": " + cities[_city][_area] + " Not Found!");
        } else{
            setMessage(to_string(recordCount) + " Restaurants Found @ " + cities[_city][0] + ": " + cities[_city][_area]);
        }
    }


// Find Manager with ManagerID
    void findRestWithManager(string _managerID){
        int i = -1;
        if(managerLink[_managerID].length() == 0){
            setMessage("No Restaurant found with ManagerID: " + _managerID);
        } else if(managerLink[_managerID] == "000"){
            setMessage("Restaurant is Permanently Closed");
            i = searchRestByMangerID(_managerID);
        } else{
            i = stoi(managerLink[_managerID]) - 1;
            setMessage("Restaurant Found!");
        }
        if(i >= 0){
            showRestaurants(i);
        }
    }

// Adding Vouchers by voucher code and its Value
    string addVoucher(string _voucher, double _value){
        if(_voucher.length() < 10){
            _voucher = string((10-_voucher.length()), '0') + _voucher;
        } else if(_voucher.length() > 10){
            _voucher = _voucher.substr(0, 10);
        }
        if(voucherValueLink[_voucher] == -1){
            return "Voucher Exists but Expired!";
        } else if(voucherValueLink[_voucher] > 0){
            return "Voucher already exists!";
        } else{
            vouchers.push_back(_voucher);
            voucherValueLink[_voucher] = _value;
            return "Voucher Added!";
        }
    }

// Blocks Voucher by turning value to 0
    string blockVoucher(string _voucher){
        if(voucherValueLink[_voucher] > 0){
            voucherValueLink[_voucher] = 0;
            return "Voucher Blocked!";
        } else if(voucherValueLink[_voucher] == -1){
            return "Voucher already Expired!";
        } else{
            return "Voucher Does not Exist";
        }
    }

// Sends Voucher to customer through customer Code and voucher code
    string sendVoucher(string _custCode, string _voucher){
        int custIndex;
        try{
            custIndex = (stoi(_custCode) - 1);
        } catch(exception& e){
            return "Invalid Voucher Code!";
        }
        if(custIndex < customers.size()){
            if(voucherValueLink[_voucher] > 0){
                customers[custIndex].addVoucher(_voucher);
                return ("Voucher sent to " + customers[custIndex].getCustomerCode());
            } else{
                return "Invalid Voucher Code!";
            }
        } else{
            return "Invalid Customer Code!";
        }
    }

// Returns Vouchers Value
    int cashVoucher(string _voucher){
        int amount = voucherValueLink[_voucher];
        voucherValueLink[_voucher] = -1;
        return amount;
    }

// Displays All Vouchers with their Status
    string showVouchers(){
        cout << "\t" << char(218) << string(10, char(196)) << char(194) << string(14, char(196)) << char(191) << "\n\t" << char(179) << setw(10) << "CODE" << char(179) << setw(14) << "STATUS/VALUE " << char(179);
        for(int i = 0; i < vouchers.size(); i++){
            cout << "\n\t" << char(195) << string(10, char(196)) << char(197) << string(14, char(196)) << char(180) << "\n\t" << char(179) << setw(10) << vouchers[i] << char(179);
            if(voucherValueLink[vouchers[i]] == -1){
                cout << setw(14) << "Expired ";
            } else if(voucherValueLink[vouchers[i]] == 0){
                cout << setw(14) << "Blocked ";
            } else{
                cout << setw(13) << voucherValueLink[vouchers[i]] << " ";
            }
            cout << char(179);
            if((i % 32) == 0 && i != 0 && i != (vouchers.size()-1)){
                cout << "\n\t" << char(192) << string(10, char(196)) << char(193) << string(14, char(196)) << char(217);
                setMessage("More....");
                setContinue();
                cleanArea(2, 10, 143, 44);
                gotoxy(2, 9);
            }
        }
        cout << "\n\t" << char(192) << string(10, char(196)) << char(193) << string(14, char(196)) << char(217);
        if(vouchers.size() > 0){
            return (to_string(vouchers.size()) + "Records Found!");
        } else{
            return "No Record Found of any Voucher";
        }
    }

// Displays Voucher using Voucher Code
    string showVouchers(string _code){
        int count = 0;
        cout << "\t" << char(218) << string(10, char(196)) << char(194) << string(14, char(196)) << char(191) << "\n\t" << char(179) << setw(10) << "CODE" << char(179) << setw(14) << "STATUS/VALUE " << char(179);
        for(int i = 0; i < vouchers.size(); i++){
            if(vouchers[i] == _code){
                cout << "\n\t" << char(195) << string(10, char(196)) << char(197) << string(14, char(196)) << char(180) << "\n\t" << char(179) << setw(10) << vouchers[i] << char(179);
                if(voucherValueLink[vouchers[i]] == -1){
                    cout << setw(14) << "Expired ";
                } else if(voucherValueLink[vouchers[i]] == 0){
                    cout << setw(14) << "Blocked ";
                } else{
                    cout << setw(13) << voucherValueLink[vouchers[i]] << " ";
                }
                cout << char(179);
                count++;
                if((count % 32) == 0 && count != 0){
                    cout << "\n\t" << char(192) << string(10, char(196)) << char(193) << string(14, char(196)) << char(217);
                    setMessage("More....");
                    setContinue();
                    cleanArea(2, 10, 143, 44);
                    gotoxy(2, 9);
                }
            }
        }
        cout << "\n\t" << char(192) << string(10, char(196)) << char(193) << string(14, char(196)) << char(217);
        if(count > 0){
            return (to_string(count) + "Records Found!");
        } else{
            return ("No Record Found of any Voucher with Code: " + _code);
        }
    }

// Shows Customer all Vouchers
    void showVouchersCust(vector<string> _vouchers){
        cout << "\t" << char(218) << string(10, char(196)) << char(194) << string(14, char(196)) << char(191) << "\n\t" << char(179) << setw(10) << "CODE" << char(179) << setw(14) << "STATUS/VALUE " << char(179);
        for(int i = 0; i < _vouchers.size(); i++){
            cout << "\n\t" << char(195) << string(10, char(196)) << char(197) << string(14, char(196)) << char(180) << "\n\t" << char(179) << setw(10) << _vouchers[i] << char(179);
            if(voucherValueLink[_vouchers[i]] == -1){
                cout << setw(14) << "Expired ";
            } else if(voucherValueLink[_vouchers[i]] == 0){
                cout << setw(14) << "Blocked ";
            } else{
                cout << setw(13) << voucherValueLink[_vouchers[i]] << " ";
            }
            cout << char(179);
            if((i % 32) == 0 && i != 0 && i != (_vouchers.size() - 1)){
                cout << "\n\t" << char(192) << string(10, char(196)) << char(193) << string(14, char(196)) << char(217);
                setMessage("More....");
                setContinue();
                cleanArea(2, 10, 143, 44);
                gotoxy(2, 9);
            }
        }
        cout << "\n\t" << char(192) << string(10, char(196)) << char(193) << string(14, char(196)) << char(217);
    }

// Show Vouchers choice = (Blocked,Expired,Unused)
    string showVouchers(int _choice){
        int count = 0;
        cout << "\t" << char(218) << string(10, char(196)) << char(194) << string(14, char(196)) << char(191) << "\n\t" << char(179) << setw(10) << "CODE" << char(179) << setw(14) << "STATUS/VALUE " << char(179);
        for(int i = 0; i < vouchers.size(); i++){
            if(_choice == 1){
                if(voucherValueLink[vouchers[i]] > 0){
                    cout << "\n\t" << char(195) << string(10, char(196)) << char(197) << string(14, char(196)) << char(180) << "\n\t" << char(179) << setw(10) << vouchers[i] << char(179);
                    if(voucherValueLink[vouchers[i]] == -1){
                        cout << setw(14) << "Expired ";
                    } else if(voucherValueLink[vouchers[i]] == 0){
                        cout << setw(14) << "Blocked ";
                    } else{
                        cout << setw(13) << voucherValueLink[vouchers[i]] << " ";
                    }
                    cout << char(179);
                    count++;
                    if((count % 32) == 0 && count != 0){
                        cout << "\n\t" << char(192) << string(10, char(196)) << char(193) << string(14, char(196)) << char(217);
                        setMessage("More....");
                        setContinue();
                        cleanArea(2, 10, 143, 44);
                        gotoxy(2, 9);
                    }
                }
            } else{
                if(voucherValueLink[vouchers[i]] == _choice){
                    cout << "\n\t" << char(195) << string(10, char(196)) << char(197) << string(14, char(196)) << char(180) << "\n\t" << char(179) << setw(10) << vouchers[i] << char(179);
                    if(voucherValueLink[vouchers[i]] == -1){
                        cout << setw(14) << "Expired ";
                    } else if(voucherValueLink[vouchers[i]] == 0){
                        cout << setw(14) << "Blocked ";
                    } else{
                        cout << setw(13) << voucherValueLink[vouchers[i]] << " ";
                    }
                    cout << char(179);
                    count++;
                    if((count % 32) == 0 && count != 0){
                        cout << "\n\t" << char(192) << string(10, char(196)) << char(193) << string(14, char(196)) << char(217);
                        setMessage("More....");
                        setContinue();
                        cleanArea(2, 10, 143, 44);
                        gotoxy(2, 9);
                    }
                }
            }
        }
        cout << "\n\t" << char(192) << string(10, char(196)) << char(193) << string(14, char(196)) << char(217);
        if(count > 0){
            return (to_string(count) + "Records Found!");
        } else{
            return "No Record Found!";
        }
    }

// sets and add Customer code, emaillink, and contact Number 
    void addCustomer(CUSTOMER _customer){
        customers.push_back(_customer);
        customers[customers.size()-1].setCustomerCode(createCustCode(customers.size()));
        custEmailLink[customers[customers.size()-1].getEmailAddress()] = customers[customers.size()-1].getCustomerCode();
        custContactLink[customers[customers.size()-1].getContactNumber()] = customers[customers.size()-1].getEmailAddress();
    }

// Blocks Customer by turning Email to "0000"
    string removeCustomer(string _emailAddress){
        if(custEmailLink[_emailAddress] == "0000"){
            return "Customer is already removed!";
        }else if(custEmailLink[_emailAddress].length() == 0){
            return "Customer does not exist";
        }else{
            customers[stoi(custEmailLink[_emailAddress]) - 1].setIsActive(false);
            custEmailLink[_emailAddress] = "0000";
            return "Customer has been removed";
        }
    }

// Returns Index of a customer having the specific Email
    int searchCustByEmail(string _emailAddress){
        for(int i = 0; i < customers.size(); i++){
            if(customers[i].getEmailAddress() == _emailAddress){
                return i;
            }else{
                if(i == (customers.size() - 1)){
                    return -1;
                }
                continue;
            }
        }
    }

// Activates Customer by setting up code of customer
    string activateCustomer(string _emailAddress){
        if(custEmailLink[_emailAddress].length() == 0){
            return "Customer does not exist";
        }else if(custEmailLink[_emailAddress] == "0000"){
            int restIndex = searchCustByEmail(_emailAddress);
            if(restIndex == -1){
                return "Customer does not exist!";
            }else{
                custEmailLink[_emailAddress] = customers[restIndex].getCustomerCode();
                customers[restIndex].setIsActive(true);
                return "Customer has been Activated!";
            }
        } else{
            return "Customer is already Active!";
        }
    }

// Changes Customer Email by swapping the old and new Email Address and emptying old email
    string changeCustEmail(int _index, string _email){
        if(custEmailLink[_email].length() == 0){
            swap(custEmailLink[customers[_index].getEmailAddress()], custEmailLink[_email]);
            custContactLink[customers[_index].getContactNumber()] = _email;
            customers[_index].setEmailAddress(_email);
            return "Email Change Successful!";
        } else{
            return "Email Address already in use on another Account!";
        }
        
    }

// Change Contact by swapping old and new Contact Number and emptying old contact
    string changeCustContact(int _index, string _contact){
        if(custContactLink[_contact].length() == 0){
            swap(custContactLink[customers[_index].getContactNumber()], custContactLink[_contact]);
            custEmailLink[customers[_index].getEmailAddress()] = _contact;
            customers[_index].setCustContactNumber(_contact);
            return "Contact Number Change Successful!";
        } else{
            return "Contact Number already in use on another Email!";
        }
        
    }

// Shows All Customer 
    void showCustomer(){
        //int record = 0;
        int title[10] = {6, 14, 14, 25, 15, 10, 11, 9, 6, 7};
        cout << "\t" << char(218);
        for(int i = 0; i < 10; i++){
            cout << string(title[i], char(196)) << char(194);
        }
        cout << "\b" << char(191) << "\n\t" << char(179) << setw(title[0]) << "CODE " << char(179) << setw(title[1]) << "FIRST NAME " << char(179) << setw(title[2]) << "LAST NAME " << char(179) << setw(title[3]) << "EMAIL ADDRESS " << char(179) << setw(title[4]) << "CONTACT NUMBER" << char(179) << setw(title[5]) << "AREA " << char(179) << setw(title[6]) << "CITY " << char(179) << setw(title[7]) << "CASH " << char(179) << setw(title[8]) << "ORDERS" << char(179) << setw(title[9]) << "ACTIVE" << char(179);
        cout << "\n\t" << char(195);
        for(int i = 0; i < 10; i++){
            cout << string(title[i], char(196)) << char(197);
        }
        cout << "\b" << char(180);
        for(int j = 0; j < customers.size(); j++){
            cout << "\n\t" << char(179) << setw(title[0]) << customers[j].getCustomerCode() << char(179) << setw(title[1]) << customers[j].getFirstName() << char(179) << setw(title[2]) << customers[j].getLastName() << char(179) << setw(title[3]) << customers[j].getEmailAddress() << char(179) << setw(title[4]) << customers[j].getContactNumber() << char(179) << setw(title[5]) << customers[j].getArea() << char(179) << setw(title[6]) << customers[j].getCity() << char(179) << setw(title[7]) << customers[j].getWalletAmount() << char(179) << setw(title[8]) << customers[j].getOrderSize() << char(179) << setw(title[9]) << customers[j].getIsActive() << char(179);
            if((j % 32) == 0 && j != 0 && j != (customers.size() - 1)){
                cout << "\n\t" << char(192);
                for(int i = 0; i < 10; i++){
                    cout << string(title[i], char(196)) << char(193);
                }
                cout << "\b" << char(217) << endl;
                setMessage("More Records Found...");
                setContinue();
                cleanArea(2, 10, 143, 44);
                gotoxy(2, 9);
            }
        }
        cout << "\n\t" << char(192);
        for(int i = 0; i < 10; i++){
            cout << string(title[i], char(196)) << char(193);
        }
        cout << "\b" << char(217) << endl;
    }

// shows Customer using Customer Code
    void showCustomer(string _Code){
        int code;
        try{
            code = (stoi(_Code) - 1);
        } catch(exception& e){
            setMessage("Invalid Code Entered");
            return;
        }
        
        if(code < customers.size()){
            customers[code].showDetails();
        }
    }

// Shows Customer by Email Address
    void showCustomerByEmail(string _email){
        if(custEmailLink[_email].length() != 0 && custEmailLink[_email] != "0000"){
            showCustomer(custEmailLink[_email]);
        } else{
            setMessage("Customer Not Found!");
        }
    }

// Shows Customer by Contact Number
    void showCustomerByContact(string _contact){
        if(custEmailLink[custContactLink[_contact]].length() != 0){
            showCustomer(custEmailLink[custContactLink[_contact]]);
        } else{
            setMessage("Customer Not Found!");
        }
    }

// Shows Customer on Location
    void showCustOnLocation(int _city, int _area){
        int record = 0;
        int title[10] = {6, 14, 14, 25, 15, 10, 11, 9, 6, 7};
        cout << "\n\t" << char(218);
        for(int i = 0; i < 10; i++){
            cout << string(title[i], char(196)) << char(194);
        }
        cout << "\b" << char(191) << "\n\t" << char(179) << setw(title[0]) << "CODE " << char(179) << setw(title[1]) << "FIRST NAME " << char(179) << setw(title[2]) << "LAST NAME " << char(179) << setw(title[3]) << "EMAIL ADDRESS " << char(179) << setw(title[4]) << "CONTACT NUMBER" << char(179) << setw(title[5]) << "AREA " << char(179) << setw(title[6]) << "CITY " << char(179) << setw(title[7]) << "CASH " << char(179) << setw(title[8]) << "ORDERS" << char(179) << setw(title[9]) << "ACTIVE" << char(179);
        cout << "\n\t" << char(195);
        for(int i = 0; i < 10; i++){
            cout << string(title[i], char(196)) << char(197);
        }
        cout << "\b" << char(180);
        for(int j = 0; j < customers.size(); j++){
            if((customers[j].getCity() == cities[_city][0]) && (customers[j].getArea() == cities[_city][_area])){
                cout << "\n\t" << char(179) << setw(title[0]) << customers[j].getCustomerCode() << char(179) << setw(title[1]) << customers[j].getFirstName() << char(179) << setw(title[2]) << customers[j].getLastName() << char(179) << setw(title[3]) << customers[j].getEmailAddress() << char(179) << setw(title[4]) << customers[j].getContactNumber() << char(179) << setw(title[5]) << customers[j].getArea() << char(179) << setw(title[6]) << customers[j].getCity() << char(179) << setw(title[7]) << customers[j].getWalletAmount() << char(179) << setw(title[8]) << customers[j].getOrderSize() << char(179) << setw(title[9]) << customers[j].getIsActive() << char(179);
                record++;
                if((record % 32) == 0 && record != 0){
                    cout << "\n\t" << char(192);
                    for(int i = 0; i < 10; i++){
                        cout << string(title[i], char(196)) << char(193);
                    }
                    cout << "\b" << char(217) << endl;
                    setMessage("More Records Found...");
                    setContinue();
                    cleanArea(2, 10, 143, 44);
                    gotoxy(2, 9);
                }
            }
        }
        cout << "\n\t" << char(192);
        for(int i = 0; i < 10; i++){
            cout << string(title[i], char(196)) << char(193);
        }
        cout << "\b" << char(217) << endl;
        setMessage(to_string(record) + " Customers Found!");
    }

// Calculates Number of Orders of all Restaurant
    int calcOrders(string _type){
        int ordersCount = 0;
        if(_type == "Pending"){
            for(int i = 0; i < restaurants.size(); i++){
                ordersCount =+ restaurants[i].getOrdersPending();
            }
        } else if(_type == "Completed"){
            for(int i = 0; i < restaurants.size(); i++){
                ordersCount =+ restaurants[i].getOrdersCompleted();
            }
        } else if(_type == "Cancelled"){
            for(int i = 0; i < restaurants.size(); i++){
                ordersCount =+ restaurants[i].getOrdersCancelled();
            }
        } else{
            return -1;
        }
        return ordersCount;
    }

// Calculates Used and Unused Vouchers
    int calcVouchers(string _type){
        int vouchersCount = 0;
        for(int i = 0; i < vouchers.size(); i++){
            if(voucherValueLink[vouchers[i]] > 0){
                vouchersCount++;
            }
        }
        if(_type == "Unused"){
            return vouchersCount;
        } else if(_type == "Used"){
            return (vouchers.size() - vouchersCount);
        }
    }

// Calculates Restaurants that are Active and Closed
    int calcRestaurants(string _type){
        int restaurantsCount = 0;
        for(int i = 0; i < restaurants.size(); i++){
            if(managerLink[restaurants[i].getManagerID()] != "000"){
                restaurantsCount++;
            }
        }
        if(_type == "Active"){
            return restaurantsCount;
        } else if(_type == "Closed"){
            return (restaurants.size() - restaurantsCount);
        }
    }

// Calculates Number of Customers Active or Removed
    int calcCustomers(string _type){
        int customersCount = 0;
        for(int i = 0; i < customers.size(); i++){
            if(custEmailLink[customers[i].getEmailAddress()] != "0000"){
                customersCount++;
            }
        }
        if(_type == "Active"){
            return customersCount;
        } else if(_type == "Removed"){
            return (customers.size() - customersCount);
        }
    }

// Shows Summary
    void showSummary(){
        cout << "\tAdmin:\t\t>\t" << userName << "\n\n\tIs Open:\t>\tYES" << "\n\n\tRevenue:\t>\t" << revenue << "\n\n\tTax:\t\t>\t" << tax << "\n\n\tVouchers Used:\t>\t" << calcVouchers("Used") << "\n\n\tVouchers Unused:\t" << calcVouchers("Unused") << "\n\n\tRestaurants Active:\t" << calcRestaurants("Active") << "\n\n\tRestaurants Closed:\t" << calcRestaurants("Closed") << "\n\n\tCustomers Active:\t" << calcCustomers("Active") << "\n\n\tCustomers Removed:\t" << calcCustomers("Removed") << "\n\n\tOrders Completed:\t" << calcOrders("Completed") << "\n\n\tOrders Pending:\t>\t" << calcOrders("Pending") << "\n\n\tOrders Cancelled:\t" << calcOrders("Cancelled") << endl;
    }

};


// static member variables
double RESTAURANT::adminFee = 0;
double ADMINISTRATOR::revenue = 0;

int main(){
    // variables used in interface
    stringstream ss; // takes data as a stream
    tm mainTime;
    string inputString, choiceString, inputItem, inputItemSub, inputItems = "", strVecInput;
    string managerID, managerPassword, restaurantCode, title, description, contactNumber, address, openTime, closeTime, freeDelivery, restDiscount, minimumOrder, deliveryCharges;
    string firstName, lastName, customerCode, emailAddress;
    string userName,passWord;
    string itemCode;
	string orderNumber, paymentString;
    bool scrSizeCheck, firstInput = true;
    int fontSize = 19, menuIndex = 0, itemIndex, restIndex, custIndex, foodIndex, sizeIndex, cuisineIndex, quantity;
    int area, city;
    int intInput;
    int stock, limit, prepTime;
    double floatVecInput;
    double price, discount;
    vector<string> strVec; //used for pizza
    vector<double> floatVecPrice; //used for pizza
    fstream adminFile; // adminFile

    // sets Console Width to 144 and Height to 47 as well as FullScreen
    setConsoleSize(144, 47); 

    // Sets font size and L here is wide charcacter 
    setFontSize(fontSize, 500, L"Courier New");

    // sets Console Title
    SetConsoleTitle("Food-Panda");

    // sets bool as alphabetical(true and false) and fix to 2 decimal places
    cout << boolalpha << fixed << setprecision(2);

    // Main titles and borders printed 
    cout << char(201) << string(142, char(205)) << char(187) << endl;
    cout << char(186) << setw(76) << "Food-Panda" << setw(67) << char(186) << endl;
    cout << char(204) << string(142, char(205)) << char(185) << endl;
    cout << char(186) << setw(143) << char(186) << endl;
    cout << char(199) << string(142, char(196)) << char(182) << endl;

    for(int i = 6; i <= 44; i++){
        cout << char(186) << setw(143) << char(186) << endl;
    }
    cout << char(199) << string(142, char(196)) << char(182) << endl;
    cout << char(186) << " Message: " << setw(133) << char(186) << endl;
    cout << char(200) << string(142, char(205)) << char(188);

    // intilizes font size depending on screen resolution
    do{
        setMessage("Font Size is " + to_string(fontSize));
        gotoxy(25, 7);
        cout << "Can you See complete Double-:Lined Border inlined with you screen? (n-No): ";
        if(tolower(getche()) == 'n'){
            gotoxy(25, 9);
            cout << "You want it bigger or smaller? (b/s): ";
            if(tolower(getche()) == 'b'){
                setFontSize(++fontSize, 500, L"Courier New");
            } else{
                setFontSize(--fontSize, 500, L"Courier New");
            }
            scrSizeCheck = false;
        } else{
            scrSizeCheck = true;
        }
        cleanArea(25, 7, 143, 9);
    } while(scrSizeCheck == false);

// Admin file is attempted to be opened 
    adminFile.open("admin.dat", ios::in | ios::binary);
    if(!adminFile.is_open()){
        adminFile.close(); // if admin file does not exist then it goto Admin to create Admin
        goto ADMIN;
        
    } else{
        getline(adminFile, userName);
        getline(adminFile, passWord);
        adminFile.close();
        setMessage("Administrator Found!");
        goto CreateAdmin;
    }

// Creates First Run Admin 
    ADMIN:
    setMessage("Administrator Details not Found! Setting Up Administrator");
    do{
        cleanArea(2, 6, 143, 44);
        gotoxy(36, 7);
        cout << "Administrator ID: ";
        getline(cin, userName);
        gotoxy(36, 9);
        cout << "Administrator Password: ";
        hideInput(true); // hides cursor
        getline(cin, passWord);
        cout << string(passWord.length(), '*');
        hideInput(false); // shows Cursor
    } while(userName.length() == 0 || passWord.length() == 0);
    adminFile.open("admin.dat", ios::out | ios::app | ios::binary);
    adminFile << userName << endl << passWord << endl;
    adminFile.close();
    
// Creates objects and pointer objects of classes
    CreateAdmin:
    ADMINISTRATOR adminOb(userName, passWord);
    RESTAURANT * restOB = new RESTAURANT;
    CUSTOMER * custOB = new CUSTOMER;
    ORDER * orderOB = new ORDER;

// Menu 
    MENU:
    hideInput(false); // shows Cursor

// Prints all Title Menu 
    setTitle(menu[menuIndex][0]); 

// gotoxy Function that places cursor at a certain position    
    gotoxy(1, 6);
    for(int i = 6; i <= 44; i++){
        cout << char(186) << setw(143) << char(186) << endl;
    }
// cleans Area from one point to another
    cleanArea(2, 6, 143, 44);

// Prints Menu from Menu Vector
    for(int i = 1; i < menu[menuIndex].size(); i++){
        gotoxy(4, 5+(i*2));
        if(i == (menu[menuIndex].size() - 1)){
            cout << "0> ";
            itemIndex = i + 1;
        } else{
            cout << i << "> ";
        }
        cout << menu[menuIndex][i];
    }

//  Input from Menu which handles Cases as well 
    do{
        if(firstInput == false){
            setMessage("Invalid Input!");
        }
        cleanArea(12, 5+(itemIndex*2), 46, 5+(itemIndex*2));
        gotoxy(4, 5+(itemIndex*2));
        cout << "Choice: ";
        getline(cin, inputString);
        firstInput = false;
    } while((inputString.length() != 1) || inputString[0] < char(48) || inputString[0] > char(48 + menu[menuIndex].size() - 2)); // limits input of choices depending on menuindex
    firstInput = true;
    choiceString = choiceString + inputString;

// switch Cases for interface
    switch (stoi(choiceString)){
    case 1: //Administrator
        cleanArea(2, 6, 143, 44);
        setMessage("Please enter Administrator Credentials");
        gotoxy(36, 7);
        cout << "Administrator ID: ";
        getline(cin, userName);
        gotoxy(36, 9);
        cout << "Administrator Password: ";
        hideInput(true);
        getline(cin, passWord);
        cout << string(passWord.length(), '*');
        hideInput(false);
        if(userName == adminOb.getUserName() && passWord == adminOb.getPassWord()){
            setMessage("Administrator Authentication Successfull!");
            menuIndex = 1;
        } else{
            setMessage("Bad Username/Password!");
            menuIndex = 0;
            choiceString = "";
        }
        setContinue();
        goto MENU;
        break;
    
    case 11: // ADMIN > Show Details
        menuIndex = 2;
        goto MENU;
        break;

    case 112: // ADMIN > Show Details > show Restaurants
        menuIndex = 3;
        goto MENU;
        break;

    case 113: // ADMIN > Show Details > show Customers
        menuIndex = 13;
        goto MENU;
        break;

    case 12: // ADMIN > Restaurant management
        menuIndex = 4;
        goto MENU;
        break;

    case 13: // ADMIN > Customer Management
        menuIndex = 5;
        goto MENU;
        break;

    case 14: // ADMIN > Voucher Management
        menuIndex = 6;
        goto MENU;
        break;

    case 141: // ADMIN > Voucher Management > Add New Voucher
        cleanArea(2, 6, 143, 44);
        setTitle("Adding New Voucher");
        gotoxy(2, 7);
        cout << "\tEnter Voucher Code:\t";
        getline(cin, inputItem);
        cout << "\n\tEnter Voucher Value:\t";
        cin >> intInput;
        cin.clear();
        cin.ignore();
        setMessage(adminOb.addVoucher(inputItem, intInput));
        choiceString = choiceString.substr(0, (choiceString.length()-1));
        goto MENU;
        break;

    case 142: // ADMIN > Voucher Management > Block Voucher
        cleanArea(2, 6, 143, 44);
        setTitle("Block Voucher");
        gotoxy(2, 7);
        cout << "\tEnter Voucher Code:\t";
        getline(cin, inputItem);
        setMessage(adminOb.blockVoucher(inputItem));
        choiceString = choiceString.substr(0, (choiceString.length()-1));
        goto MENU;
        break;

    case 143: // ADMIN > Voucher Management > Send Voucher
        cleanArea(2, 6, 143, 44);
        setTitle("Send Voucher");
        gotoxy(2, 7);
        cout << "\tEnter Voucher Code:\t";
        getline(cin, inputItem);
        cout << "\n\tEnter Customer Code:\t";
        getline(cin, customerCode);
        setMessage(adminOb.sendVoucher(customerCode, inputItem));
        choiceString = choiceString.substr(0, (choiceString.length()-1));
        goto MENU;
        break;

    case 144: // ADMIN > Voucher Management > show Vouchers
        cleanArea(2, 6, 143, 44);
        setTitle("Show Vouchers");
        gotoxy(2, 7);
        cout << "\t1> Show All\n\n\t2> Find Voucher by Code\n\n\t3> Show Unused\n\n\t4> Show Expired\n\n\t5> Show Blocked\n\n\t0> Go Back\n\n\tChoice:\t";
        cin >> intInput;
        cin.clear();
        cin.ignore();
        cleanArea(2, 6, 143, 44);
        gotoxy(2, 7);
        if(intInput == 1){
            setMessage(adminOb.showVouchers());
        } else if(intInput == 2){
            cout << "\tVoucher Code:\t";
            getline(cin, inputItem);
            cleanArea(2, 6, 143, 44);
            gotoxy(2, 7);
            setMessage(adminOb.showVouchers(inputItem));
        } else if(intInput == 3){
            setMessage(adminOb.showVouchers(1));
        } else if(intInput == 4){
            setMessage(adminOb.showVouchers(-1));
        } else if(intInput == 5){
            setMessage(adminOb.showVouchers(0));
        }
        if(intInput > 0 && intInput < 6){
            setContinue();
        }
        choiceString = choiceString.substr(0, (choiceString.length()-1));
        goto MENU;
        break;

    case 2: //Restaurant Manager
        cleanArea(2, 6, 143, 44);
        setMessage("Please enter Manager Credentials");
        gotoxy(36, 7);
        if(adminOb.getRestaurantSize() > 0){
            cout << "Manager ID: ";
            getline(cin, managerID);
            gotoxy(36, 9);
            cout << "Manager Password: ";
            hideInput(true);
            getline(cin, managerPassword);
            cout << string(managerPassword.length(), '*');
            hideInput(false);
            restIndex = (adminOb.checkManager(managerID) - 1);
            if((restIndex >= 0) && (adminOb.getRestPassword(restIndex) == managerPassword)){
                setMessage("Manager Authentication Successfull!");
                restOB = adminOb.getRestaurant(restIndex);
                menuIndex = 7;
            } else{
                setMessage("Bad ID/Password!");
                menuIndex = 0;
                choiceString = "";
            }
        } else{
            menuIndex = 0;
            choiceString = "";
            setMessage("There is no Record of any Restaurant!");
        }
        goto MENU;
        break;

    case 21: // REST > show Details
        cleanArea(2, 6, 143, 44);
        setTitle("RESTAURANT DETAILS");
        gotoxy(2, 7);
        restOB->showDetails();
        setContinue();
        choiceString = choiceString.substr(0, (choiceString.length()-1));
        goto MENU;
        break;
    
    case 22: // REST > Manager Password Change
        setTitle("CHANGING PASSWORD");
        do{
            cleanArea(2, 6, 143, 44);
            gotoxy(2, 7);
            cout << "\tOld Password:\t\t";
            hideInput(true);
            getline(cin, inputItem);
            cout << string(inputItem.length(), '*') << "\n\tNew Password:\t\t";
            getline(cin, managerPassword);
            cout << string(managerPassword.length(), '*') << "\n\tRetype New Password:\t";
            getline(cin, passWord);
            cout << string(passWord.length(), '*');
            hideInput(false);
        }while(inputItem.length() == 0 || managerPassword.length() == 0 || passWord.length() == 0);
        if(passWord == managerPassword){
            if(restOB->getManagerPassword() == inputItem){
                restOB->setManagerPassword(passWord);
                setMessage("Password Change Successful!");
            } else{
                setMessage("Password Change Unsuccessful, Wrong Password!");
            }
        } else{
            setMessage("Password does not match!");
        }
        setContinue();
        choiceString = choiceString.substr(0, (choiceString.length()-1));
        goto MENU;
        break;

    case 23: // REST > Restaurant Open/Close
        if(restOB->getIsRestOpenR() == false){
            restOB->setIsRestOpen(true);
            setMessage("Restaurant Open");
        } else{
            restOB->setIsRestOpen(false);
            setMessage("Restaurant Closed");
        }
        choiceString = choiceString.substr(0, (choiceString.length()-1));
        goto MENU;
        break;

    case 24: // REST > Day/Time Setup
        cleanArea(2, 6, 143, 44);
        setTitle("Setting Up Opening Days/Timings");
        gotoxy(2, 7);
        cout << "\t1> Change Opening Days\n\n\t2> Change Timings\n\n\t0> Go Back\n\n\tChoice:\t";
        getline(cin, inputItem);
        if(inputItem == "1"){
            setMessage("Enter 0 - 6 to change Status or 'q' to quit.");
            do{
                cleanArea(2, 6, 143, 44);
                gotoxy(2, 7);
                restOB->displayDays();
                cout << "\n\n\tCode:\t";
                getline(cin, inputItem);
                if((inputItem.length() == 1) && (inputItem[0] >= 48 && inputItem[0] < 55)){
                    if(restOB->getDaysOpen(stoi(inputItem)) == true){
                        restOB->setDayClose(stoi(inputItem));
                        setMessage("Now Restaurant will stay Closed on " + days[stoi(inputItem)]);
                    } else {
                        restOB->setDayOpen(stoi(inputItem));
                        setMessage("Now Restaurant will stay Open on " + days[stoi(inputItem)]);
                    }
                } else if(inputItem == "q"){
                    setMessage("");
                } else{
                    setMessage("Invalid Input, enter 'q' to quit");
                }
            } while(tolower(inputItem[0]) != 'q');
        } else if(inputItem == "2"){
            cleanArea(2, 6, 143, 44);
            gotoxy(2, 7);
            cout << "\tOpening Time:\t";
            cin >> openTime;
            cout << "\tClosing Time:\t";
            cin >> closeTime;
            cin.clear();
            cin.ignore();
            try{
                if((stoi(openTime) >= 0 && stoi(openTime) < 24) && (stoi(closeTime) >= 0 && stoi(closeTime) < 24)){
                    restOB->setOpenTime(stoi(openTime));
                    restOB->setCloseTime(stoi(closeTime));
                    setMessage("Restaurant's Timings Changed");
                } else{
                    setMessage("Restaurant's Timings Unchanged! Incorrect time format use 24 Hours Format");
                }
            } catch(exception& e){
                setMessage("Invalid Time Entered");
                setContinue();
            }
        }
        // removes one string from choice String to go back to previous Menu
        choiceString = choiceString.substr(0, (choiceString.length()-1));
        goto MENU;
        break;
    
    case 25: // REST >Modifying Restaurant Details
        cleanArea(2, 6, 143, 44);
        setTitle("Modifying Restaurant Details");
        gotoxy(2, 7);
        cout << "\t1> Title\n\n\t2> Description\n\n\t3> Contact Number\n\n\t4> Location\n\n\t5> Discount Percentage\n\n\t6> Delivery Options\n\n\t0> Go Back\n\n\tChoice:\t";
        getline(cin, inputItem);
        cleanArea(2, 6, 143, 44);
        gotoxy(2, 7);
        if(inputItem == "1"){
            cout << "\tCurrent Title:\t";
            getline(cin, inputItemSub);
            cout << "\tNew Title:\t";
            getline(cin, title);
            if(restOB->getTitle() == inputItemSub && title.length() > 0){
                restOB->setTitle(title);
                setMessage("Restaurant Title Changed!");
            } else if(title.length() == 0){
                setMessage("Restaurant Title Unchanged!");
            } else{
                setMessage("Restaurant Title not matched!");
            }
        } else if(inputItem == "2"){
            cout << "\tCurrent Description:\t" << restOB->getDescription().substr(0, 100) << "\n\n\tNew Description:\t";
            getline(cin, inputItemSub);
            if(inputItemSub.length() > 0){
                restOB->setDescription(inputItemSub);
                setMessage("Restaurant Description Changed!");
            } else{
                setMessage("Restaurant Description Unchanged!");
            }
        } else if(inputItem == "3"){
            cout << "\tCurrent Contact Number:\t" << restOB->getContactNumber() << "\n\n\tNew Contact Number:\t";
            getline(cin, inputItemSub);
            if(inputItemSub.length() > 0){
                restOB->setContactNumber(inputItemSub);
                setMessage("Restaurant Contact Number Changed!");
            } else{
                setMessage("Restaurant Contact Number Unchanged!");
            }
        } else if(inputItem == "4"){
            cout << "\tCities:\n";
            for(int i = 0; i < cities.size(); i++){
                cout << "\t\t" << i << ") " << cities[i][0] << endl;
            }
            cout << "\tChoice:\t";
            try{
                cin >> city;
                cin.clear();
                cin.ignore();
                if(city < 0 && city > 4){
                    throw "Invalid City Entered"; 
                }    
            } catch(const char* msg){
                setMessage(msg);
                setContinue();
                choiceString = choiceString.substr(0, (choiceString.length()-1));
                goto MENU;
            }
            
            cout << "\n\tArea:\n";
            for(int i = 1; i < cities[city].size(); i++){
                cout << "\t\t" << i << ") " << cities[city][i] << endl;
            }
            cout << "\tChoice:\t";
            cin.clear();
            cin.ignore();
            try{
                cin >> area;
                if(area <= 0){
                    throw "Invalid Area Entered";
                }
            } catch(const char* msg){
                cin.clear();
                cin.ignore();
                setMessage(msg);
                setContinue();
                choiceString = choiceString.substr(0, (choiceString.length()-1));
                goto MENU;
            }
            cin.clear();
            cin.ignore();
            cout << "\n\tAddress:\t";
            getline(cin, address);
            restOB->setCity(city);
            restOB->setArea(area);
            restOB->setAddress(address);
            setMessage("Restaurant Location Changed!");
        } else if(inputItem == "5"){
            cout << "\tCurrent Discount Percentage:\t" << restOB->getRestDiscount() << "%\n\n\tNew Discount Percentage:\t";
            cin >> discount;
            cin.clear();
            cin.ignore();
            restOB->setDiscount(discount);
            setMessage("Restaurant Discount Percentage Changed!");
        } else if(inputItem == "6"){
            cout << "\tDo you offer Free Delivery (y/n):\t";
            if(tolower(getche()) == 'y'){
                restOB->setFreeDelivery(true);
                cout << "\n\n\tMinimum Order for Free Delivery:\t";
                getline(cin, inputItemSub);
                try{
                    restOB->setMininmumOrder(stoi(inputItemSub));
                    if(stoi(inputItemSub) > 0){
                        cout << "\n\tDelivery Charges for Orders less than " << inputItemSub << ":\t";
                        getline(cin, inputItemSub);
                        restOB->setDeliveryCharges(stod(inputItemSub));
                    } else{
                        restOB->setDeliveryCharges(0);
                    }
                } catch(exception& e){
                    setMessage("Invalid Input!");
                    setContinue();
                    choiceString = choiceString.substr(0, (choiceString.length()-1));
                    goto MENU;
                }
            } else{
                restOB->setFreeDelivery(false);
                restOB->setMininmumOrder(0);
                cout << "\n\n\tDelivery Charges for All Orders:\t";
                getline(cin, inputItemSub);
                try{
                    restOB->setDeliveryCharges(stod(inputItemSub));
                } catch(exception& e){
                    setMessage("Invalid Input!");
                    setContinue();
                    choiceString = choiceString.substr(0, (choiceString.length()-1));
                    goto MENU;
                }
            }
            setMessage("Restaurant Delivery Options Changed!");
        } else if(inputItem != "0"){
            setMessage("Invalid Options!");
        }
        setContinue();
        choiceString = choiceString.substr(0, (choiceString.length()-1));
        goto MENU;
        break;

    case 26: // REST > Menu Mangement
        menuIndex = 8;
        goto MENU;
        break;

    case 261: // REST > Menu Mangement > Add Item
        setTitle("RESTAURANT > MENU > Adding Item");
        setMessage("Enter '0 - 11' to Add Item OR anything else to Quit.");
        cleanArea(2, 6, 143, 44);
        gotoxy(1, 7);
        cout << "\tCuisine List:";
        for(int i = 0; i < cuisineTitle.size(); i++){
            cout << "\n\n\t\t" << i << "> " << cuisineTitle[i];
        }
        cout << "\n\tChoice:\t";
        getline(cin, inputItem);
        try{
            if(((inputItem.length() == 1) && (inputItem[0] >= 48 && inputItem[0] < 58)) || inputItem == "10" || inputItem == "11"){
                do{
                    cleanArea(2, 6, 143, 44);
                    gotoxy(2, 7);
                    cout << "\tTitle:\t\t\t";
                    getline(cin, title);
                } while(title.length() == 0);
                cout << "\n\tDescription:\t\t";
                getline(cin, description);
                cout << "\n\tStock:\t\t\t";
                cin >> stock;
                cin.clear();
                cin.ignore();
                cout << "\n\tMax Order Limit:\t";
                cin >> limit;
                cin.clear();
                cin.ignore();
                cout << "\n\tPreparation Time:\t";
                cin >> prepTime;
                cin.clear();
                cin.ignore();
                cout << "\n\tDiscount Percentage:\t";
                cin >> discount;
                cin.clear();
                cin.ignore();
                if(inputItem != "0"){
                    cout << "\n\tPrice (per Unit/Pound):\t";
                    cin >> price;
                    cin.clear();
                    cin.ignore();
                }
                if(inputItem == "0"){
                    strVec.clear();
                    floatVecPrice.clear();
                    cout << "\n\tDo you offer \"" << title << "\" in different sizes? (y/n):\t";
                    if(tolower(getche()) == 'y'){
                        cout << "\n\n\tNumber of Sizes:\t";
                        cin >> intInput;
                        cin.clear();
                        cin.ignore();
                        if(intInput <= 0){
                            intInput = 1;
                        }
                        for(int i = 0; i < intInput; i++){
                            cleanArea(2, 6, 143, 44);
                            gotoxy(1, 7);
                            cout << "\n\tSize: " << (i + 1) << "\n\n\tSize Description:\t";
                            cin >> strVecInput;
                            cin.clear();// 
                            cin.ignore(); //
                            strVec.push_back(strVecInput);
                            cout << "\n\tPrice:\t";
                            cin >> floatVecInput;
                            floatVecPrice.push_back(floatVecInput);
                            cin.clear();
                            cin.ignore();
                            //cout << "\n";
                        }
                    } else{
                        cout << "\n\tDef";
                        strVec.push_back("Default");
                        cout << "\n\tPrice:\t\t\t";
                        cin >> floatVecInput;
                        floatVecPrice.push_back(floatVecInput);
                        cin.clear();
                        cin.ignore();
                    }
                    PIZZA pizzaOB(title, description, stock, limit, prepTime, discount, floatVecPrice, strVec);
                    restOB->addItem(pizzaOB);
                } else if(inputItem == "1"){
                    BURGER burgerOB(title, description, stock, limit, prepTime, discount, price);
                    restOB->addItem(burgerOB);
                } else if(inputItem == "2"){
                    SANDWICHE sandwichOB(title, description, stock, limit, prepTime, discount, price);
                    restOB->addItem(sandwichOB);
                } else if(inputItem == "3"){
                    FASTFOOD fastFoodOB(title, description, stock, limit, prepTime, discount, price);
                    restOB->addItem(fastFoodOB);
                } else if(inputItem == "4"){
                    BARBQ barbqOB(title, description, stock, limit, prepTime, discount, price);
                    restOB->addItem(barbqOB);
                } else if(inputItem == "5"){
                    PAKISTANI pakistaniOB(title, description, stock, limit, prepTime, discount, price);
                    restOB->addItem(pakistaniOB);
                } else if(inputItem == "6"){
                    CHINESE chineseOB(title, description, stock, limit, prepTime, discount, price);
                    restOB->addItem(chineseOB);
                } else if(inputItem == "7"){
                    INTERNATIONAL internationalOB(title, description, stock, limit, prepTime, discount, price);
                    restOB->addItem(internationalOB);
                } else if(inputItem == "8"){
                    SEAFOOD seaFoodOB(title, description, stock, limit, prepTime, discount, price);
                    restOB->addItem(seaFoodOB);
                } else if(inputItem == "9"){
                    DESSERT dessertOB(title, description, stock, limit, prepTime, discount, price);
                    restOB->addItem(dessertOB);
                } else if(inputItem == "10"){
                    CAKE cakeOB(title, description, stock, limit, prepTime, discount, price);
                    restOB->addItem(cakeOB);
                } else if(inputItem == "11"){
                    BEVERAGE beverageOB(title, description, stock, limit, prepTime, discount, price);
                    restOB->addItem(beverageOB);
                }
                setMessage(cuisineTitle[stoi(inputItem)] + " Item Added to Menu");
            } else{
                setMessage("Nothing Added to Menu!");
            }
        } catch(exception& e){
            setMessage("Invalid Input Nothing Added to Menu!");
        }
        setContinue();
        choiceString = choiceString.substr(0, (choiceString.length()-1));
        goto MENU;
        break;
    
    case 262: // REST > Menu Mangement > Modifying Item
        setTitle("RESTAURANT > MENU > Modifying Item");
        setMessage("Enter Item Code to modify it!");
        cleanArea(2, 6, 143, 44);
        gotoxy(1, 7);
        cout << "\tItem Code:\t";
        getline(cin, inputItem);
        try{
            if((inputItem.length() == 8) && (inputItem.substr(0, 3) == restOB->getCode())){
                foodIndex = (stoi(inputItem.substr(5, 3)) - 1);
                cleanArea(2, 6, 143, 44);
                gotoxy(1, 7);
                cout << "\tOld Title:\n\tNew Title:\n\n\tOld Description:\n\tNew Description:\n\n\tOld Stock:\n\tNew Stock:\n\n\tOld Order Limit:\n\tNew Order Limit:\n\n\tOld Preparation Time:\n\tNew  Preparation Time:\n\n\tOld Discount:\n\tNew  Discount:";
                if(inputItem.substr(3, 2) == "00"){
                    PIZZA * pizzaOB = new PIZZA;
                    if(foodIndex < restOB->getPizzaSize()){
                        pizzaOB = restOB->getPizza(stoi(inputItem.substr(5, 3)) - 1);
                    } else{
                        setMessage("Invalid Item Code!");
                        setContinue();
                        choiceString = choiceString.substr(0, (choiceString.length()-1));
                        goto MENU;
                    }
                    gotoxy(1, 7);
                    cout << "\t\t\t\t" << pizzaOB->getTitle() << "\n\n\n\t\t\t\t" << pizzaOB->getDescription() << "\n\n\n\t\t\t\t" << pizzaOB->getStock() << "\n\n\n\t\t\t\t" << pizzaOB->getLimit() << "\n\n\n\t\t\t\t" << pizzaOB->getPrepTime() << "\n\n\n\t\t\t\t" << pizzaOB->getDiscount();
                    gotoxy(1, 6);
                    for(int i = 0; i < 6; i++){
                        cout << "\n\n\t\t\t\t";
                        getline(cin, inputItemSub);
                        if(inputItemSub.length() != 0){
                            if(i == 0){pizzaOB->setTitle(inputItemSub);}
                            else if(i == 1){pizzaOB->setDescription(inputItemSub);}
                            else if(i == 2){pizzaOB->setStock(stoi(inputItemSub));}
                            else if(i == 3){pizzaOB->setLimit(stoi(inputItemSub));}
                            else if(i == 4){pizzaOB->setPrepTime(stoi(inputItemSub));}
                            else if(i == 5){pizzaOB->setDiscount(stod(inputItemSub));}
                        }
                    }
                    strVec.clear();
                    floatVecPrice.clear();
                    cout << "\n\tDo you offer \"" << pizzaOB->getTitle() << "\" in different sizes? (y/n):\t";
                    if(tolower(getche()) == 'y'){
                        cout << "\n\n\tNumber of Sizes:\t";
                        cin >> intInput;
                        cin.clear();
                        cin.ignore();
                        for(int i = 0; i < intInput; i++){
                            cleanArea(2, 6, 143, 44);
                            gotoxy(1, 7);
                            cout << "\n\tSize: " << (i + 1) << "\n\n\tSize Description:\t";
                            cin >> strVecInput;
                            cin.clear();//
                            cin.ignore();//
                            strVec.push_back(strVecInput);
                            cout << "\n\tPrice:\t";
                            cin >> floatVecInput;
                            floatVecPrice.push_back(floatVecInput);
                            cin.clear();
                            cin.ignore();
                        }
                    } else{
                        strVec.push_back("Default");
                        cout << "\n\tPrice:\t";
                        cin >> floatVecInput;
                        floatVecPrice.push_back(floatVecInput);
                        cin.clear();
                        cin.ignore();
                    }
                    pizzaOB->setSize(strVec);
                    pizzaOB->setPrice(floatVecPrice);
                    setMessage("Menu Item '" + inputItem + "' Modified!");
                } else if((inputItem[3] == '0' && (inputItem[4] > 48 && inputItem[4] < 58)) || inputItem.substr(3, 2) == "10" || inputItem.substr(3, 2) == "11"){
                    cout << "\n\n\tOld Price:\n\tNew Price:";
                    FOOD * foodOB = new FOOD(stoi(inputItem.substr(3, 2)));
                    if(inputItem.substr(3, 2) == "01" && foodIndex < restOB->getBurgerSize()){
                        foodOB = restOB->getBurger(stoi(inputItem.substr(5, 3)) - 1);
                    } else if(inputItem.substr(3, 2) == "02" && foodIndex < restOB->getSandwicheSize()){
                        foodOB = restOB->getSandwich(stoi(inputItem.substr(5, 3)) - 1);
                    } else if(inputItem.substr(3, 2) == "03" && foodIndex < restOB->getFastFoodSize()){
                        foodOB = restOB->getFastFood(stoi(inputItem.substr(5, 3)) - 1);
                    } else if(inputItem.substr(3, 2) == "04" && foodIndex < restOB->getBarBQsize()){
                        foodOB = restOB->getBarbq(stoi(inputItem.substr(5, 3)) - 1);
                    } else if(inputItem.substr(3, 2) == "05" && foodIndex < restOB->getPakistaniSize()){
                        foodOB = restOB->getPakistani(stoi(inputItem.substr(5, 3)) - 1);
                    } else if(inputItem.substr(3, 2) == "06" && foodIndex < restOB->getChineseSize()){
                        foodOB = restOB->getChinese(stoi(inputItem.substr(5, 3)) - 1);
                    } else if(inputItem.substr(3, 2) == "07" && foodIndex < restOB->getInternationalSize()){
                        foodOB = restOB->getInternational(stoi(inputItem.substr(5, 3)) - 1);
                    } else if(inputItem.substr(3, 2) == "08" && foodIndex < restOB->getSeaFoodSize()){
                        foodOB = restOB->getSeafood(stoi(inputItem.substr(5, 3)) - 1);
                    } else if(inputItem.substr(3, 2) == "09" && foodIndex < restOB->getDessertSize()){
                        foodOB = restOB->getDessert(stoi(inputItem.substr(5, 3)) - 1);
                    } else if(inputItem.substr(3, 2) == "10" && foodIndex < restOB->getCakeSize()){
                        foodOB = restOB->getCake(stoi(inputItem.substr(5, 3)) - 1);
                    } else if(inputItem.substr(3, 2) == "11" && foodIndex < restOB->getBeveragesSize()){
                        foodOB = restOB->getBeverage(stoi(inputItem.substr(5, 3)) - 1);
                    }
                    gotoxy(1, 7);
                    cout << "\t\t\t\t" << foodOB->getTitle() << "\n\n\n\t\t\t\t" << foodOB->getDescription() << "\n\n\n\t\t\t\t" << foodOB->getStock() << "\n\n\n\t\t\t\t" << foodOB->getLimit() << "\n\n\n\t\t\t\t" << foodOB->getPrepTime() << "\n\n\n\t\t\t\t" << foodOB->getDiscount() << "\n\n\n\t\t\t\t" << foodOB->getPrice();
                    gotoxy(1, 6);
                    for(int i = 0; i < 7; i++){
                        cout << "\n\n\t\t\t\t";
                        getline(cin, inputItemSub);
                        if(inputItemSub.length() != 0){
                            if(i == 0){foodOB->setTitle(inputItemSub);}
                            else if(i == 1){foodOB->setDescription(inputItemSub);}
                            else if(i == 2){foodOB->setStock(stoi(inputItemSub));}
                            else if(i == 3){foodOB->setLimit(stoi(inputItemSub));}
                            else if(i == 4){foodOB->setPrepTime(stoi(inputItemSub));}
                            else if(i == 5){foodOB->setDiscount(stod(inputItemSub));}
                            else if(i == 6){foodOB->setPrice(stod(inputItemSub));}
                        }
                    }
                }
                setMessage("Menu Item '" + inputItem + "' Modified!");
            } else{
                setMessage("Invalid Code");
            }
        } catch(exception& e){
            setMessage("Invalid Input! Maybe something Modified partially, Please Recheck!");
        }
        setContinue();
        choiceString = choiceString.substr(0, (choiceString.length()-1));
        goto MENU;
        break;

// sets Stock to zero    
    case 263: // REST > Menu Mangement > Deleting Item 
        setTitle("RESTAURANT > MENU > Deleting Item");
        setMessage("Enter Item Code to delete it!");
        cleanArea(2, 6, 143, 44);
        gotoxy(1, 7);
        cout << "\tItem Code:\t";
        getline(cin, inputItem);
        if((inputItem.length() == 8) && (inputItem.substr(0, 3) == restOB->getCode())){
            setMessage(restOB->deleteItem(inputItem));
        } else{
            setMessage("Invalid Code");
        }
        setContinue();
        choiceString = choiceString.substr(0, (choiceString.length()-1));
        goto MENU;
        break;
    
    case 264: // REST > Menu Mangement > show Details
        menuIndex = 14;
        goto MENU;
        break;

    case 2641: // REST > Menu Mangement > show Details > Show All
        cleanArea(2, 6, 143, 44);
        setTitle("MENU ITMES (ALL)");
        gotoxy(2, 7);
        restOB->showFood(12);
        choiceString = choiceString.substr(0, (choiceString.length()-1));
        goto MENU;
        break;

    case 2642: // REST > Menu Mangement > show Details > show by cuisine
        cleanArea(2, 6, 143, 44);
        setTitle("MENU ITMES (By Cuisine)");
        gotoxy(2, 7);
        cout << "\tSelect Cuisine:\n";
        for(int i = 0; i < cuisineTitle.size(); i++){
            cout << "\n\t\t" << i << "> " << cuisineTitle[i];
        }
        cout << "\n\n\tChoice:\t";
        cin >> intInput;
        cin.clear();
        cin.ignore();
        if(intInput >= 0 && intInput < 12){
            cleanArea(2, 6, 143, 44);
            setTitle("MENU ITMES (Cuisine: " + cuisineTitle[intInput] + ")");
            gotoxy(2, 7);
            restOB->showFood(intInput);
        } else{
            setMessage("Invalid Code!");
        }
        choiceString = choiceString.substr(0, (choiceString.length()-1));
        goto MENU;
        break;

        case 2643: // REST > Menu Mangement > show Details > show by code
        cleanArea(2, 6, 143, 44);
        setTitle("MENU ITMES (By Code)");
        gotoxy(2, 7);
        cout << "\tItem Code:\t";
        getline(cin, inputItem);
        if((inputItem.length() == 8) && (inputItem.substr(0, 3) == restOB->getCode()) && (inputItem[4] > 47 && inputItem[4] < 58) && (inputItem[3] > 47 && inputItem[3] < 50)){
            cleanArea(2, 6, 143, 44);
            setTitle("MENU ITMES (Code: " + inputItem + ")");
            gotoxy(2, 7);
            restOB->showFood(inputItem);
        } else{
            setMessage("Invalid Code!");
        }
        setContinue();
        choiceString = choiceString.substr(0, (choiceString.length()-1));
        goto MENU;
        break;

    case 27: // REST > Order Mangement
        menuIndex = 9;
        goto MENU;
        break;

    case 271: // REST > Order Mangement > show Details
        setTitle("RESTAURANT MANAGER > Order Management > Show Details");
        cleanArea(2, 6, 143, 44);
        gotoxy(2, 7);
        cout << "\t1> Show All\n\n\t2> Show Order\n\n\t0> Go Back\n\n\t\tChoice:\t";
        getline(cin, inputItem);
        cleanArea(2, 6, 143, 44);
        if(inputItem == "1"){
            setTitle("ORDERS (ALL)");
            gotoxy(2, 7);
            restOB->showAllOrders();
        } else if(inputItem == "2"){
            setTitle("ORDER (CODE)");
            gotoxy(2, 7);
            cout << "\tOrder Number:\t";
            getline(cin, orderNumber);
            if(orderNumber.length() == 10 && orderNumber.substr(0, 3) == restOB->getCode()){
                cleanArea(2, 6, 143, 44);
                setTitle("ORDER (" + orderNumber + ")");
                gotoxy(2, 7);
                restOB->showOrder(orderNumber);
            } else{
                setMessage("Invalid Order Code!");
            }
        } else if(inputItem != "0"){
            setMessage("Invalid Choice!");
        }
        setContinue();
        choiceString = choiceString.substr(0, (choiceString.length()-1));
        goto MENU;
        break;

    case 3: // CUST
        menuIndex = 10;
        goto MENU;
        break;

    case 31: // CUST > new Customer
        do{
            cleanArea(2, 6, 143, 44);
            gotoxy(2, 7);
            cout << "\tEmail Address:\t";
            getline(cin, emailAddress);
            cout << "\tContact Number:\t";
            getline(cin, contactNumber);
        }while(emailAddress.length() == 0 || contactNumber.length() == 0 || adminOb.checkCustomer(emailAddress, contactNumber) != -1);
        cout << "\n\tCities:\n";
        for(int i = 0; i < cities.size(); i++){
            cout << "\t\t" << i << ") " << cities[i][0] << endl;
        }
        cout << "\tChoice:\t\t";
        try{
            cin >> city;
            cin.clear();
            cin.ignore();
            if(city < 0 && city > 4){
                throw "Invalid City Entered"; 
            }    
        } catch(const char* msg){
            setMessage(msg);
            setContinue();
            choiceString = choiceString.substr(0, (choiceString.length()-1));
            goto MENU;
        }
        cout << "\n\tArea:\n";
        for(int i = 1; i < cities[city].size(); i++){
            cout << "\t\t" << i << ") " << cities[city][i] << endl;
        }
        cout << "\tChoice:\t\t";
        try{
            cin >> area;
            cin.clear();
            cin.ignore();
            if(area <= 0){
                throw "Invalid Area!";
            }
        } catch(const char* msg){
            setMessage(msg);
            setContinue();
            choiceString = choiceString.substr(0, (choiceString.length()-1));
            goto MENU;
        }
        cleanArea(2, 6, 143, 44);
        gotoxy(2, 7);
        cout << "\n\tAddress:\t";
        getline(cin, address);
        cout << "\n\tFirst Name:\t";
        getline(cin, firstName);
        cout << "\n\tLast Name:\t";
        getline(cin, lastName);
        cout << "\n\tPassword:\t";
        hideInput(true);
        getline(cin, passWord);
        cout << string(passWord.length(), '*');
        hideInput(false);
        if(emailAddress.length() != 0 && contactNumber.length() != 0 && passWord.length() != 0 && (city >= 0 && city < 6) && (area > 0 && area <= cities[city].size())){
            CUSTOMER custOb(firstName, lastName, passWord, emailAddress, contactNumber, address, area, city);
            adminOb.addCustomer(custOb);
            setMessage("Customer Added Successfully");
        } else{
            setMessage("Mandatory Fields cannot be left empty OR Invalid City/Area option!");
        }
        setContinue();
        choiceString = choiceString.substr(0, (choiceString.length()-1));
        goto MENU;
        break;

    case 32: // CUST > Sign In
        cleanArea(2, 6, 143, 44);
        setMessage("Please enter Customer Credentials");
        gotoxy(36, 7);
        if(adminOb.getCustomerSize() > 0){
            cout << "Customer Email/Contact: ";
            getline(cin, emailAddress);
            gotoxy(36, 9);
            cout << "Customer Password: ";
            hideInput(true);
            getline(cin, passWord);
            cout << string(passWord.length(), '*');
            hideInput(false);
            custIndex = (adminOb.checkCustomer(emailAddress) - 1);
            if((custIndex >= 0) && (adminOb.getCustPassword(custIndex) == passWord)){
                setMessage("Customer Authentication Successfull!");
                custOB = adminOb.getCustomer(custIndex);
                menuIndex = 11;
            } else{
                setMessage("Bad Email/Contact OR Password!");
                menuIndex = 10;
                choiceString = choiceString.substr(0, (choiceString.length()-1));
            }
        } else{
            menuIndex = 10;
            choiceString = choiceString.substr(0, (choiceString.length()-1));
            setMessage("There is no Record of any Customer!");
        }
        goto MENU;
        break;

    case 321: // CUST > Sign In > show Details
        cleanArea(2, 6, 143, 44);
        gotoxy(1, 7);
        custOB->showDetails();
        setContinue();
        choiceString = choiceString.substr(0, (choiceString.length()-1));
        goto MENU;
        break;

    case 322: // CUST > Sign In > Modify Details
        cleanArea(2, 6, 143, 44);
        gotoxy(1, 7);
        cout << "\t1> Change Password\n\n\t2> Change Email Address\n\n\t3> Change Contact Number\n\n\t4> Change Location\n\n\t0> Go Back\n\n\tChoice:\t";
        getline(cin, inputItem);
        cleanArea(2, 6, 143, 44);
        gotoxy(1, 7);
        if(inputItem == "1"){
            cout << "\tOld Password:\t\t";
            hideInput(true);
            getline(cin, passWord);
            cout << string(passWord.length(), '*') << "\n\tNew Password:\t\t";
            getline(cin, managerPassword);
            cout << string(managerPassword.length(), '*') << "\n\tRetype New Password:\t";
            getline(cin, inputItemSub);
            cout << string(inputItemSub.length(), '*');
            hideInput(false);
            if(managerPassword == inputItemSub && managerPassword.length() > 0){
                if(passWord == custOB->getCustPassword()){
                    custOB->setCustPassword(inputItemSub);
                    setMessage("Password Change Successful!");
                } else{
                    setMessage("Wrong Password! Password Change Unsuccessful!");
                }
            } else{
                setMessage("New Password not Matched!");
            }
        } else if(inputItem == "2"){
            cout << "\tPassword:\t";
            hideInput(true);
            getline(cin, passWord);
            cout << string(passWord.length(), '*');
            hideInput(false);
            if(passWord == custOB->getCustPassword()){
                cout << "\n\tNew Email Address:\t";
                getline(cin, emailAddress);
                if(emailAddress.length() > 0){
                    setMessage(adminOb.changeCustEmail(custIndex, emailAddress));
                } else{
                    setMessage("Email cannot be Empty!");
                }
            } else{
                setMessage("Wrong Password Entered!");
            }
        } else if(inputItem == "3"){
            cout << "\tPassword:\t";
            hideInput(true);
            getline(cin, passWord);
            cout << string(passWord.length(), '*');
            hideInput(false);
            if(passWord == custOB->getCustPassword()){
                cout << "\n\tNew Contact Number:\t";
                getline(cin, contactNumber);
                if(contactNumber.length() > 0){
                    setMessage(adminOb.changeCustContact(custIndex, contactNumber));
                } else{
                    setMessage("Contact Number cannot be Empty!");
                }
            } else{
                setMessage("Wrong Password Entered!");
            }
        } else if(inputItem == "4"){
            cout << "\tCities:\n";
            for(int i = 0; i < cities.size(); i++){
                cout << "\t\t" << i << ") " << cities[i][0] << endl;
            }
            cout << "\tChoice:\t";
            try{
                cin >> city;
                cin.clear();
                cin.ignore();
                if(city < 0 && city > 4){
                    throw "Invalid City Entered"; 
                }    
            } catch(const char* msg){
                setMessage(msg);
                setContinue();
                choiceString = choiceString.substr(0, (choiceString.length()-1));
                goto MENU;
            }
            cout << "\n\tArea:\n";
            for(int i = 1; i < cities[city].size(); i++){
                cout << "\t\t" << i << ") " << cities[city][i] << endl;
            }
            cout << "\tChoice:\t";
            try{
                cin >> area;
                cin.clear();
                cin.ignore();
                if(area <= 0){
                    throw "Invalid Area Entered!";
                }
            } catch(const char* msg){
                setMessage(msg);
                setContinue();
                choiceString = choiceString.substr(0, (choiceString.length()-1));
                goto MENU;
            }
            cout << "\n\tAddress:\t";
            getline(cin, address);
            custOB->setCustCity(city);
            custOB->setCustArea(area);
            custOB->setCustAddress(address);
            setMessage("Customer Location Changed!");
        }
        setContinue();
        choiceString = choiceString.substr(0, (choiceString.length()-1));
        goto MENU;
        break;

    case 323: // CUST > Sign In > order Food
        menuIndex = 15;
        goto MENU;
        break;

    case 3231: // CUST > Sign In > Order Food > show Restauants
        menuIndex = 16;
        goto MENU;
        break;

    case 32311: // CUST > Sign In > Order Food > show Restaurant > show All
        cleanArea(2, 6, 143, 44);
        setTitle("RESTAURANTS (ALL)");
        gotoxy(2, 7);
        adminOb.showRestaurants();
        setContinue();
        choiceString = choiceString.substr(0, (choiceString.length()-1));
        goto MENU;
        break;

    case 32312: // CUST > Sign In > Order Food > show Restaurant > By cuisine
        cleanArea(2, 6, 143, 44);
        setTitle("CUSTOMER > Sign In > Order Food > Show Restaurants > By Cuisine");
        gotoxy(2, 7);
        for(int i = 0; i < cuisineTitle.size(); i++){
            cout << "\t" << (i + 1) << "> " << cuisineTitle[i] << "\n" << endl;
        }
        cout << "\t0> Go Back\n\n\tChoice: ";
        getline(cin, inputItem);
        try{
            inputItem = to_string(stoi(inputItem) - 1);
        } catch(exception& e){
            setMessage("Invalid Cuisine Index!");
            setContinue();
            choiceString = choiceString.substr(0, (choiceString.length()-1));
            goto MENU;
        }
        setTitle("RESTAURANTS {" + cuisineTitle[stoi(inputItem)] + "}");
        gotoxy(2, 7);
        if(inputItem != "-1"){
            cleanArea(2, 6, 143, 44);
            gotoxy(3, 7);
            try{
                if(stoi(inputItem) > 11){
                    throw "Invalid Cuisine!";
                }
            } catch(const char* msg){
                setMessage(msg);
                setContinue();
                choiceString = choiceString.substr(0, (choiceString.length()-1));
                goto MENU;
            }
            adminOb.showRestWithCuisine(cuisineTitle[stoi(inputItem)]);
        } else{
            setMessage("Invalid Cuisine!");
        }
        setContinue();
        choiceString = choiceString.substr(0, (choiceString.length()-1));
        goto MENU;
        break;

    case 32313: // CUST > Sign In > Order Food > show Restaurant > By location
    cleanArea(2, 6, 143, 44);
        setTitle("CUSTOMER > Sign In > Order Food > Show Restaurants > By Location");
        gotoxy(2, 7);
        for(int i = 0; i < cities.size(); i++){
            cout << "\t" << (i + 1) << "> " << cities[i][0] << "\n" << endl;
        }
        cout << "\t0> Go Back\n\n\tChoice: ";
        cin >> city;
        cin.clear();//
        cin.ignore();//
        city--;
        if(city >= 0 && city < 5){
            cleanArea(2, 6, 143, 44);
            gotoxy(4, 7);
            for(int i = 1; i < cities[city].size(); i++){
                cout << "\t" << i << "> " << cities[city][i] << "\n" << endl;
            }
            cout << "\t0> Go Back\n\n\tChoice: ";
            cin >> area;
            cin.clear();
            cin.ignore();
            if(area > 0 && area < cities[city].size()){
                cleanArea(2, 6, 143, 44);
                gotoxy(3, 7);
                adminOb.showRestOnLocation(city, area);
            } else{
                setMessage("Invalid Area!");
            }
        } else{
            setMessage("Invalid City!");
        }
        setContinue();
        choiceString = choiceString.substr(0, (choiceString.length()-1));
        goto MENU;
        break;

    case 3232: // CUST > Sign In > Order Food > show Restaurant Menu
        cleanArea(2, 6, 143, 44);
        gotoxy(1, 7);
        cout << "\tRestaurant Code:\t";
        getline(cin, restaurantCode);
        if(restaurantCode.length() == 3){
            cuisineIndex = -1;
            try{
                restIndex = (stoi(restaurantCode) - 1);
            } catch(exception& e){
                setMessage("Invalid Restaurant Code Entered!");
                setContinue();
                choiceString = choiceString.substr(0, (choiceString.length()-1));
                goto MENU;
            }
            if(restIndex > -1 && restIndex < adminOb.getRestaurantSize()){
                restOB = adminOb.getRestaurant(restIndex);
                if(custOB->getCity() == restOB->getCity() && restOB->getIsRestActive() == true && restOB->getIsRestOpen() == true){
                    ORDER tempOrder;
                    custOB->addOrder(tempOrder, restOB->getCode());
                    orderOB = custOB->getNewOrder();
                    ORDERITEM orderItemOB;
                    do{
                        showCuisine(cuisineIndex);
                        cout << "\n\n\tChoice:\t";
                        cin >> cuisineIndex;
                        cin.clear();
                        cin.ignore();
                        if(cuisineIndex >= 0 && cuisineIndex < 12){
                            showCuisine(cuisineIndex);
                            cleanArea(33, 6, 143, 44);
                            gotoxy(1, 7);
                            if(restOB->hasFood(cuisineIndex) == false){
                                //cuisineIndex = -12;
                                goto ORDEREND;
                            } else{
                                restOB->displayRestMenu(cuisineIndex);
                                cout << "\n\n\t\t\t\tItem Code:\t";
                                getline(cin, itemCode);
                                try{
                                    foodIndex = (stoi(itemCode.substr(5, 3)) - 1);
                                } catch(exception& e){
                                    custOB->deleteLastOrder();
                                    setMessage("Invalid Item Code Entered!");
                                    setContinue();
                                    choiceString = choiceString.substr(0, (choiceString.length()-1));
                                    goto MENU;
                                }
                            }
                            if(cuisineIndex == 0){
                                PIZZA * pizzaOB = new PIZZA;
                                pizzaOB = restOB->getPizza(foodIndex);
                                cout << "\n\t\t\t\tSizes Available:\t";
                                for(int i = 0; i < pizzaOB->getSizeLength(); i++){
                                    cout << "\n\t\t\t\t\t" << i << "> " << pizzaOB->getSize(i) << ":\t" << pizzaOB->getPrice(i);
                                    if(i == (pizzaOB->getSizeLength() - 1)){
                                        cout << "\n\t\t\t\tChoice:\t";
                                        cin >> sizeIndex;
                                        cin.clear();//
                                        cin.ignore();//
                                    }
                                }
                            }
                            cout << "\n\t\t\t\tMax Limit:\t" << restOB->getLimit(cuisineIndex, foodIndex) << "\t\tStock Available:\t" << restOB->getStock(cuisineIndex, foodIndex) << "\n\t\t\t\tQuantity:\t";
                            cin >> quantity;
                            cin.clear();
                            cin.ignore();
                            if(quantity <= restOB->getLimit(cuisineIndex, foodIndex) && quantity <= restOB->getStock(cuisineIndex, foodIndex)){
                                if(cuisineIndex == 0){
                                    PIZZA * pizzaOB = new PIZZA;
                                    pizzaOB = restOB->getPizza(foodIndex);
                                    if(pizzaOB->getDiscount() > restOB->getRestDiscount()){
                                        discount = pizzaOB->getDiscount();
                                    } else{
                                        discount = restOB->getRestDiscount();
                                    }
                                    ORDERITEM tempOrderItemOB(0, pizzaOB->getItemCode(), pizzaOB->getTitle(), pizzaOB->getSize(sizeIndex), pizzaOB->getPrice(sizeIndex), discount, pizzaOB->getPrepTime(), quantity);
                                    orderItemOB = tempOrderItemOB;
                                } else{
                                    FOOD * foodOB = new FOOD(cuisineIndex);
                                    if(cuisineIndex == 1){
                                        foodOB = restOB->getBurger(foodIndex);
                                    } else if(cuisineIndex == 2){
                                        foodOB = restOB->getSandwich(foodIndex);
                                    } else if(cuisineIndex == 3){
                                        foodOB = restOB->getFastFood(foodIndex);
                                    } else if(cuisineIndex == 4){
                                        foodOB = restOB->getBarbq(foodIndex);
                                    } else if(cuisineIndex == 5){
                                        foodOB = restOB->getPakistani(foodIndex);
                                    } else if(cuisineIndex == 6){
                                        foodOB = restOB->getChinese(foodIndex);
                                    } else if(cuisineIndex == 7){
                                        foodOB = restOB->getInternational(foodIndex);
                                    } else if(cuisineIndex == 8){
                                        foodOB = restOB->getSeafood(foodIndex);
                                    } else if(cuisineIndex == 9){
                                        foodOB = restOB->getDessert(foodIndex);
                                    } else if(cuisineIndex == 10){
                                        foodOB = restOB->getCake(foodIndex);
                                    } else if(cuisineIndex == 11){
                                        foodOB = restOB->getBeverage(foodIndex);
                                    }
                                    if(foodOB->getDiscount() > restOB->getRestDiscount()){
                                        discount = foodOB->getDiscount();
                                    } else{
                                        discount = restOB->getRestDiscount();
                                    }
                                    ORDERITEM tempOrderItemOB(cuisineIndex, foodOB->getItemCode(), foodOB->getTitle(), "", foodOB->getPrice(), discount, foodOB->getPrepTime(), quantity);
                                    orderItemOB = tempOrderItemOB;
                                }
                                cout << "\n\t\t\t\tEnter \"+\" to add more Items OR \"q\" to Quit OR \"c\" to Confirm:\t";
                                getline(cin, inputItem);
                                if(inputItem[0] == '+'){
                                    orderOB->addOrderItem(orderItemOB);
                                } else if(inputItem[0] == 'c'){
                                    orderOB->addOrderItem(orderItemOB);
                                    if(custOB->getWalletAmount() >= orderOB->getBill()){
                                        orderOB->setIsPaid(true);
                                        orderOB->setDeliveryTime(custOB->getCityInt(), custOB->getAreaInt(), restOB->getAreaInt());
                                        paymentString = custOB->payOrder(restOB->confirmOrder(*orderOB));
                                        if(paymentString == "Insufficient Funds to Pay Delivery Charges!"){
                                            setMessage(paymentString);
                                            restOB->deleteLastOrder();
                                        } else{
                                            setMessage(paymentString);
                                        }
                                    } else{
                                        setMessage("Insufficient Funds to Complete Order! Please Recharge & Reorder.");
                                    }
                                    cuisineIndex = 12;
                                } else if(inputItem[0] == 'q'){
                                    custOB->deleteLastOrder();
                                    cuisineIndex = 12;
                                    setMessage("Exit.");
                                }
                            } else{
                                setMessage("Order Quantity Exceeds Stock/Limit!");
                            }
                        } else{
                            custOB->deleteLastOrder();
                        }
                        ORDEREND:
                        if(cuisineIndex == -1){
                            setMessage("Restaurant does not offer this Cuisine");
                        }
                    } while(cuisineIndex >= 0 && cuisineIndex < 12);
                } else{
                    setMessage("Restaurant: " + restOB->getTitle() + "is Closed now OR it dows not offer service in your City");
                }
            } else{
                setMessage("Invalid Restaurant Code: " + restaurantCode);
            }
        } else{
            setMessage("You Entered Invalid Restaurant Code!");
        }
        setContinue();
        choiceString = choiceString.substr(0, (choiceString.length()-1));
        goto MENU;
        break;

    case 324: // CUST > Sign In > Order Details 
        setTitle("CUSTOMER > Sign In > Order Details");
        cleanArea(2, 6, 143, 44);
        gotoxy(2, 7);
        cout << "\t1> Show All\n\n\t2> Show Order\n\n\t0> Go Back\n\n\t\tChoice:\t";
        getline(cin, inputItem);
        cleanArea(2, 6, 143, 44);
        if(inputItem == "1"){
            setTitle("ORDERS (ALL)");
            gotoxy(2, 7);
            custOB->showAllOrders();
        } else if(inputItem == "2"){
            setTitle("ORDER (CODE)");
            gotoxy(2, 7);
            cout << "\tOrder Number:\t";
            getline(cin, orderNumber);
            if(orderNumber.length() == 10 && orderNumber.substr(0, 3) == restOB->getCode()){
                cleanArea(2, 6, 143, 44);
                setTitle("ORDER (" + orderNumber + ")");
                gotoxy(2, 7);
                custOB->showOrder(orderNumber);
            } else{
                setMessage("Invalid Order Code!");
            }
        } else if(inputItem != "0"){
            setMessage("Invalid Choice!");
        }
        if(inputItem != "0"){
            setContinue();
        }
        choiceString = choiceString.substr(0, (choiceString.length()-1));
        goto MENU;
        break;

    case 325: // CUST > Sign In > Voucher management
        menuIndex = 12;
        goto MENU;
        break;

    case 3251: // CUST > Sign In > Voucher management > show Details
        setTitle("Displaying Voucher Details");
        cleanArea(2, 6, 143, 44);
        gotoxy(1, 7);
        cout << "\t1> Show New Vouchers\n\n\t2> Show Past Vouchers\n\n\tChoice:\t";
        getline(cin, inputItem);
        cleanArea(2, 6, 143, 44);
        gotoxy(1, 7);
        if(inputItem == "1"){
            adminOb.showVouchersCust(custOB->getVoucher());
        }else if(inputItem == "2"){
            adminOb.showVouchersCust(custOB->getVoucherUsed());
        }
        setContinue();
        choiceString = choiceString.substr(0, (choiceString.length()-1));
        goto MENU;
        break;

    case 3252: // CUST > Sign In > Voucher management > Use Vouchers
        setTitle("Recharge Wallet");
        cleanArea(2, 6, 143, 44);
        gotoxy(1, 7);
        cout << "\tVoucher Code:\t";
        getline(cin, inputItem);
        setMessage(custOB->chargeWallet(adminOb.cashVoucher(inputItem), inputItem));
        setContinue();
        choiceString = choiceString.substr(0, (choiceString.length()-1));
        goto MENU;
        break;

    case 10: // ADMIN > Go Back
        menuIndex = 0;
        choiceString = choiceString.substr(0, (choiceString.length()-2));
        goto MENU;
        break;

    case 20: // REST > Go Back
        menuIndex = 0;
        choiceString = choiceString.substr(0, (choiceString.length()-2));
        goto MENU;
        break;

    case 30: // CUST > Go Back
        menuIndex = 0;
        choiceString = choiceString.substr(0, (choiceString.length()-2));
        goto MENU;
        break;

    case 110: // ADMIN > show Details > Go Back
        menuIndex = 1;
        choiceString = choiceString.substr(0, (choiceString.length()-2));
        goto MENU;
        break;
    
    case 120: // ADMIN > Restaurant Management > Go Back
        menuIndex = 1;
        choiceString = choiceString.substr(0, (choiceString.length()-2));
        goto MENU;
        break;
    
    case 130: // ADMIN > Customer Management > Go Back
        menuIndex = 1;
        choiceString = choiceString.substr(0, (choiceString.length()-2));
        goto MENU;
        break;

    case 140: // ADMIN > Voucher >> Go Back
        menuIndex = 1;
        choiceString = choiceString.substr(0, (choiceString.length()-2));
        goto MENU;
        break;

    case 1120: // ADMIN > show Details > Show Restaurant > Go Back 
        menuIndex = 2;
        choiceString = choiceString.substr(0, (choiceString.length()-2));
        goto MENU;
        break;

    case 1130: // ADMIN > show Details > Show Customers > Go Back
        menuIndex = 2;
        choiceString = choiceString.substr(0, (choiceString.length()-2));
        goto MENU;
        break;

    case 260: // REST > Menu management > Go Back
        menuIndex = 7;
        choiceString = choiceString.substr(0, (choiceString.length()-2));
        goto MENU;
        break;

    case 2640: // REST > Menu > Show Details > Go Back
        menuIndex = 8;
        choiceString = choiceString.substr(0, (choiceString.length()-2));
        goto MENU;
        break;

    case 270: // REST > Order Management > Go Back
        menuIndex = 7;
        choiceString = choiceString.substr(0, (choiceString.length()-2));
        goto MENU;
        break;

    case 320: // CUST > Sign In > Go Back
        menuIndex = 10;
        choiceString = choiceString.substr(0, (choiceString.length()-2));
        goto MENU;
        break;

    case 32310: // CUST > Sign In > Order Food > show Restaurant > Go Back
        menuIndex = 15;
        choiceString = choiceString.substr(0, (choiceString.length()-2));
        goto MENU;
        break;

    case 3230: // CUST > Sign In > Order Food > Go Back 
        menuIndex = 11;
        choiceString = choiceString.substr(0, (choiceString.length()-2));
        goto MENU;
        break;
    
    case 3250: // CUST > Sign In > Voucher Management > Go Back
        menuIndex = 11;
        choiceString = choiceString.substr(0, (choiceString.length()-2));
        goto MENU;
        break;

    case 121: // ADMIN > Restaurant Management > Add New
        setTitle("ADMINISTRATOR > Restaurant Management > Add New");
        do{
            cleanArea(2, 6, 143, 44);
            gotoxy(1, 7);
            cout << "\tManager ID:\t\t";
            getline(cin, managerID);
            cout << "\tManager Password:\t";
            hideInput(true);
            getline(cin, managerPassword);
            cout << string(managerPassword.length(), '*');
            hideInput(false);
        }while(managerID.length() == 0 || managerPassword.length() == 0 || adminOb.checkManager(managerID) != -1);
        cout << "\n\tCities:\n";
        for(int i = 0; i < cities.size(); i++){
            cout << "\t\t" << i << ") " << cities[i][0] << endl;
        }
        cout << "\tChoice:\t";
        try{
            cin >> city;
            cin.clear();
            cin.ignore();
            if(city < 0 && city > 4){
                throw "Invalid City Entered"; 
            }    
        } catch(const char* msg){
            setMessage(msg);
            setContinue();
            choiceString = choiceString.substr(0, (choiceString.length()-1));
            goto MENU;
        }
        cout << "\n\tArea:\n";
        for(int i = 1; i < cities[city].size(); i++){
            cout << "\t\t" << i << ") " << cities[city][i] << endl;
        }
        cout << "\tChoice:\t";
        try{
            cin >> area;
            cin.clear();
            cin.ignore();
            if(area <= 0){
                throw "Invalid Area Entered!";
            }
        } catch(const char* msg){
            setMessage(msg);
            setContinue();
            choiceString = choiceString.substr(0, (choiceString.length()-1));
            goto MENU;
        }
        cout << "\n\tAddress:\n\tRestaurant Title:\n\tRestaurant Description:\n\tContact Number:\n\tOpening Time:\n\tClosing Time:\n\tDiscount Percentage:";
        gotoxy(1, getY()-6);
        for(int i = 1; i < 8; i++){
            cout << "\t\t\t\t  ";
            getline(cin, inputItem);
            inputItems = inputItems + inputItem + ";";
        }
        cout << "\tDo you offer Free Delivery (y/n):\t";
        if(getche() == 'y'){
            inputItems = inputItems + "1;";
            cout << "\n\tMinimum Order for Free Delivery:\t";
            getline(cin, inputItem);
            inputItems = inputItems + inputItem + ";";
            if(stoi(inputItem) > 0){
                cout << "\tDelivery Charges for Orders less than " << inputItem << ":\t";
                getline(cin, inputItem);
                inputItems = inputItems + inputItem;
            } else{
                inputItems = inputItems + "0";
            }
        } else{
            inputItems = inputItems + "0" + ";";
            inputItems = inputItems + "0" + ";";
            cout << "\n\tDelivery Charges:\t";
            getline(cin, inputItem);
            inputItems = inputItems + inputItem;
        }
        ss.str(inputItems);
        getline(ss, address, ';');
        getline(ss, title, ';');
        getline(ss, description, ';');
        getline(ss, contactNumber, ';');
        getline(ss, openTime, ';');
        getline(ss, closeTime, ';');
        getline(ss, restDiscount, ';');
        getline(ss, freeDelivery, ';');
        getline(ss, minimumOrder, ';');
        getline(ss, deliveryCharges, ';');
        try{
            RESTAURANT restOb(managerID, managerPassword, stoi(openTime), stoi(closeTime), title, description, contactNumber, address, area, city, stoi(freeDelivery), stod(minimumOrder), stod(deliveryCharges), stod(restDiscount));
            adminOb.addRestaurant(restOb);
            setMessage("Restaurant Added Succesfully! ");
        } catch(exception &e){
            setMessage("Invalid Data Entered!");
        }
        inputItems = "";
        ss.clear();
        choiceString = choiceString.substr(0, (choiceString.length()-1));
        goto MENU;
        break;

    case 1121: // ADMIN > Show Details > Show Restaurants > Show All  
        cleanArea(2, 6, 143, 44);
        setTitle("RESTAURANTS (ALL)");
        gotoxy(2, 7);
        adminOb.showRestaurants();
        setContinue();
        choiceString = choiceString.substr(0, (choiceString.length()-1));
        goto MENU;
        break;

    case 1131: // ADMIN > Show Details > Customer > show All
        cleanArea(2, 6, 143, 44);
        setTitle("CUSTOMERS (ALL)");
        gotoxy(2, 7);
        adminOb.showCustomer();
        setContinue();
        choiceString = choiceString.substr(0, (choiceString.length()-1));
        goto MENU;
        break;
    
    case 111: // ADMIN > Show Details > Summary
        cleanArea(2, 6, 143, 44);
        setTitle("Summary");
        gotoxy(2, 7);
        adminOb.showSummary();
        setContinue();
        choiceString = choiceString.substr(0, (choiceString.length()-1));
        goto MENU;
        break;
    
    case 1122: //ADMIN> Show Details > Show Restaurants > By Cuisine
        cleanArea(2, 6, 143, 44);
        setTitle("ADMINISTRATOR > Show Details > Show Restaurants > By Cuisine");
        gotoxy(2, 7);
        for(int i = 0; i < cuisineTitle.size(); i++){
            cout << "\t" << (i + 1) << "> " << cuisineTitle[i] << "\n" << endl;
        }
        cout << "\t0> Go Back\n\n\tChoice: ";
        getline(cin, inputItem);
        inputItem = to_string(stoi(inputItem) - 1);
        setTitle("RESTAURANTS {" + cuisineTitle[stoi(inputItem)] + "}");
        gotoxy(2, 7);
        if(inputItem != "-1"){
            cleanArea(2, 6, 143, 44);
            gotoxy(3, 7);
            adminOb.showRestWithCuisine(cuisineTitle[stoi(inputItem)]);
        } else{
            setMessage("Invalid Cuisine!");
        }
        setContinue();
        choiceString = choiceString.substr(0, (choiceString.length()-1));
        goto MENU;
        break;
    
    case 1123: // ADMIN > Show Details > Show Restaurants > By Location
        cleanArea(2, 6, 143, 44);
        setTitle("ADMINISTRATOR > Show Details > Show Restaurants > By Location");
        gotoxy(2, 7);
        for(int i = 0; i < cities.size(); i++){
            cout << "\t" << (i + 1) << "> " << cities[i][0] << "\n" << endl;
        }
        cout << "\t0> Go Back\n\n\tChoice: ";
        cin >> city;
        cin.clear();//
        cin.ignore();//
        city--;
        if(city >= 0 && city < 5){
            cleanArea(2, 6, 143, 44);
            gotoxy(4, 7);
            for(int i = 1; i < cities[city].size(); i++){
                cout << "\t" << i << "> " << cities[city][i] << "\n" << endl;
            }
            cout << "\t0> Go Back\n\n\tChoice: ";
            cin >> area;
            if(area > 0 && area < cities[city].size()){
                cleanArea(2, 6, 143, 44);
                gotoxy(3, 7);
                adminOb.showRestOnLocation(city, area);
            } else{
                setMessage("Invalid Area!");
            }
        } else{
            setMessage("Invalid City!");
        }
        cin.clear();
        cin.ignore();
        setContinue();
        choiceString = choiceString.substr(0, (choiceString.length()-1));
        goto MENU;
        break;

    case 1132: // ADMIN > Show Details > Show Customers > By Location
        cleanArea(2, 6, 143, 44);
        setTitle("ADMINISTRATOR > Show Details > Show Customers > By Location");
        gotoxy(2, 7);
        for(int i = 0; i < cities.size(); i++){
            cout << "\t" << (i + 1) << "> " << cities[i][0] << "\n" << endl;
        }
        cout << "\t0> Go Back\n\n\tChoice: ";
        cin >> city;
        cin.clear();//
        cin.ignore();//
        city--;
        if(city >= 0 && city < 5){
            cleanArea(2, 6, 143, 44);
            gotoxy(4, 7);
            for(int i = 1; i < cities[city].size(); i++){
                cout << "\t" << i << "> " << cities[city][i] << "\n" << endl;
            }
            cout << "\t0> Go Back\n\n\tChoice: ";
            cin >> area;
            if(area > 0 && area < cities[city].size()){
                cleanArea(2, 6, 143, 44);
                setTitle("CUSTOMERS @" + cities[city][0] + ": " + cities[city][area]);
                gotoxy(3, 7);
                adminOb.showCustOnLocation(city, area);
            } else{
                setMessage("Invalid Area! ");
            }
        } else{
            setMessage("Invalid City! ");
        }
        cin.clear();
        cin.ignore();
        setContinue();
        choiceString = choiceString.substr(0, (choiceString.length()-1));
        goto MENU;
        break;

    case 122: // ADMIN > Restaurant Management > Close
        cleanArea(2, 6, 143, 44);
        setTitle("ADMINISTRATOR > Restaurant Management > Close");
        gotoxy(2, 7);
        cout << "\tManager ID:\t";
        getline(cin, inputItem);
        setMessage(adminOb.removeRestaurant(inputItem));
        choiceString = choiceString.substr(0, (choiceString.length()-1));
        goto MENU;
        break;

    case 132: //ADMIN > Customer Management > Block
        cleanArea(2, 6, 143, 44);
        setTitle("ADMINISTRATOR > Customer Management > Block");
        gotoxy(1, 7);
        cout << "\tCustomer Email Address:\t";
        getline(cin, inputItem);
        setMessage(adminOb.removeCustomer(inputItem));
        choiceString = choiceString.substr(0, (choiceString.length()-1));
        goto MENU;
        break;

    case 123: // ADMIN > Restaurant Management > Re-Open
        cleanArea(2, 6, 143, 44);
        setTitle("ADMINISTRATOR > Restaurant Management > Re-Open");
        gotoxy(2, 7);
        cout << "\tManager ID:\t";
        getline(cin, inputItem);
        setMessage(adminOb.reOpenRestaurant(inputItem));
        choiceString = choiceString.substr(0, (choiceString.length()-1));
        goto MENU;
        break;

    case 133: // ADMIN > Customer Management > Unblock
        cleanArea(2, 6, 143, 44);
        setTitle("ADMINISTRATOR > Customer Management > Unblock");
        gotoxy(2, 7);
        cout << "\tCustomer Email Address:\t";
        getline(cin, inputItem);
        setMessage(adminOb.activateCustomer(inputItem));
        choiceString = choiceString.substr(0, (choiceString.length()-1));
        goto MENU;
        break;
    
    case 124: // ADMIN > Restaurant Management > Find
        cleanArea(2, 6, 143, 44);
        setTitle("ADMINISTRATOR > Restaurant Management > Find");
        gotoxy(2, 7);
        cout << "\t1> Manager ID\n\n\t2> Restaurant Code\n\n\t3> Restaurant Title\n\n\t0> Go Back\n\n\t Choice: ";
        getline(cin, inputItem);
        cleanArea(2, 6, 143, 44);
        if(inputItem == "1"){
            setTitle("ADMINISTRATOR > Restaurant Management > Find > Manager ID");
            gotoxy(2, 7);
            cout << "\tManager ID:\t";
            getline(cin, inputItemSub);
            cleanArea(2, 6, 143, 44);
            gotoxy(2, 7);
            adminOb.findRestWithManager(inputItemSub);
            //setContinue();
        } else if(inputItem == "2"){
            setTitle("ADMINISTRATOR > Restaurant Management > Find > Restaurant Code");
            gotoxy(2, 7);
            cout << "\tRestaurant Code:\t";
            getline(cin, inputItem);
            cleanArea(2, 6, 143, 44);
            if((stoi(inputItem) > 0) && (stoi(inputItem) <= adminOb.getRestaurantSize())){
                gotoxy(2, 7);
                adminOb.showRestaurants(stoi(inputItem) - 1);
                setMessage("Restaurant Found!");
            } else{
                setMessage("Restaurant with Code " + inputItem + " Not Found!");
            }
        } else if(inputItem == "3"){
            setTitle("ADMINISTRATOR > Restaurant Management > Find > Restaurant Code");
            gotoxy(2, 7);
            cout << "\tRestaurant Title:\t";
            getline(cin, inputItem);
            cleanArea(2, 6, 143, 44);
            gotoxy(1, 7);
            adminOb.showRestaurants(inputItem);
        }
        if(inputItem != "0"){
            setContinue();
        }
        choiceString = choiceString.substr(0, (choiceString.length()-1));
        goto MENU;
        break;

    case 125: // ADMIN > Restaurant Management > Receive Revenue 
        setMessage(adminOb.receiveRevenue());
        setContinue();
        choiceString = choiceString.substr(0, (choiceString.length()-1));
        goto MENU;
        break;

    case 134: // ADMIN > Customer Management > Find
        cleanArea(2, 6, 143, 44);
        setTitle("ADMINISTRATOR > Customer Management > Find");
        gotoxy(2, 7);
        cout << "\t1> Customer Code\n\n\t2> Email Address\n\n\t3> Contact Number\n\n\t0> Go Back\n\n\t Choice: ";
        getline(cin, inputItem);
        cleanArea(2, 6, 143, 44);
        gotoxy(2, 7);
        if(inputItem == "1"){
            cout << "\tCustomer Code:\t";
            getline(cin, inputItem);
            if((stoi(inputItem) > 0) && (stoi(inputItem) <= adminOb.getCustomerSize())){
                setMessage("Customer Found!");
                cleanArea(2, 6, 143, 44);
                setTitle("CUSTOMER: " + inputItem);
                gotoxy(2, 7);
                adminOb.showCustomer(inputItem);
            } else{
                setMessage("Customer with Code " + inputItem + " Not Found!");
            }
        } else if(inputItem == "2"){
            cout << "\tEmail Address:\t";
            getline(cin, inputItem);
            cleanArea(2, 6, 143, 44);
            setTitle("CUSTOMER: " + inputItem);
            gotoxy(2, 7);
            adminOb.showCustomerByEmail(inputItem);
        } else if(inputItem == "3"){
            cout << "\tContact Number:\t";
            getline(cin, inputItem);
            cleanArea(2, 6, 143, 44);
            setTitle("CUSTOMER: " + inputItem);
            gotoxy(2, 7);
            adminOb.showCustomerByContact(inputItem);
        }
        if(inputItem != "0"){
            setContinue();
        }
        choiceString = choiceString.substr(0, (choiceString.length()-1));
        goto MENU;
        break;

    case 131: //ADMIN > Customer Management > Add New
        setTitle("ADMINISTRATOR > Customer Management > Add New");
        do{
            cleanArea(2, 6, 143, 44);
            gotoxy(2, 7);
            cout << "\tEmail Address:\t";
            getline(cin, emailAddress);
            cout << "\tContact Number:\t";
            getline(cin, contactNumber);
        }while(adminOb.checkCustomer(emailAddress, contactNumber) != -1);
        cout << "\n\tCities:\n";
        for(int i = 0; i < cities.size(); i++){
            cout << "\t\t" << i << ") " << cities[i][0] << endl;
        }
        cout << "\tChoice:\t\t";
        try{
            cin >> city;
            cin.clear();
            cin.ignore();
            if(city < 0 && city > 4){
                throw "Invalid City Entered"; 
            }    
        } catch(const char* msg){
            setMessage(msg);
            setContinue();
            choiceString = choiceString.substr(0, (choiceString.length()-1));
            goto MENU;
        }
        cout << "\n\tArea:\n";
        for(int i = 1; i < cities[city].size(); i++){
            cout << "\t\t" << i << ") " << cities[city][i] << endl;
        }
        cout << "\tChoice:\t\t";
        try{
            cin >> area;
            cin.clear();
            cin.ignore();
            if(area <= 0){
                throw "Invalid Area Entered!";
            }
        } catch(const char* msg){
            setMessage(msg);
            setContinue();
            choiceString = choiceString.substr(0, (choiceString.length()-1));
            goto MENU;
        }
        cout << "\n\tAddress:\t";
        getline(cin, address);
        cout << "\n\tFirst Name:\t";
        getline(cin, firstName);
        cout << "\n\tLast Name:\t";
        getline(cin, lastName);
        cout << "\n\tPassword:\t";
        hideInput(true);
        getline(cin, passWord);
        cout << string(passWord.length(), '*');
        hideInput(false);
        if(emailAddress.length() != 0 && contactNumber.length() != 0 && passWord.length() != 0 && (city >= 0 && city < 6) && (area > 0 && area <= cities[city].size())){
            CUSTOMER custOb(firstName, lastName, passWord, emailAddress, contactNumber, address, area, city);
            adminOb.addCustomer(custOb);
            setMessage("New Customer Registered Successfuly!");
        } else{
            setMessage("New Customer Registeration Unsuccessful!");
        }
        setContinue();
        choiceString = choiceString.substr(0, (choiceString.length()-1));
        goto MENU;
        break;

    case 0: // Exit
        system("exit");
        break;

    default:
        break;
    }
    
    gotoxy(20, 20);
    system("pause");
    return 0;
}

void cleanArea(int _x1, int _y1, int _x2, int _y2){
    for(int i = _y1; i <= _y2; i++){
        gotoxy(_x1, _y1++);
        cout << string((_x2 - _x1 + 1), ' ') << endl;
    }
}

void clearMain(){
    cleanArea(1, 6, 144, 44);
    gotoxy(1, 7);
}


template<class T> void setMessage(T message){
    cout << boolalpha << fixed << setprecision(2);
    cleanArea(12, 46, 143, 46);
    gotoxy(12, 46);
    cout << message;
}

void setContinue(){
    gotoxy(110, 46);
    system("pause");
    setMessage("");
}

void setTitle(string message){
    cleanArea(2, 4, 143, 4);
    gotoxy(73-message.length()/2, 4);
    cout << message;
}

void showCuisine(int _index){
    cleanArea(2, 6, 143, 44);
    gotoxy(2,7);
    cout << "\t" << char(218) << string(2, char(196)) << char(194) << string(14, char(196)) << char(191) << "\n\t" << char(179) << "C#" << char(179) << setw(14) << "CUISINES   " << char(179);
    for(int i = 0; i < cuisineTitle.size(); i++){
        cout << "\n\t" << char(195) << string(2, char(196)) << char(197) << string(14, char(196)) << char(180) << "\n\t" << char(179) << setw(2) << i << char(179) << setw(14) << cuisineTitle[i] << char(179);
        if(_index == i){
            cout << "  " << char(254);
        }
    }
    cout << "\n\t" << char(192) << string(2, char(196)) << char(193) << string(14, char(196)) << char(217);
}