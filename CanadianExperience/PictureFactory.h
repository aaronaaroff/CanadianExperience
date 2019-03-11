/**
 * \file PictureFactory.h
 *
 * \author Aaron Eshleman
 *
 * 
 * A factory class that builds our picture.
 *
 */



#pragma once
#include <memory>
#include "Picture.h"

 /**
 * A factory class that builds our picture.
 */
class CPictureFactory
{
public:
	CPictureFactory();

	/** \brief Copy constructor disabled */
	CPictureFactory(const CPictureFactory &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CPictureFactory &) = delete;

	virtual ~CPictureFactory();

	std::shared_ptr<CPicture> CPictureFactory::Create();
};

