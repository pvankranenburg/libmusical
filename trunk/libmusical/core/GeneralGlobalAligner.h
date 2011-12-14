/*
 * GeneralGlobalAligner.h
 *
 *  Created on: Nov 28, 2011
 *      Author: pvk
 */

#ifndef GENERALGLOBALALIGNER_H_
#define GENERALGLOBALALIGNER_H_

#include <AlignmentAlgorithm.h>

namespace musical {

class GeneralGlobalAligner: public musical::AlignmentAlgorithm {
public:
	GeneralGlobalAligner();
	virtual ~GeneralGlobalAligner();
};

}

#endif /* GENERALGLOBALALIGNER_H_ */
