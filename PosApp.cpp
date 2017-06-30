#include <cstring>
#include <iomanip>
#include "PosApp.h"
#include "Item.h"
#include "Perishable.h"
#include "NonPerishable.h"

using namespace std;
using namespace sict;
namespace sict{
	
	PosApp::PosApp(const char* filename, const char* billfname){
		InitializePos();
		strncpy(_filename, filename, 128);
		_filename[128] = '\0';
		strncpy(_billfname, billfname, 128);
		_billfname[128] = '\0';	
		loadRecs();

	}


	
	
	void PosApp::InitializePos(){
		_filename[0] = '\0';
		_billfname[0] = '\0';
		_noOfItems = 0;
		for (int i = 0; i < MAX_NO_ITEMS; i++){
			_items[i] = (Item*)0;
		}
		for (int i = 0; i < MAX_NO_ITEMS; i++){
			_itemsType[i] = '0';
		}

	}

	PosApp::~PosApp(){
		
		for (int i = 0; i < MAX_NO_ITEMS; i++){
			delete _items[i];
		}
		
	}


	int PosApp::menu(){
		int n;
		bool r=true;
		do{
			cout<< "The OOPs Store" << endl
				<< "1- List items" << endl
				<< "2- Add Perishable item" << endl
				<< "3- Add Non-Perishable item" << endl
				<< "4- Update item quantity" << endl
				<< "5- Show Item" << endl
				<< "6- POS" << endl
				<< "0- exit program" << endl
				<< "> ";
			cin >> n;
			cout << endl;
			switch (n){
			case 1:
				//cout << ">Start"<<endl;
				listItems();
				cout<< endl;
				break;
			case 2:
				//cout << "Start";
				addItem(true);
				cout << endl;
				break;
			case 3:
				//cout << ">Start"<<endl;
				addItem(false);
				cout << endl;
				break;
			case 4:
				//cout << ">Start" <<endl;
				updateQty();
				cout << endl;
				break;
			case 5:
				char a[80];
				char t;
				cout << "Please enter the SKU: ";
				cin.get(t);
				cin.getline(a, 79, '\n');
				int i;
				if ((i = searchItems(a)) != -1){
					cout << "v-----------------------------------v"<<endl;
					_items[i]->write(cout, false);
					cout << "^-----------------------------------^";
					cout << endl <<endl;
				}
				else{
					cout << "Not found!" << endl;
				}
				break;
			case 6:
				POS();
				cout << endl;
				break;
			case 0:
				cout << endl;
				r=false;
				break;
			}
		} while (r);
		return 0;
	}

	void PosApp::loadRecs(){
		int i = 0;		
		char ID;
		char c;
		
		fstream Recordfile(_filename, ios::in);
		if (Recordfile.is_open()){		
				
					delete _items[i];
					
					if (Recordfile.fail()) cout << "fail";
					if (!Recordfile.fail()){
						Recordfile >> ID;
						while (!Recordfile.eof()){
							
							Recordfile >> c;

							if (ID == 'P'){
								_items[i] = new Perishable;
								_items[i]->load(Recordfile);
								_itemsType[i] = 'P';
								_noOfItems = i + 1;
								i++;
							}
							else if (ID == 'N'){
								_items[i] = new NonPerishable;
								_items[i]->load(Recordfile);
								_itemsType[i] = 'N';
								_noOfItems = i + 1;
								i++;
							}
							else{
								Recordfile.ignore(2000, ',');
								_items[i] = new Item;
								_items[i]->load(Recordfile);
								_itemsType[i] = 'I';
								_noOfItems = i + 1;
								i++;
							}

							Recordfile >>ID;
						}
						Recordfile.close();
					}
					
		}
		else {
			//cout << "Open file failed";
			Recordfile.clear();
			Recordfile.close();
			Recordfile.open(_filename, ios::out);
			Recordfile.close();
		}
		

	}
	void PosApp::saveRecs(){
		int i = 0;
		

		fstream Recordfile(_filename, ios::out);
		if (Recordfile.is_open()){
			if(Recordfile.good()  ){

				for (i = 0; i <_noOfItems; i++){

					if (_items[i]->quantity()!= 0){
						_items[i]->save(Recordfile);
					}					
				}
				
			}
			Recordfile.close();
			loadRecs();
		}
		else {
			//cout << "Open file failed";
			Recordfile.clear();
			Recordfile.close();
			Recordfile.open(_filename, ios::out);
			Recordfile.close();
		}

	}
	int PosApp::searchItems(const char* sku)const{
		int i;
		
		int result=-1;
		//fstream Recordfile(_filename, ios::in);
		
		for (i = 0; i <_noOfItems; i++){ // && !Recordfile.eof()
			if (*_items[i] == sku ){
				result=i;
			}
		}
		
		return result;
		
		
	}
	void PosApp::updateQty(){

		char skuN[81];
		int index;
		int qty;

		cout<< "Please enter the SKU: ";
		cin.ignore(2000, '\n');
		cin.getline(skuN, 80, '\n');
		skuN[80] = '\0';

		index = searchItems(skuN);
		if (index != -1){
			_items[index]->write(cout,false);
			cout << endl << "Please enter the number of purchased items: ";
			cin >> qty;
			//if (!cin.fail){
			*_items[index] += qty;
			saveRecs();
			cout << "Updated!" << endl;
		}
		else {
			cout << "Not found!" << endl;
		}

	}
	void PosApp::addItem(bool isPerishable){

		if (isPerishable && _noOfItems <MAX_NO_ITEMS ){
			_items[_noOfItems] = new Perishable; //Perishable* pI = new Perishable;
			
			cin >> *_items[_noOfItems];
			if (cin.fail()){
				cin.clear();
				cin.ignore(2000, '\n');

				cout << *_items[_noOfItems];
				delete _items[_noOfItems];
				_items[_noOfItems] = (Item*)0;
			}
			else{
				//_items[_noOfItems] = pI;
				_noOfItems++;
				saveRecs();
				cout << "Item added." << endl;

			}
		}
		else{

		}
	}
	void PosApp::listItems()const{
		int i = 0;
		
		double TotalAsset = 0;
		cout << " Row | SKU    | Item Name          | Price |TX |Qty |   Total |" << endl
		     << "-----|--------|--------------------|-------|---|----|---------|" << endl;
		     
		for (i = 0; i < _noOfItems; i++){

			cout << setw(4) << right << i+1 << " |";


			/*cout << setw(5) << left << _items[i]->sku() << "|"
				<< setw(11) << left << _items[i]->name() << "|"
				<< setw(7) << setprecision(2) <<fixed << right << _items[i]->price() << "|";
			if (_items[i]->taxed()){
				cout << setw(4) << " tp" << "|"
					<< setw(5) << right << _items[i]->quantity() << "|"
					<< setw(7) <<fixed<< setprecision(2) << right
					<<( _items[i]->quantity())*(_items[i]->price())*(1 + TAX) << "|";
			}
			else {
				cout << setw(4) << "p" << "|"
					<< setw(5) << right << _items[i]->quantity() << "|"
					<< setw(7) << fixed<< setprecision(2) << right
					<< (_items[i]->quantity())*(_items[i]->price()) << "|";
			}
			*/
			_items[i]->write(cout,true);
			if (_items[i]->taxed()){
				TotalAsset = (_items[i]->price())*(_items[i]->quantity())*(1 + TAX) + TotalAsset;
			}
			else{
				TotalAsset = (_items[i]->price())*(_items[i]->quantity()) + TotalAsset;
			}
			cout << endl;
			
			
		}
		cout << "-----^--------^--------------------^-------^---^----^---------^" << endl;
		cout << "Total Asset: $" << TotalAsset << endl;
	}
	void PosApp::showBill(){

		int i = 0;
		char ID;
		char c;
		double Total = 0;

		Date temp;
		
		Item* it=(Item*)0;
		fstream billFile(_billfname, ios::in);

		cout << "v--------------------------------------------------------v" << endl;
		cout << "| ";
		temp.write(cout);
		cout << "                                      |" << endl;
		cout << "| SKU    | Item Name          | Price |TX |Qty |   Total |"<<endl;
		cout << "|--------|--------------------|-------|---|----|---------|"<<endl;
		if (billFile.is_open()){

			delete it;

			if (billFile.fail()) cout << "fail";
			if (!billFile.fail()){
				billFile >> ID;
				while (!billFile.eof()){

					billFile >> c;

					if (ID == 'P'){
						it = new Perishable;
						it->load(billFile);
						//_itemsType[i] = 'P';
						//_noOfItems = i + 1;
						cout << "|";
						it->write(cout,true);
						cout << endl;
						i++;
					}
					else if (ID == 'N'){
						it = new NonPerishable;
						it->load(billFile);
						//_itemsType[i] = 'N';
						//_noOfItems = i + 1;

						cout << "|";
						it->write(cout, true);
						cout << endl;
						i++;
					}
					else{
						billFile.ignore(2000, ',');
						it = new Item;
						it->load(billFile);
						//_itemsType[i] = 'I';
						//_noOfItems = i + 1;
						cout << "|";
						it->write(cout, true);
						cout << endl;
						i++;
					}
					if (it->taxed()){
						Total = (it->price())*(it->quantity())*(1 + TAX) + Total;
					}
					else{
						Total = (it->price())*(it->quantity()) + Total;
					}
					billFile >> ID;
				}
				billFile.close();
			}

		}
		else {
			//cout << "Open file failed";
			billFile.clear();
			billFile.close();
			billFile.open(_filename, ios::out);
			billFile.close();
		}
		cout <<"^--------^--------------------^-------^---^----^---------^" <<endl;
		cout << "Total: $" << Total << endl;

	}
	void PosApp::addToBill(Item& I){

		int qty;
		qty = I.quantity();
		I.quantity(1);

		fstream billfile(_billfname,ios::out | ios::app);
		billfile<<I;
		if (qty >= 1) qty--;
		I.quantity(qty);
		saveRecs();
		loadRecs();

		billfile.close();
			
	
	}
	void PosApp::POS(){
		
		fstream f;
		f.open(_billfname, ios::out);		
		f.close();


		cin.ignore(2000, '\n');
		char s[81];
		int i = 0;
		//char a;
		while (true){

			cout << "Sku: ";
			
			cin.getline(s,80,'\n');
			if (strcmp(s, "") != 0){
				i = searchItems(s);
				if (i != -1){
					cout << "v------------------->" << endl
						<< "| ";
					cout << _items[i]->name() << endl;
					cout << "^------------------->" << endl;
					addToBill(*_items[i]);
				}
				else{					
					cout << "Not found!"<<endl;
				}
			}

			else{
				showBill();
				break;
			}
		}
	}
	void PosApp::Allocate(){
		
	}
	void PosApp::DeAllocate(){
		int i;
		
		for (i = 0; i < MAX_NO_ITEMS; i++){
			delete _items[i];
			_items[i] = (Item*)0;
		}		
	}

	
	void PosApp::run(){
		menu();
	}

}
