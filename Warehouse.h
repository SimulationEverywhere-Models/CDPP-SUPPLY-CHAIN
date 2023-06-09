/*******************************************************************
*  DESCRIPTION: Atomic Model Warehouse
*  AUTHOR: Liu, Qi
*  EMAIL: liuqi@sce.carleton.ca
*  DATE: 15/10/2004
*******************************************************************/
#ifndef WAREHOUSE_H
#define WAREHOUSE_H

/** include files **/
#include "atomic.h"  // class Atomic

/** declarations **/
class Warehouse: public Atomic
{
public:
	Warehouse( const string &name = "Warehouse" ) ;	 // Default constructor

	virtual string className() const
		{return "Warehouse";}

protected:
	Model &initFunction()
	{
      return *this;
    };

	Model &externalFunction( const ExternalMessage & );

	Model &internalFunction( const InternalMessage & );

	Model &outputFunction( const InternalMessage & );

private:
	const Port &win1;  //input materials from outside
	const Port &win2;  //input from Preprocessor (-1 means refusal, 1 means request)
	const Port &win3;  //input from Transportation (-1 means busy, 1 means free)
	Port &wout1;       //materials output, 1 unit per time
    Port &wout2;       //1 means requiring materials from outside
    
    Time processing_time;     //time interval to send out materials, default is 1 hour
    const int warehouse_capacity; //number of units of materials can be stored
    int current_units;  //current number of units 
    bool pause;
    bool trans_busy;
};	// class Warehouse


#endif    //Warehouse_H
