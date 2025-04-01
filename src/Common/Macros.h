#pragma once

#ifdef LUNA_BUILD_DSO
#define LUNA_API __attribute__((visibility("default")))
#else
#define LUNA_API
#endif
