#pragma once

#ifdef DEBUG_ENABLED

#define DEBUG(x) std::cout<< x << std::endl;

#else

#define DEBUG(x)

#endif // DEBUG
