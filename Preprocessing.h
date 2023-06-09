/*******************************************************************
*  DESCRIPTION: Atomic Model Preprocessing
*  AUTHOR: Liu, Qi
*  EMAIL: liuqi@sce.carleton.ca
*  DATE: 15/10/2004
*******************************************************************/
#ifndef PREPROCESSING_H
#define PREPROCESSING_H

/** include files **/
#include "atomic.h"  // class Atomic

/** declarations **/
class Preprocessing: public Atomic
{
public:
	Preprocessing( const string &name = "Preprocessing" ) ;	 // Default constructor

	virtual string className() const
		{return "Preprocessing";}

protected:
	Model &initFunction()
	{
      return *this;
    };

	Model &externalFunction( const ExternalMessage & );

	Model &internalFunction( const InternalMessage & );

	Model &outputFunction( const InternalMessage & );

private:
	const Port &pin1;  //input materials from transportation
	const Port &pin2;  //input from assembling	                   
	                   //when the Assembling finishs a product,
	                   //there will be a 1 input from pint2
	Port &pout1;       //materials output, 1 unit per time	                                	                   
    Port &pout2;       //request/refusal signal output
                       // 1 means requiring materials; -1 means refusing materials                  
                      
    Time preprocessing_time;   //time to do preprocessing, default is 30 minutes
    Time check_time;           //time to check the current inventory, default is 0

    const int storage_capacity; //max of units can be stored, default is 3
    int before;                 //unprocessed units, default is 0
    int after;                  //finished units, default is 0
    //Note: 0 <= before + after <=storage_capacity at anytime
    
    bool request;       //true means request from assembling, default is true    
    bool shift;         //true means one unit is finished, default is false
    bool send_check_result; //true means should inventory check result to pout2                            //default is false
    
    int check_result;      //the result of a check, 1 or -1
    
};	// class Preprocessing


#endif    //Preprocessing_H
