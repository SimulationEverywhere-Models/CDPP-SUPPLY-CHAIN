/*******************************************************************
*  DESCRIPTION: Atomic Model Preprocessing
*  AUTHOR: Liu, Qi
*  EMAIL: liuqi@sce.carleton.ca
*  DATE: 15/10/2004
*******************************************************************/

/** include files **/
#include <iostream>
#include "Preprocessing.h"  // base header
#include "message.h"       // InternalMessage ....
#include "mainsimu.h"      // class MainSimulator
#include "strutil.h"       // str2float( ... )

/*******************************************************************
* Function Name: Preprocessing
* Description: constructor
* default preprocessing_time is 30 minutes
* default check_time is 0
* default storage_capacity is 3
********************************************************************/
Preprocessing::Preprocessing( const string &name ) : 
Atomic(name), 
preprocessing_time(0,30,0,0),
check_time(0,0,0,0),
storage_capacity(3),
before(0),
after(0),
request(true),
shift(false),
send_check_result(false),
check_result(0),
pin1( addInputPort( "pin1" ) ), 
pin2( addInputPort( "pin2" ) ),
pout1( addOutputPort( "pout1" ) ), 
pout2( addOutputPort( "pout2" ) )
{
	
}

/*******************************************************************
* Function Name: externalFunction
* Description: receives the materials from transportation
*              and gets request signal from assembling
********************************************************************/
Model &Preprocessing::externalFunction( const ExternalMessage &msg )
{
  int current_storage = before + after;
  
  if(msg.port() == pin1){  //receive materials from pin1 port
      if(msg.value() == 1){ //must be 1
      	  if((current_storage + msg.value()) <= storage_capacity){ //cannot overflow        	  
        	  //1. update inventory
        	  before++;  
              current_storage++;                            
              //2. if inventory >=2, prepare to send out refusal signal
              if(current_storage >= 2){
              	  send_check_result = true;
              	  check_result = -1;              	   
                  holdIn(active, check_time);
              }else if((this->state() == passive) && (before > 0)){    
        		  shift = true;        		  
                  holdIn(active, preprocessing_time);
	          }  
      	  } else { //if storage overflows, should never happen
      	  	  cout << endl;
      	      cout << msg.time() << "Note: Preprocessing storage overflow!!!" << endl;
      	      cout << "      input = " << msg.value() 
      	           << "      current_storage + msg.value() = " 
      	           << (current_storage + msg.value()) << endl;
      	      cout << "Storage is set to 10." << endl;
      	  }
      }else{  //if the input is not 1
          cout << endl;
          cout << "Error: Preprocessing received an error input!!!" << endl;
          cout << "      input = " << msg.value() << endl;
      } 
  } 
  
  if(msg.port() == pin2){ //request signal from pin2 
      if(msg.value() == 1){
          request = true;          
          current_storage = before + after;           
          if(current_storage <= 1){
          	  send_check_result = true;
          	  check_result = 1;          	  
              holdIn(active, check_time);
          }else if(this->state() == passive){        		  
                  holdIn(active, 0);
	      }  
      }else{
          cout << "ERROR: Preprocessing get an error input from pin2!  " << msg.value() << endl;
      }
  }
  
  return *this ;
}

/*******************************************************************
* Function Name: internalFunction
* Description: 
********************************************************************/
Model &Preprocessing::internalFunction( const InternalMessage & )
{
	if(this->state() == active){
		//1. if request =true and after > 0 --> send output to pout1 immediately
		//2. if request = false and before >0 --> do processing
		if(request && (after > 0)){			
		    holdIn(active, 0);   
		}else if(before > 0){    
		    shift = true;		   
            holdIn(active, preprocessing_time);
	    }else if((before == 0) && !shift && !send_check_result){	    	
            passivate();
        }
	} else {
	    //this will never happen
	    cout << "Error: Preprocessing internal function was called in passive state!" << endl;
	}
	return *this;
}

/*******************************************************************
* Function Name: outputFunction
* Description:
* ********************************************************************/
Model &Preprocessing::outputFunction( const InternalMessage &msg )
{ 
  //if the preprocessing is done, shift one unit from before to after 
  if(shift){ 
      shift = false;
	  before--;
	  after++;
  }
  
  //request = true && after > 0, send output to pout1 immediately
  if(request && (after > 0)){
      after--;      
      sendOutput( msg.time(), pout1, 1 );
      request = false;
  }
  //if there are check results to output
  if(send_check_result && (check_result != 0)){
      if(check_result == -1){  //inventory >=2  	  
  	      send_check_result = false;
  	      check_result = 0;
          sendOutput(msg.time(), pout2, -1);
      } 
      
      if(check_result == 1){   //inventory <=1  	  
  	      send_check_result = false;
  	      check_result = 0;
          sendOutput(msg.time(), pout2, 1); 
      }
  }
  
  return *this;
}
