/*******************************************************************
*  DESCRIPTION: Atomic Model Transportation
*  AUTHOR: Liu, Qi
*  EMAIL: liuqi@sce.carleton.ca
*  DATE: 15/10/2004
*******************************************************************/
#ifndef TRANSPORTATION_H
#define TRANSPORTATION_H

/** include files **/
#include "atomic.h"  // class Atomic

/** declarations **/
class Transportation: public Atomic
{
public:
	Transportation( const string &name = "Transportation" ) ;	 // Default constructor

	virtual string className() const
		{return "Transportation";}

protected:
	Model &initFunction()
	{
      return *this;
    };

	Model &externalFunction( const ExternalMessage & );

	Model &internalFunction( const InternalMessage & );

	Model &outputFunction( const InternalMessage & );

private:
	const Port &tin;  //input materials from the warehouse
	Port &tout1;      //output materials to tout1 after trans_time
	Port &tout2;      //1.once received the materials from the warehouse, 
	                  //  output -1 to tout2 indicating it's busy
	                  //2.after output to tout1, 
	                  //  output 1 to tout2 indicating it's free 
    Time trans_time;
    bool just_received;  //indicating an input is just received   
};	// class Transportation


#endif    //Transportation_H
