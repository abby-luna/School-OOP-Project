# School-OOP-Project
By abigail, zander, kieran and scott


# Abbys chunk

Abby worked on making the CItem class definition and all the functions that went along with it
In addition to this she collaberated with scott to develop a system where input is validated 
Abbys contribution to the input handler was the addition of a `typedef`. In addtion to this
she did the following menu functions

```cpp
// menu options
void DoDisplayFullPriceList(void);
void DoDisplayItem(void);
void DoTotalInvoice(void);
```

# Scotts chunk

Scott collaberated with abby to create the validated input handler, scott had the clever idea of using
a while loop to validate input. In addition to this scott wrote the CUser class definition and corresponding 
functions.  In addtion to this he did the following menu functions


```cpp
// menu options
void DoInitializePriceList(void);
void DoAddItemToList(void);
void DoSetItemPrice(void);
```

# kierans chunk

Kirean worked on the file handler, he ensured that all data that went through the program was being appropiatly saved 
to a CSV file. This is clever becuase it allowss the files to be edited in Microsoft Excel. In addition to file io kirean
made the Util functions to put the data from both files into the appropiate object. In addtion to this he did the following menu functions

```cpp
// menu options
void DoRemoveItemFromList(void);
void DoTotalInvoice(void);
void DoQuit(void);
```

# Zanders chunk

Zander worked on priority handling. He ensured that certain functions were only accessed by certain user types, he had the 
clever idea to create a priortity "level" and implemented that into our existing showNumbers function. Due to the nature of this task
we also assigned him to set up the menu. In addtion to this he did the following menu functions

```cpp
// menu options
void DoSetItemDiscountRate(void);
void DoOrderCost(void);
```

# Job Overlap

Kirean had to edit Zanders menu to save files

Scott and Zander both worked on `void DoSetItemPrice(void);` and `void DoSetItemDiscountRate(void);` due to the 
similar nature on the jobs

Scott and Abby worked on the input handler together mixing our skills to make the best possible function for the job

Abby got advice from her team on the table for both `void DoTotalInvoice(void);` and `void DoDisplayFullPriceList(void);` 

We all worked together to identify and squish bugs

Abby worked with Zander and Kirean to refactor the code

Kirean and Abby created data for the CSV's in Excel 
