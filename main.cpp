#include <iostream>
#include "Common.h"
#include "Home.h"
#include "FoodDelivery.h"
#include "AfterOrdering.h"
#include "Etc.h"

string Common::response = "";
string Common::username = "";
bool Common::sign_up_status = false;
int Common::deposit = 0;
int FoodDelivery::total_price = 0;

int main() {
	Common::login();
	Home home;
}