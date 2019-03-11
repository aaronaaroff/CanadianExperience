/**
* Observer base class for a picture.
*
* This class implements the base class functionality for
* an observer in the observer pattern.
*/

#pragma once
#include <memory>

class CPicture;

/**This class implements the base class functionality for an observer in the observer pattern. */
class CPictureObserver
{
public:
	virtual ~CPictureObserver();
	/// Copy Constructor (Disabled)
	CPictureObserver(const CPictureObserver &) = delete;
	/// Assignment Operator (Disabled)
	void operator=(const CPictureObserver &) = delete;

	/// This function is called to update any observers
	virtual void UpdateObserver() = 0;

	/** Get the picture
	* \returns Picture */
	std::shared_ptr<CPicture> GetPicture() { return mPicture; }

	/** Set the picture
	* \param picture  The new picture */
	void SetPicture(std::shared_ptr<CPicture> picture);
protected:
	CPictureObserver();
private:
	/// Picture we are observing
	std::shared_ptr<CPicture> mPicture;
};

