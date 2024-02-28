#ifndef _CONFIG_HPP_
#define _CONFIG_HPP_

// GSC MODULES
#define COMPILE_ENTITY 1
#define COMPILE_PLAYER 1
#define COMPILE_UTILS 1

#if ENABLE_UNSAFE == 1
#define COMPILE_EXEC 1
#define COMPILE_MEMORY 1
#else
#define COMPILE_EXEC 0
#define COMPILE_MEMORY 0
#endif

#endif