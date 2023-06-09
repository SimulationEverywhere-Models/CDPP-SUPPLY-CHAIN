/*******************************************************************
*  DESCRIPTION: Atomic Model Assembling
*  AUTHOR: Liu, Qi
*  EMAIL: liuqi@sce.carleton.ca
*  DATE: 15/10/2004
*******************************************************************/
#ifndef ASSEMBLING_H
#define ASSEMBLING_H

/** include files **/
#include "atomic.h"  // class Atomic

/** declarations **/
class Assembling: public Atomic
{
public:
	Assembling( const string &name = "Assembling" ) ;	 // Default constructor

	virtual string className() const
		{return "Assembling";}

protected:
	Model &initFunction()
	{
      return *this;
    };

	Model &externalFunction( const ExternalMessage & );

	Model &internalFunction( const InternalMessage & );

	Model &outputFunction( const InternalMessage & );

private:
	const Port &ain ;
	Port &aout1 ;
    Port &aout2;
    Time assembling_time;

};	// class Assembling

#endif    //Assembling_H
