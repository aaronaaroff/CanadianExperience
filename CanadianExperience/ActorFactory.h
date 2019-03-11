/**
 * \file ActorFactory.h
 *
 * \author Aaron Eshleman
 *
 * Abstract base class for actor factories. 
 */



#pragma once
#include <memory.h>
#include "Actor.h"


/**
 * 
 * Abstract base class for actor factories. 
 *
 */
class CActorFactory
{
public:

	CActorFactory();

	/** \brief Copy constructor disabled */
	CActorFactory(const CActorFactory &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CActorFactory &) = delete;

	virtual ~CActorFactory();

	/** Abstract class 
	*\return actor Type actor pointer*/
	virtual std::shared_ptr<CActor> CActorFactory::Create() = 0;
};

