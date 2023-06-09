/*******************************************************************
*  DESCRIPTION: Atomic Model Transportation
*  AUTHOR: Liu, Qi
*  EMAIL: liuqi@sce.carleton.ca
*  DATE: 15/10/2004
*******************************************************************/

/** include files **/
#include <iostream>
#include "Transportation.h"  // base header
#include "message.h"       // InternalMessage ....
#include "mainsimu.h"      // class MainSimulator
#include "strutil.h"       // str2float( ... )

/*******************************************************************
* Function Name: Transportation
* Description: constructor
* Default trans_time is 2 hours
********************************************************************/
Transportation::Transportation( const string &name ) : 
Atomic(name), 
trans_time(2,0,0,0),
just_received(false),
tin(addInputPort("tin")), 
tout1(addOutputPort("tout1")),
tout2(addOutputPort("tout2"))
{
	
}

/*******************************************************************
* Function Name: externalFunction
* Description: the Transportation receives the material from Warehouse (1)
********************************************************************/
Model &Transportation::externalFunction( const ExternalMessage &msg )
{
  if(msg.value() == 1){
      if(this->state() == passive){
      	  just_received = true;
      	  holdIn(active, 0); //output -1 to tout2 immediately (busy)
      }else{ 
      	  //should never be here 
      	  //the warehouse will never send material when the transportation is busy
      	  cout << "Error: Transportation received input when BUSY!" << endl;
      }
  }else{
      cout << "Error: Transportation received an eror input!" << endl;
  }
  return *this ;
}

/*******************************************************************
* Function Name: internalFunction
********************************************************************/
Model &Transportation::internalFunction( const InternalMessage & )
{
	if(just_received){  //schedule the delivery after trans_time
		just_received = false;
		holdIn(active, trans_time);
	}else{ //received = false 
	    passivate();
	}
	return *this;
}

/*******************************************************************
* Function Name: outputFunction
********************************************************************/
Model &Transportation::outputFunction( const InternalMessage &msg )
{
  if(just_received){
      sendOutput(msg.time(), tout2, -1 );  //output -1 to the warehouse
  }else{
  	  sendOutput(msg.time(), tout1, 1 );  //output the materials
      sendOutput(msg.time(), tout2, 1 );  //tell the warehouse that it's free now
  }
  
  return *this;
}
