#include "stdint.h"

#define IWDG_REFRESH      (uint32_t)(0x0000AAAA)
#define IWDG_WRITE_ACCESS (uint32_t)(0x00005555)
#define IWDG_START        (uint32_t)(0x0000CCCC)
#define IWDG_RELOAD       (500)

void Configure_IWDG(void);
uint32_t CheckResetIWFG(void);
void ClearIWDGRSTF(void);

