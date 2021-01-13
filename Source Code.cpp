#include<iostream>
#include <ctime>
#include<string>
#include <vector>
#define INT_MAX 10000000

using namespace std;
const int Main_Menu = 1, Admin_Panel = 2, QUIT = 3;

// node for a food item
class foodItem
{
public:
	string itemName;             // name of food item/dish
	float price;                 // price of food item
	int quantity;                // quantity of food item
	int itemNum;                 // serial number of food item
	foodItem* next;              // next pointer to point next food item in list
};

//node for a food order containing details of an order
struct orderDetails
{
	string CustomerName;            // name of customer 
	string creditCardNum;           // credit card number of customer
	string orderDate, orderTime;    // date and time of a food order
	float totalBill;                // total bill of an order
	int orderNum;                   // indication of which order is it
	orderDetails* next;             // next pointer to point to next order in list
};

//////////////   Main Menu class   //////////////
class main_menu
{
private:
	foodItem* head;
	int key;                   // key is used to keep trace of number of items
public:
	//	    constructor to initialize the values
	main_menu()
	{
		head = NULL;
		key = 0;
	}
	//      function to add a food item in menu
	virtual void insert_item(string n, int q, float p)
	{
		foodItem* newItem = new foodItem;
		newItem->itemName = n;
		newItem->price = p;
		newItem->quantity = q;
		newItem->next = NULL;
		key++;
		newItem->itemNum = key;
		// if there's no food item in menu, make this item as first
		if (head == NULL)
		{
			head = newItem;
		}
		//otherwise, add this item at the end of the main menu
		else
		{
			foodItem* item_ptr = head;
			while (item_ptr->next != NULL)
			{
				item_ptr = item_ptr->next;
			}
			item_ptr->next = newItem;
		}
	}
	//		function to delete any food item from menu
	void delete_item(int n)
	{
		foodItem* item_ptr = head;
		foodItem* prev_ptr = NULL;
		// if the item to be deleted is the first item of menu
		if (item_ptr->itemNum == n)
		{
			head = head->next;
			delete item_ptr;
		}
		//otherwise, search it in menu
		else
		{
			// keep on traversing till the food item to be deleted is not found, 
			// and if the item to be deleted is not in menu, traverse till end of menu
			while (item_ptr->next && item_ptr->itemNum != n)
			{
				prev_ptr = item_ptr;
				item_ptr = item_ptr->next;
			}
			prev_ptr->next = item_ptr->next;
			delete item_ptr;
		}
	}
	//		function to search the item in menu when order is being placed by customer 
	//      and return the whole item node
	foodItem* search_item(int serial_num, int q)
	{
		foodItem* item_ptr = new foodItem;
		item_ptr = head;
		while (item_ptr->itemNum != serial_num && item_ptr->next != NULL)
		{
			item_ptr = item_ptr->next;
		}
		item_ptr->quantity -= q;
		return item_ptr;
	}
	//		function to display the main menu
	void display_list()
	{
		foodItem* item_ptr = head;
		cout << endl << endl << "                        MAIN MENU" << endl << endl;
		cout << "   Item No.     |" << "     Name          |" << "     Quantity    |" << "     Price    |" << endl;
		for (int i = 1; i <= key; i++)
		{
			cout << "       " << item_ptr->itemNum << "        |    " << item_ptr->itemName << "  |       " << item_ptr->quantity << "        |    " << item_ptr->price << "       | " << endl;
			item_ptr = item_ptr->next;
		}
	}
	//		destructor to delete main menu
	~main_menu()
	{
		delete head;
	}
};

//////////////   order list(made by customer) class   //////////////
class order_list
{
private:
	foodItem* head;
	float total_cost;            // storing total bill of an order
	int key;                     // key is used to keep trace of number of items
public:
	//		constructor to initialize the values
	order_list()
	{
		head = NULL;
		total_cost = 0.0;
		key = 0;
	}
	//		function to add the food item in customer's order list
	void add_item(string name, int q, float price)
	{
		foodItem* newItem = new foodItem;
		newItem->itemName = name;
		newItem->price = price;
		newItem->quantity = q;
		newItem->next = NULL;
		key++;
		newItem->itemNum = key;
		// if there's nothing in order list
		if (head == NULL)
		{
			head = newItem;
		}
		// otherwise, add the food item att end of order list
		else
		{
			foodItem* item_ptr = head;
			while (item_ptr->next != NULL)
			{
				item_ptr = item_ptr->next;
			}
			item_ptr->next = newItem;
		}
		// increase the total bill everytime a need food item is added in list
		total_cost += ((newItem->price) * (newItem->quantity));
	}
	//		function to delete food item from order list 
	void delete_item(int n)
	{
		foodItem* item_ptr = head;
		foodItem* prev_ptr = NULL;
		if (item_ptr->itemNum == n)
		{
			total_cost -= ((head->price) * (head->quantity));
			head = head->next;
			delete item_ptr;
		}
		else
		{
			while (item_ptr->next && item_ptr->itemNum != n)
			{
				prev_ptr = item_ptr;
				item_ptr = item_ptr->next;
			}
			total_cost -= ((item_ptr->price) * (item_ptr->quantity));
			prev_ptr->next = item_ptr->next;
			delete item_ptr;
		}
	}
	//		function to display the order list
	void display_order()
	{
		foodItem* item_ptr = head;
		cout << "   Item No.     |" << "     Name          |" << "     Quantity    |" << "     Price    |" << endl;
		while (item_ptr)
		{
			cout << "       " << item_ptr->itemNum << "        |    " << item_ptr->itemName << "  |       ";
			cout << item_ptr->quantity << "         |    " << (item_ptr->price) * (item_ptr->quantity) << "       | " << endl;
			item_ptr = item_ptr->next;
		}
	}
	//		function that return the total bill of the order being made
	float Total_bill()
	{
		return total_cost;
	}
	//		function to delete the whole order list
	void delete_order()
	{
		foodItem* item_ptr;
		while(head != NULL)
		{
			item_ptr = head->next;
			delete head;
			head = item_ptr;
		}
		head = NULL;
		key = 0;
		total_cost = 0;
	}
};

//////////    class to keep the all orders record   ////////////
class orders_history
{
private:
	orderDetails* head;
	int key;
public:
	//		constructor to set values
	orders_history()
	{
		head = NULL;
		key = 0;
	}
	//		function to add an order details in orders_history record
	void add_order_details(string customer_name, string credit_cardNum, float bill, string date, string time)
	{
		orderDetails* New_order = new orderDetails;
		New_order->CustomerName = customer_name;
		New_order->creditCardNum = credit_cardNum;
		New_order->totalBill = bill;
		New_order->orderDate = date;
		New_order->orderTime = time;
		New_order->next = NULL;
		key++;
		New_order->orderNum = key;
		//			if there is no order in record orders history
		if (head == NULL)
		{
			head = New_order;
		}
		//			otherwise, add the order details at end of orders_history list
		else
		{
			orderDetails* order_ptr = head;
			while (order_ptr->next != NULL)
			{
				order_ptr = order_ptr->next;
			}
			order_ptr->next = New_order;
		}
	}
	//      function to display orders_history
	void display_ordersHistory()
	{
		orderDetails* order_ptr = head;
		cout << endl << endl << "                                                       __Order History__" << endl << endl;
		cout << "     Order No.    |      Name      |    Credit Card Num.    |     Bill     |     Date     |     Time     |" << endl;
		while (order_ptr)
		{
			cout << "        " << order_ptr->orderNum << "         |  " << order_ptr->CustomerName << "   |    " << order_ptr->creditCardNum;
			cout << "    |     " << order_ptr->totalBill << "      |  " << order_ptr->orderDate << " |   " << order_ptr->orderTime << "   |" << endl;
			order_ptr = order_ptr->next;
		}
	}
};

///////////   function to display Admin panel   ////////////
void display_admin_panel()
{
	cout << endl << endl << "                        ADMIN PANEL" << endl << endl;
	cout << "                       1- ADD FOOD ITEM\n                       2- REMOVE FOOD ITEM\n";
	cout << "                       3- TOTAL EARNING\n                       4- ORDERS History\n";
	cout << "                       5- CHANGE PASSWORD\n" << endl;
}

////////////   dijikstra algorithm starts   /////////////
class Node;
class Edge;

// functions definition
void Dijkstras();
vector<Node*>* AdjacentRemainingNodes(Node* node);
Node* ExtractSmallest(vector<Node*>& nodes);
int Distance(Node* node1, Node* node2);
bool Contains(vector<Node*>& nodes, Node* node);
int ShortestRouteTo(Node* destination);

// array of node and edge lists
vector<Node*> nodes;
vector<Edge*> edges;

/////////////   node/vertex class   ////////////
class Node
{
public:
	char id;
	Node* previous;
	int distanceFromStart;
	Node(char id) : id(id), previous(NULL), distanceFromStart(INT_MAX)
	{
		nodes.push_back(this);
	}
};

/////////////   node/vertex class   ////////////
class Edge {
public:
	Node* node1;
	Node* node2;
	int distance;
	Edge(Node* node1, Node* node2, int distance) : node1(node1), node2(node2), distance(distance)
	{
		edges.push_back(this);
	}
	bool Connects(Node* node1, Node* node2)
	{
		return ((node1 == this->node1 && node2 == this->node2) || (node1 == this->node2 && node2 == this->node1));
	}
};

//////////   main dijkstras algorithm   //////////// 
int DijkstrasMain(string desti)
{
	// making spots/nodes where food order can be delivered
	Node* I9_food_center = new Node('a');
	Node* I9_1 = new Node('b');
	Node* I9_2 = new Node('c');
	Node* I9_3 = new Node('d');
	Node* I9_4 = new Node('e');
	Node* I8_1 = new Node('f');
	Node* I8_2 = new Node('g');
	Node* I8_3 = new Node('h');
	Node* I8_4 = new Node('i');
	Node* I10_1 = new Node('j');
	Node* I10_2 = new Node('e');
	Node* I10_3 = new Node('k');
	Node* I10_4 = new Node('l');

	// creating weighted edges between vertices/spots
	Edge* e1 = new Edge(I9_food_center, I9_1, 3000);
	Edge* e2 = new Edge(I9_food_center, I9_2, 3000);
	Edge* e3 = new Edge(I9_food_center, I9_3, 3000);
	Edge* e4 = new Edge(I9_food_center, I9_4, 3000);
	Edge* e5 = new Edge(I9_3, I9_2, 5000);
	Edge* e6 = new Edge(I9_4, I9_1, 5000);
	Edge* e7 = new Edge(I9_3, I9_4, 2000);
	Edge* e8 = new Edge(I9_3, I8_2, 4000);
	Edge* e9 = new Edge(I9_4, I8_1, 4000);
	Edge* e10 = new Edge(I8_2, I8_1, 2000);
	Edge* e11 = new Edge(I8_2, I8_3, 5000);
	Edge* e12 = new Edge(I8_1, I8_4, 5000);
	Edge* e13 = new Edge(I8_4, I8_3, 2000);
	Edge* e14 = new Edge(I9_2, I9_1, 2000);
	Edge* e15 = new Edge(I9_2, I10_3, 4000);
	Edge* e16 = new Edge(I9_1, I10_4, 4000);
	Edge* e17 = new Edge(I10_3, I10_4, 2000);
	Edge* e18 = new Edge(I10_3, I10_2, 5000);
	Edge* e19 = new Edge(I10_4, I10_1, 5000);
	Edge* e20 = new Edge(I10_1, I10_2, 2000);

	// setting distance of main food center to itself=0
	I9_food_center->distanceFromStart = 0;
	Dijkstras();
	int dist = 0;
	// checking which node/delivery spot user had entered,
	// and calculating its shortest distance from the food center
	if (desti == "I_9/1")
	{
		dist = ShortestRouteTo(I9_1);
	}
	if (desti == "I_9/2")
	{
		dist = ShortestRouteTo(I9_2);
	}
	if (desti == "I_9/3")
	{
		dist = ShortestRouteTo(I9_3);
	}
	if (desti == "I_9/4")
	{
		dist = ShortestRouteTo(I9_4);
	}
	if (desti == "I_8/1")
	{
		dist = ShortestRouteTo(I8_1);
	}
	if (desti == "I_8/2")
	{
		dist = ShortestRouteTo(I8_2);
	}
	if (desti == "I_8/3")
	{
		dist = ShortestRouteTo(I8_3);
	}
	if (desti == "I_8/4")
	{
		dist = ShortestRouteTo(I8_4);
	}
	if (desti == "I_10/1")
	{
		dist = ShortestRouteTo(I10_1);
	}
	if (desti == "I_10/2")
	{
		dist = ShortestRouteTo(I10_2);
	}
	if (desti == "I_10/3")
	{
		dist = ShortestRouteTo(I10_3);
	}
	if (desti == "I_10/4")
	{
		dist = ShortestRouteTo(I10_4);
	}

	return dist;
}
// function to return the shortest distance between the node(delivery spot) customer entered and the food center
int ShortestRouteTo(Node* destination)
{
	Node* previous = destination;
	return destination->distanceFromStart;
}

///////////////////

void Dijkstras()
{
	while (nodes.size() > 0)
	{
		Node* smallest = ExtractSmallest(nodes);
		vector<Node*>* adjacentNodes = AdjacentRemainingNodes(smallest);

		const int size = adjacentNodes->size();
		for (int i = 0; i < size; ++i)
		{
			Node* adjacent = adjacentNodes->at(i);
			int distance = Distance(smallest, adjacent) + smallest->distanceFromStart;
			if (distance < adjacent->distanceFromStart)
			{
				adjacent->distanceFromStart = distance;
				adjacent->previous = smallest;
			}
		}
		delete adjacentNodes;
	}
}

// Find the node with the smallest distance,
// remove it, and return it.
Node* ExtractSmallest(vector<Node*>& nodes)
{
	int size = nodes.size();
	if (size == 0) return NULL;
	int smallestPosition = 0;
	Node* smallest = nodes.at(0);
	for (int i = 1; i < size; ++i)
	{
		Node* current = nodes.at(i);
		if (current->distanceFromStart < smallest->distanceFromStart)
		{
			smallest = current;
			smallestPosition = i;
		}
	}
	nodes.erase(nodes.begin() + smallestPosition);
	return smallest;
}

// Return all nodes adjacent to 'node' which are still in the 'nodes' collection.
vector<Node*>* AdjacentRemainingNodes(Node* node)
{
	vector<Node*>* adjacentNodes = new vector<Node*>();
	const int size = edges.size();
	for (int i = 0; i < size; ++i)
	{
		Edge* edge = edges.at(i);
		Node* adjacent = NULL;
		if (edge->node1 == node)
		{
			adjacent = edge->node2;
		}
		else if (edge->node2 == node)
		{
			adjacent = edge->node1;
		}
		if (adjacent && Contains(nodes, adjacent))
		{
			adjacentNodes->push_back(adjacent);
		}
	}
	return adjacentNodes;
}

// Return distance between two respective nodes 
int Distance(Node* node1, Node* node2)
{
	const int size = edges.size();
	for (int i = 0; i < size; ++i)
	{
		Edge* edge = edges.at(i);
		if (edge->Connects(node1, node2))
		{
			return edge->distance;
		}
	}
	return -1;  // should never happen
}

// function to check if the respective nodes are present in 'nodes' vector or not
bool Contains(vector<Node*>& nodes, Node* node)
{
	const int size = nodes.size();
	for (int i = 0; i < size; ++i)
	{
		if (node == nodes.at(i))
		{
			return true;
		}
	}
	return false;
}

//  dijikstra algorithm ends

int main()
{
	int choice, back_main = 0, back_admin = 0, choice_admin, serial_num, quantity, total_cash_earned = 0.0;
	string user_name, password = "1234", new_password, password_entered, food_item_name, order_changes, add_or_del_item_in_order;
	float price, bill;
	main_menu menu;
	order_list orderList;
	orders_history orderHistory;
	menu.insert_item("Biryani      ", 23, 150.00);
	menu.insert_item("Pizza        ", 15, 600.00);
	menu.insert_item("Zinger Burger", 15, 100.00);
	menu.insert_item("Roll Paratha ", 20, 200.00);
	menu.insert_item("Macroni      ", 25, 120.00);
	menu.insert_item("CocaCola     ", 50, 050.00);
	menu.insert_item("Sprite       ", 50, 050.00);

	//  main loop....iterate until customer wants to quit 
	while (back_main != 1)
	{
		//		food delivery app(FOOD EXPRESS) interface
		cout << "\n\n\n ----------------------------------------------------------------------\n";
		cout << "                              FOOD EXPRESS " << endl << endl;
		cout << "                          1)- MAIN MENU" << endl;
		cout << "                          2)- ADMIN PANEL" << endl;
		cout << "                          3)- QUIT" << endl;
		cout << "\n ----------------------------------------------------------------------\n";
		//		asking user to select any of three options from main
		cout << endl << "  Press any number between 1 to 3 to access the respective panel: ";
		cin >> choice;

		////	if user selects the main menu....  ////
		if (choice == Main_Menu)
		{
			menu.display_list();               //displaying main menu of items baing served
			cout << "\n\n\n                     Place your order here(enter 0 to finish your order): \n\n";
			//			keep on taking the order untill the user enters 0 for both serial num, and quantity of item
			do
			{
				cout << "                           Serial number of food: ";
				cin >> serial_num;
				cout << "                           Quantity: ";
				cin >> quantity;
				//				search the item from main menu class and pass it to order list class to add that item in user order
				if (serial_num != 0)
				{
					foodItem* Item = new foodItem;
					Item = menu.search_item(serial_num, quantity);
					orderList.add_item(Item->itemName, quantity, Item->price);
				}
			} while (serial_num != 0);
			//			ask user if he/she wants to make changes to his order
			cout << "\n  Do you want to make changes to your order?(yes or no) : ";
			cin >> order_changes;
			//			if user wants to change order
			if (order_changes == "yes")
			{
				//				keep on asking and making changes until he says no
				do
				{
					cout << "\n  Want to Add any item or Delete any item?(add or del): ";
					cin >> add_or_del_item_in_order;
					//					t add any item to user's list 
					if (add_or_del_item_in_order == "add")
					{
						cout << "                           Serial number of food: ";
						cin >> serial_num;
						cout << "                           Quantity: ";
						cin >> quantity;
						foodItem* Item = new foodItem;
						Item = menu.search_item(serial_num, quantity);
						orderList.add_item(Item->itemName, quantity, Item->price);
					}
					//					to delete any item from order
					if (add_or_del_item_in_order == "del")
					{
						cout << "  Enter Serial Number: "; cin >> serial_num;
						orderList.delete_item(serial_num);
					}
					cout << "  Do you want to make further changes in your order(yes/no): ";
					cin >> order_changes;
				} while (order_changes == "yes");
			}
			//			user's final order  bill
			int payment_mode; string customer_name, address, credit_cardNum;
			bill = orderList.Total_bill();
			//			Adding the bill to today's total money earned
			total_cash_earned += bill;
			//			Asking the basic details of user for  keeping the orders record
			cout << "\n\n  CUSTOMER NAME: ";
			cin.ignore();
			getline(cin, customer_name);
			cout << "\n  DELIVERY ADDRESS(Islamabad, sector): "; cin >> address;
			//          Calculating shortest distance from food center to user's address using dijkstras algorithm
			int dist = DijkstrasMain(address);
			float delivery_time = 0.2 * dist;  //considering 1 meters takes 0.2 minutes to travel
//          Asking payment mode of order bill
			cout << "  PAYMENT MODES:\n             1- Cash on Delivery\n             2- Online Payment\n";
			cout << "  YOUR PAYMENT MODE: "; cin >> payment_mode;
			if (payment_mode == 2)
			{
				cout << "\n  Credit Card Number: "; cin >> credit_cardNum;
				cout << "\n  Payment has been made. Thank you!" << endl;
			}
			else
			{
				credit_cardNum = "cash on delivery";
			}
			//	        noticing time of final order
			time_t now = time(0);
			tm* ltm = gmtime(&now);
			int h, m, s, day, month, year;

			year = 1900 + ltm->tm_year;
			month = 1 + ltm->tm_mon;
			day = ltm->tm_mday;
			h = 5 + ltm->tm_hour;
			m = ltm->tm_min;
			s = ltm->tm_sec;
			//		    saving the date and time in proper format
			string date = to_string(day) + ", " + to_string(month) + ", " + to_string(year);
			string time = to_string(h) + ":" + to_string(m) + ":" + to_string(s);
			orderHistory.add_order_details(customer_name, credit_cardNum, bill, date, time);

			//			Displaying Receipt
			cout << "\n ----------------------------------------------------------------------\n";
			cout << endl << "                           __Order Receipt__" << endl;
			cout << "\n   CUSTOMER NAME:  " << customer_name;
			cout << "\n   DELIVERY ADDRESS: " << "Sector " << address << ", Islamabad. ";
			cout << "\n   ORDER TIME: " << time << endl << endl;
			orderList.display_order();
			cout << "\n                          YOUR TOTAL BILL: " << bill << endl;
			cout << "\n  Your order will be delivered in " << delivery_time << " minutes!\n";   // telling the delivery time
			cout << "  THANK YOU " << customer_name << " FOR ORDERING FOOD FROM FOOD EXPRESS!";
			cout << "\n                 ENJOY YOUR MEAL!\n";
			cout << "\n ----------------------------------------------------------------------\n";
			//          order is being recorded, so, deleting the previous order to empty the order list
			orderList.delete_order();
			bill = 0;
			//          asking user if they want to go back to main 
			cout << "\n\n  Do you want to go back to MAIN(press 0 to go back): ";
			cin >> back_main;
			cout << endl;
		}

		////    if user wants to go to admin panel...  ////
		else if (choice == Admin_Panel)
		{
			//			keep on asking for user name and password until user enters the correct name and password
			do
			{
				cout << "\n  USER NAME:  ";
				cin >> user_name;
				cout << "\n  PASSWORD:  ";
				cin >> password_entered;
				if (user_name != "admin_admin" || password_entered != password)
				{
					cout << "\n  Either User name or Password entered is wrong.Enter again!\n";
				}
			} while (user_name != "admin_admin" || password_entered != password);
			//			iterate till user wants to stay in admin panel
			while (back_admin != 1)
			{
				//				displaying admin panel and ask to select any option
				display_admin_panel();
				cout << "\n  Select any option: ";
				cin >> choice_admin;
				//				if user wants to add any item in menu
				if (choice_admin == 1)
				{
					cout << "  Item Name: ";
					cin.ignore();
					getline(cin, food_item_name);
					cout << "  Quantity: "; cin >> quantity;
					cout << "  Price: "; cin >> price;
					menu.insert_item(food_item_name, quantity, price);
				}
				//				if user wants to delete any item from menu
				else if (choice_admin == 2)
				{
					cout << "\n  Enter Serial Number: "; cin >> serial_num;
					menu.delete_item(serial_num);
				}
				//				if user wants to know today's total earning
				else if (choice_admin == 3)
				{
					cout << "\n  Total cash earned today: " << total_cash_earned << endl;
				}
				//				if user wants to see today's order history 
				else if (choice_admin == 4)
				{
					orderHistory.display_ordersHistory();
				}
				//				if user wants to change password of admin panel
				else
				{
					string prev_password;
					cout << "\n  Enter";
					cout << "\n  Current password:  ";
					cin >> prev_password;
					cout << "\n  New Password:  ";
					cin >> new_password;
					while (prev_password != password)
					{
						cout << "\n  Incorrect Password entered. Please try again!  \n";
						cout << "\n  Enter";
						cout << "\n  Current password:  ";
						cin >> prev_password;
						cout << "\n  New Password:  ";
						cin >> new_password;
					}
					password = new_password;
				}
				//				asking if the user want to go back to admin panel 
				cout << "\n  Do you want to go back to Admin Panel(press 0 to go back): ";
				cin >> back_admin;
			}
			back_admin = 0;
			//			asking if the user want to go back to main				
			cout << "\n\n  Do you want to go back to MAIN(press 0 to go back): ";
			cin >> back_main;
		}
		////    if user wants to QUIT the app		
		else
		{
			back_main = 1;
		}
	}
	cout << "\n ----------------------------------------------------------------------\n" << endl;

	return 0;
}