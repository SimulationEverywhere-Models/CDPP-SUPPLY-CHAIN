/*******************************************************************
*  DESCRIPTION: Atomic Model Assembling
*  AUTHOR: Liu, Qi
*  EMAIL: liuqi@sce.carleton.ca
*  DATE: 15/10/2004
*******************************************************************/

/** include files **/
#include <iostream>
#include "Assembling.h"    // base header
#include "message.h"       // InternalMessage ....
#include "mainsimu.h"      // class MainSimulator
#include "strutil.h"       // str2float( ... )

/*******************************************************************
* Function Name: Assembling
* Description: constructor
* Default Assembling_time is 4 hours
********************************************************************/
Assembling::Assembling( const string &name ) : 
Atomic( name ), 
assembling_time(4,0,0,0),
ain( addInputPort( "ain" ) ), 
aout1( addOutputPort( "aout1" ) ), 
aout2( addOutputPort( "aout2" ) )
{
	
}

/*******************************************************************
* Function Name: externalFunction
* Description: the Assembling receives the material from Preprocessor (int 1)
********************************************************************/
Model &Assembling::externalFunction( const ExternalMessage &msg )
{
  if((msg.value() == 1) && (this->state() == passive)){
	holdIn( active, assembling_time); //change to active for assembling_time
  }else{
    cout << "Error: Assembling receives an error input!!!" << endl;
  }
  return *this ;
}

/*******************************************************************
* Function Name: internalFunction
********************************************************************/
Model &Assembling::internalFunction( const InternalMessage & )
{
	passivate();	
	return *this;
}

/*******************************************************************
* Function Name: outputFunction
********************************************************************/
Model &Assembling::outputFunction( const InternalMessage &msg )
{
  sendOutput( msg.time(), aout1, 1 );  //output the product
  sendOutput( msg.time(), aout2, 1 );  //send 1 to inform Preprocessor 
 
  return *this;
}
