  if(((RCC_OscInitStruct->OscillatorType) & RCC_OSCILLATORTYPE_LSE) == RCC_OSCILLATORTYPE_LSE)
  {
    FlagStatus       pwrclkchanged = RESET;
    
    /* Check the parameters */
    assert_param(IS_RCC_LSE(RCC_OscInitStruct->LSEState));

    /* Update LSE configuration in Backup Domain control register    */
    /* Requires to enable write access to Backup Domain of necessary */
    if(__HAL_RCC_PWR_IS_CLK_DISABLED())
    {
      __HAL_RCC_PWR_CLK_ENABLE();
      pwrclkchanged = SET;
    }
    
    if(HAL_IS_BIT_CLR(PWR->CR, PWR_CR_DBP))
    {
      /* Enable write access to Backup domain */
      SET_BIT(PWR->CR, PWR_CR_DBP);
      
      /* Wait for Backup domain Write protection disable */
      tickstart = HAL_GetTick();

      while(HAL_IS_BIT_CLR(PWR->CR, PWR_CR_DBP))
      {
        if((HAL_GetTick() - tickstart) > RCC_DBP_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }

    /* Set the new LSE configuration -----------------------------------------*/
    __HAL_RCC_LSE_CONFIG(RCC_OscInitStruct->LSEState);
    /* Check the LSE State */
    if(RCC_OscInitStruct->LSEState != RCC_LSE_OFF)
    {
      /* Get Start Tick */
      tickstart = HAL_GetTick();
      
      /* Wait till LSE is ready */  
      while(__HAL_RCC_GET_FLAG(RCC_FLAG_LSERDY) == RESET)
      {
        if((HAL_GetTick() - tickstart ) > RCC_LSE_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }
    else
    {
      /* Get Start Tick */
      tickstart = HAL_GetTick();
      
      /* Wait till LSE is disabled */  
      while(__HAL_RCC_GET_FLAG(RCC_FLAG_LSERDY) != RESET)
      {
        if((HAL_GetTick() - tickstart ) > RCC_LSE_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }

    /* Require to disable power clock if necessary */
    if(pwrclkchanged == SET)
    {
      __HAL_RCC_PWR_CLK_DISABLE();
    }
  }
  
  ///-----------------------------------------------------
  
  if(Format == RTC_FORMAT_BIN)
  
	tmpreg = (uint32_t)(((uint32_t)RTC_ByteToBcd2(sTime->Hours) << 16U) | \
                        ((uint32_t)RTC_ByteToBcd2(sTime->Minutes) << 8U) | \
                        ((uint32_t)RTC_ByteToBcd2(sTime->Seconds)) | \
                        (((uint32_t)sTime->TimeFormat) << 16U));  
						
						
						
  
  if(Format == RTC_FORMAT_BCD)
  
	tmpreg = (((uint32_t)(sTime->Hours) << 16U) | \
              ((uint32_t)(sTime->Minutes) << 8U) | \
              ((uint32_t)sTime->Seconds) | \
              ((uint32_t)(sTime->TimeFormat) << 16U));  
			  
			  
    /* Set the RTC_TR register */
    hrtc->Instance->TR = (uint32_t)(tmpreg & RTC_TR_RESERVED_MASK);
     
    /* Clear the bits to be configured */
    hrtc->Instance->CR &= ((uint32_t)~RTC_CR_BCK);

    /* Configure the RTC_CR register */
    hrtc->Instance->CR |= (uint32_t)(sTime->DayLightSaving | sTime->StoreOperation);
	
	/* Set the RTC_DR register */
    hrtc->Instance->DR = (uint32_t)(datetmpreg & RTC_DR_RESERVED_MASK);
	
	
	datetmpreg = ((((uint32_t)sDate->Year) << 16U) | \
                  (((uint32_t)sDate->Month) << 8U) | \
                  ((uint32_t)sDate->Date) | \
                  (((uint32_t)sDate->WeekDay) << 13U));  
	
	
	
	
	
	
	
	
	
	
	
	
  
  
