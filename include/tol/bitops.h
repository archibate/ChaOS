#pragma once

#define ENTSOF(w) (1<<(w))
#define MASKOF(w) (-ENTSOF(w))
#define OFFMOF(w) (ENTSOF(w)-1)
