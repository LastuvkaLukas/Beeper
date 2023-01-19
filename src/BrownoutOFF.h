#pragma once
//* -------------------------------
//* Brownout detector off

#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"

void brownoutOFF()
{
#ifdef DEBUG
    WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
#endif
}

//* -------------------------------
//* END