#ifndef SICT_POSAPP_H__
#define SICT_POSAPP_H__
#include "Perishable.h"
#include "NonPerishable.h"
namespace sict{
  class PosApp{
    char _filename[128];
    char _billfname[128];
    Item* _items[MAX_NO_ITEMS];
	char _itemsType[MAX_NO_ITEMS];
    int _noOfItems;
    int menu();
    void loadRecs();
    void saveRecs();
    int searchItems(const char* sku)const;
    void updateQty();
    void addItem(bool isPerishable);
    void listItems()const;
    void showBill();
    void addToBill(Item& I);
    void POS();
	void Allocate();
	void DeAllocate();
  public:   
    // prevent copying and assignment here!
	//PosApp();
    PosApp(const char* filename, const char* billfname);
	PosApp(const PosApp& p)=delete;
	void InitializePos();
	~PosApp();
	PosApp& operator= (const PosApp& p) = delete;
	
    void run();
  };
}
#endif
