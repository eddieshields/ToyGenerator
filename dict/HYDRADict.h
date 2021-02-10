#ifndef DICT_TOYGENDICT_H
#define DICT_TOYGENDICT_H 1
// Include files

// Core HYDRA
#include "algorithm.h"
#include "algorithmstore.h"
#include "algorithmwrapper.h"
#include "clock.h"
#include "descriptor.h"
#include "event.h"
#include "hydra.h"
#include "particle.h"
#include "particlestore.h"
#include "pyalgorithm.h"
#include "random.h"
#include "sequence.h"
#include "threads.h"

// Algorithms.
#include "accept.h"
#include "amplitude.h"
#include "compositeparam.h"
#include "customparam.h"
#include "d02k3pi.h"
#include "decay3body.h"
#include "decay3bodymixing.h"
#include "efficiency.h"
#include "eventparam.h"
#include "generator.h"
#include "param.h"
#include "particleparam.h"
#include "tupling.h"

// Models.
#include "coefficient.h"
#include "configfile.h"
#include "configureamplitude.h"
#include "amplitude.h"
#include "flatte.h"
#include "parameter.h"
#include "phasespace.h"
#include "relbreitwigner.h"
#include "resonance.h"

#endif // DICT_TOYGEN_H