/**
 * \file HaroldFactory.h
 *
 * \author Aaron Eshleman
 *
 * Factory class that builds the Harold character
 */


#pragma once
#include "ActorFactory.h"
#include "Actor.h"
#include <memory>


/**
 * Factory class that builds the Harold character
 */
class CHaroldFactory :
	public CActorFactory
{
public:
	CHaroldFactory();

	/** \brief Copy constructor disabled */
	CHaroldFactory(const CHaroldFactory &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CHaroldFactory &) = delete;

	~CHaroldFactory();

	std::shared_ptr<CActor> CHaroldFactory::Create() override;
};

