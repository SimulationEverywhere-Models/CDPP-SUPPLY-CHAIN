/*******************************************************************
*  DESCRIPTION: Atomic Model Warehouse
*  AUTHOR: Liu, Qi
*  EMAIL: liuqi@sce.carleton.ca
*  DATE: 15/10/2004
*******************************************************************/

/** include files **/
#include <iostream>
#include "Warehouse.h"     // base header
#include "message.h"       // InternalMessage ....
#include "mainsimu.h"      // class MainSimulator
#include "strutil.h"       // str2float( ... )

/*******************************************************************
* Function Name: Warehouse
* Description: constructor
* default processing_time = 1 hour
********************************************************************/
Warehouse::Warehouse( const string &name ) : 
Atomic( name ), 
processing_time(1,0,0,0),
warehouse_capacity(10),
current_units(0),
pause(false),
trans_busy(false),
win1( addInputPort( "win1" ) ), 
win2( addInputPort( "win2" ) ),
win3( addInputPort( "win3" ) ),  
wout1( addOutputPort( "wout1" ) ), 
wout2( addOutputPort( "wout2" ) )
{
	
}

/*******************************************************************
* Function Name: externalFunction
* Description: the Warehouse receives the materials from outside (within 10 capacity)
********************************************************************/
Model &Warehouse::externalFunction( const ExternalMessage &msg )
{
  if(msg.port() == win1){  //receive materials from win1 port
      if(msg.value() > 0){
      	  //1. update inventory
      	  int temp = msg.value() + current_units;
      	  if(temp > warehouse_capacity){ //input too many, discard redundents
              temp = warehouse_capacity;
              cout << "Warehouse overflow!  Inventory is set to 10. " << endl;
          }
          current_units = temp;   //reset inventory to the maximum          
          
          //2. now the inventory is not empty 
          //   iff not paused, and transportation is free, start processing
          //   otherwise, no state change, keep waiting passively
          if ((!pause) && (!trans_busy) && (this->state() == passive)){            
              holdIn( active, processing_time);
          }
      }else{  //if the input is out of range
          cout << "Warning: Warehouse must receive a positive integer value (>0)!" << endl;
      } 
  } 
  
  if(msg.port() == win2){ //input from win2
      if(msg.value() == 1){ //request from Preprocessing
          pause = false;
          if((!trans_busy) && (this->state() == passive) && (current_units > 0)){
      	      holdIn( active, processing_time);
          }
      }
      
      if(msg.value() == -1){ //pause output, changes to passive
      	  pause = true;
          if(this->state() == active)
              passivate();
      } 
  }
  
  if(msg.port() == win3){ //input from win3
      if(msg.value() == 1){
          trans_busy = false;
          if((!pause) && (this->state() == passive) && (current_units > 0)){
      	      holdIn( active, processing_time);
          }
          //if paused or the inventory is empty, stay passive
      }
      
      if(msg.value() == -1){ 
      	  trans_busy = true;
      	  //transportation is busy, cannot output
          if(this->state() == active)
              passivate();
      } 
  }
  return *this ;
}

/*******************************************************************
* Function Name: internalFunction
********************************************************************/
Model &Warehouse::internalFunction( const InternalMessage & )
{
	if(this->state() == active){
	    //1. if not paused, inventory > 0, and transportation is free 
	    //   schedules the next state change
	    if((!pause) && (!trans_busy) && (current_units > 0)){
		    holdIn(active, processing_time);
    	} 
    	//2. if paused or transportation is busy or inventory is zero
    	//   become passive
	    if((pause) || (trans_busy) || (current_units == 0)){
	        passivate();
    	}
	} else {
	    //this will never happen
	    cout << "Error: Warehouse internal function was called in passive state!" << endl;
	}
	return *this;
}

/*******************************************************************
* Function Name: outputFunction
********************************************************************/
Model &Warehouse::outputFunction( const InternalMessage &msg )
{
  if((!pause) && (!trans_busy) && (current_units > 0)){ // send out 1 unit
  	  sendOutput( msg.time(), wout1, 1 );
  	  current_units -= 1; 
  }
  
  if(current_units == 0){ //send out 1 to indicate the warehouse is empty
      sendOutput( msg.time(), wout2, 1 ); 
  }
  return *this;
}
