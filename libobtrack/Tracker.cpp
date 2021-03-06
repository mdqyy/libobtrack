#include "Tracker.h"
#include <iostream>

namespace obt {

Tracker::Tracker(bool needsTraining, bool needsHint):
		_needsTraining(needsTraining),
		_needsHint(needsHint),
		trained(false),
		started(false) {
}

/*! Initializes this tracker. Having a need for this should be avoided, but library users
	should call it anyway, to account for the cases where such a need exists.

	\return A negative value on failure. Any other value if successful.
*/
/* Dev note: for the future, try to replace this with a factory method when needed
   (i.e. static MyTracker createTracker(...)).
*/
int Tracker::init() {
	return 0;
}

/*! Trains an object tracker, according to sample images, or
	known (image, shapes) pairs. If a tracker needs training, it should
	always overload this function.

	\param ti A vector of images, or (image, object) pairs.

	\return Whether the training has been successful. 
		If the method hasn't been overriden, always returns true.
*/
bool Tracker::train(const std::vector<TrainingInfo>& ti) {
	return defaultTrainImpl();
}

/*! Trains an object tracker, according to a single sample image, or
	known (image, shapes) pair. If a tracker needs training, it should
	always overload this function.

	\param ti An image, or (image, shapes) pair

	\return Whether the training has been successful. 
		If the method hasn't been overriden, always returns true.
*/
bool Tracker::train(const TrainingInfo& ti) {
	return defaultTrainImpl();
}

bool Tracker::defaultTrainImpl() {
	if(_needsTraining)  {
		std::cerr << "Tracker::train: This tracker needs training."
				"You really should override this" << std::endl;
	}
	trained = true;
	return true;
}

/*! Stops tracking a single object, deleting its training data.

	This only applies if the tracker needs training or a hint.

	After calling this function, the shapes vector obtained by the next call
	to \ref objectShapes() or \ref objectShapes2D() shall have one less
	element than before.
		
	\param idx The index of the object to stop tracking, as reported by objectShapes()

	\return Whether there was success.

	\sa objectShapes()
	\sa needsHint()
*/
void Tracker::stopTrackingSingleObject(size_t idx) {
	if(!_needsTraining && !_needsHint)
		std::cerr << "Tracker::stopTrackingSingleObject: Can't stop tracking single object in\n"
				"\t\tautomatic trackers (i.e. when needsHint() == false)." << std::endl;
	else
		std::cerr << "Tracker::stopTrackingSingleObject: Manual object trackers\n"
				"\t\t(i.e. when needsHint() == false && needsTraining() == false) "
				"really should override this" << std::endl;
}

/*! Stops all tracking. Forgets any prior training.
*/
void Tracker::stopTracking() {
	trained = false;
	started = false;
}

/*! Returns whether this Tracker needs training data prior to working.
	The Tracker's author can choose to statically load its training
	data, without using the \ref train function. In such a case, needsTraining
	should be set to false.
*/
bool Tracker::needsTraining() const {
	return _needsTraining;
}

/*! Returns whether this Tracker needs a hint to determine the tracked
	object's initial position. If true, such a hint should be passed to the 
	\ref start function.
*/
bool Tracker::needsHint() const {
	return _needsHint;
}

bool Tracker::isTrained() const {
	return trained;
}

bool Tracker::isStarted() const {
	return started;
}


/*! Appends 2D versions of the shapes found to a vector. This is the 2D rendition
	from image number forImage. The shapes must be in the same order as the ones in
	objectShapes, and shapes not present in image forImage must be invalid ones.
	Invalid shapes include, but are not limited to, an empty Blob, an INVALID_RECT or 
	INVALID_ROTATED_RECT.
	The contents are only guaranteed to be valid pointers until the next call to feed().
	By default, calls objectShapes(shapes).

	\param shapes Output. The found shapes will be appended to this vector.
	\param forImage In multi-camera trackers, the image's index. Default: 0.

	\sa INVALID_RECT
	\sa INVALID_ROTATED_RECT
	\sa Shape
	\sa feed
*/
void Tracker::objectShapes2D(std::vector<const Shape*>& shapes, int forImage) const {
	objectShapes(shapes);
}

}	