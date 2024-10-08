#include "main.h"

ADC_HandleTypeDef hadc1;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);

uint32_t adcValue = 0;

int main(void)
{
  HAL_Init();
  SystemClock_Config();

  MX_GPIO_Init();
  MX_ADC1_Init();

  while (1)
  {
    HAL_ADC_Start(&hadc1); // Bắt đầu chuyển đổi ADC

    if (HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY) == HAL_OK)
    {
      adcValue = HAL_ADC_GetValue(&hadc1); // Lấy giá trị ADC
    }

    HAL_ADC_Stop(&hadc1); // Dừng ADC

    // Xử lý giá trị adcValue (ví dụ: chuyển đổi sang điện áp)
    float voltage = (adcValue / 4095.0) * 3.3; // Với Vref = 3.3V

    HAL_Delay(100); // Delay 100ms
  }
}

static void MX_ADC1_Init(void)
{
  ADC_ChannelConfTypeDef sConfig = {0};

  /** Cấu hình ADC **/
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    // Xử lý lỗi
  }

  /** Cấu hình kênh ADC **/
  sConfig.Channel = ADC_CHANNEL_0; // PA0
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    // Xử lý lỗi
  }
}

void SystemClock_Config(void)
{
  // Cấu hình clock (tự động sinh bởi CubeMX)
}

static void MX_GPIO_Init(void)
{
  // Cấu hình GPIO (tự động sinh bởi CubeMX)
}
