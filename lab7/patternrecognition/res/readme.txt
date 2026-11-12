/**********************************************************************
 *  Mönsterigenkänning readme.txt
 **********************************************************************/

/**********************************************************************
 *  Empirisk    Fyll i tabellen nedan med riktiga körtider i sekunder
 *  analys      när det känns vettigt att vänta på hela beräkningen.
 *              Ge uppskattningar av körtiden i övriga fall.
 *
 **********************************************************************/
    
      N       brute       sortering
 ----------------------------------
    150       0.016         0.007
    200       0.033         0.020
    300       0.077         0.042
    400       0.184         0.088
    800       1.409         0.659
   1600       11.053        5.124
   3200       67.53         40.846
   6400       463.22        250.08
  12800       3177.32       1742.4


/**********************************************************************
 *  Teoretisk   Ge ordo-uttryck för värstafallstiden för programmen som
 *  analys      en funktion av N. Ge en kort motivering.
 *
 **********************************************************************/

Brute: O(n^4) fyra loopar som alltid går igenom alla punkter.

Sortering: O(n^3) tre loopar som alltid går igenom alla punkter 

