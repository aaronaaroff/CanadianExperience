/**
* \file BaldyFactory.h
*
* \author Aaron Eshleman
*
* Factory class that builds the Harold character
*/

#pragma once
#include "ActorFactory.h"


/**
 * Factory class that builds the Harold character
 */
class CBaldyFactory :
	public CActorFactory
{
public:
	/** constructor*/
	CBaldyFactory();

	/** \brief Copy constructor disabled */
	CBaldyFactory(const CBaldyFactory &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CBaldyFactory &) = delete;

	/** destructor*/
	~CBaldyFactory();

	std::shared_ptr<CActor> CBaldyFactory::Create() override;

};

