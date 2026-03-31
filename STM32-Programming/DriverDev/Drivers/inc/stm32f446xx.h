/*
 * stm32f446xx.h
 *
 *  Created on: Feb 10, 2026
 *      Author: mohul
 */

#ifndef INC_STM32F446XX_H_
#define INC_STM32F446XX_H_

/*
 * Memory base addresses
 */

#define FLASH_BASEADDR 0x08000000U
#define ROM_BASEADDR 0x1FFF0000U
#define SRAM1_BASEADDR 0x20000000U
#define SRAM2_BASEADDR 0x2001C000U
#define SRAM_BASEADDR SRAM1_BASEADDR

/*
 * Peripheral base addresses
 */

#define APB1_PBASEADDR 0x40000000U
#define APB2_PBASEADDR 0x40010000U
#define AHB1_PBASEADDR 0x40020000U
#define AHB2_PBASEADDR 0x50000000U
#define AHB3_PBASEADDR 0x60000000U

/*
 * Peripherals in AHB1 bus
 */

#define GPIOA_BASEADDR 						(AHB1_PBASEADDR + 0x0000U)
#define GPIOB_BASEADDR 						(AHB1_PBASEADDR + 0x0400U)
#define GPIOC_BASEADDR 						(AHB1_PBASEADDR + 0x0800U)
#define GPIOD_BASEADDR 						(AHB1_PBASEADDR + 0x0C00U)
#define GPIOE_BASEADDR 						(AHB1_PBASEADDR + 0x1000U)
#define GPIOF_BASEADDR 						(AHB1_PBASEADDR + 0x1400U)
#define GPIOG_BASEADDR 						(AHB1_PBASEADDR + 0x1800U)
#define GPIOH_BASEADDR 						(AHB1_PBASEADDR + 0x1C00U)
#define CRC_BASEADDR 						(AHB1_PBASEADDR + 0x3000U)
#define RCC_BASEADDR 						(AHB1_PBASEADDR + 0x3800U)

/*
 * Peripherals in AHB2 bus
 */

#define USB_OTG_FS_BASEADDR (AHB2_PBASEADDR + 0x0000U)

/*
 * Peripherals in APB1 bus
 */

#define SPI2_I2S2_PBASEADDR 				(APB1_PBASEADDR + 0x3800U)
#define SPI3_I2S3_PBASEADDR 				(APB1_PBASEADDR + 0x3C00U)
#define USART2_PBASEADDR 					(APB1_PBASEADDR + 0x4400U)
#define USART3_PBASEADDR 					(APB1_PBASEADDR + 0x4800U)
#define UART4_PBASEADDR 					(APB1_PBASEADDR + 0x4C00U)
#define UART5_PBASEADDR 					(APB1_PBASEADDR + 0x5000U)
#define I2C1_PBASEADDR 						(APB1_PBASEADDR + 0x5400U)
#define I2C2_PBASEADDR 						(APB1_PBASEADDR + 0x5800U)
#define I2C3_PBASEADDR 						(APB1_PBASEADDR + 0x5C00U)
#define CAN1_PBASEADDR 						(APB1_PBASEADDR + 0x6400U)
#define CAN2_PBASEADDR 						(APB1_PBASEADDR + 0x6800U)

/*
 * Peripherals in APB2 bus
 */


/*
 * GPIO Register Definitions
 */

typedef struct {
	volatile uint32_t MODER;
	volatile uint32_t OTYPER;
	volatile uint32_t OSPEEDER;
	volatile uint32_t PUPDR;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AFR[2];
} GPIO_RegDef_t;

#define GPIOA 							(GPIO_RegDef_t *)(GPIOA_BASEADDR)
#define GPIOB 							(GPIO_RegDef_t *)(GPIOB_BASEADDR)
#define GPIOC 							(GPIO_RegDef_t *)(GPIOC_BASEADDR)
#define GPIOD 							(GPIO_RegDef_t *)(GPIOD_BASEADDR)
#define GPIOE 							(GPIO_RegDef_t *)(GPIOE_BASEADDR)
#define GPIOF 							(GPIO_RegDef_t *)(GPIOF_BASEADDR)
#define GPIOG 							(GPIO_RegDef_t *)(GPIOG_BASEADDR)
#define GPIOH 							(GPIO_RegDef_t *)(GPIOH_BASEADDR)

/*
 * I2C Register Definitions
 */

typedef struct {
	volatile uint32_t I2C_CR1;
	volatile uint32_t I2C_CR2;
	volatile uint32_t I2C_OAR1;
	volatile uint32_t I2C_OAR2;
	volatile uint32_t I2C_DR;
	volatile uint32_t I2C_SR1;
	volatile uint32_t I2C_SR2;
	volatile uint32_t I2C_CCR;
	volatile uint32_t I2C_TRISE;
	volatile uint32_t I2C_FLTR;

} I2C_RegDef_t;

#define I2C1 							(I2C_RegDef_t *)(I2C1_PBASEADDR)
#define I2C2 							(I2C_RegDef_t *)(I2C2_PBASEADDR)
#define I2C3 							(I2C_RegDef_t *)(I2C3_PBASEADDR)

/*
 * SPI Register Definitions
 */

typedef struct {
	volatile uint32_t SPI_CR1;
	volatile uint32_t SPI_CR2;
	volatile uint32_t SPI_SR;
	volatile uint32_t SPI_DR;
	volatile uint32_t SPI_CRCPR;
	volatile uint32_t SPI_RXCRCR;
	volatile uint32_t SPI_TXCRCR;
	volatile uint32_t SPI_I2SCFGR;
	volatile uint32_t SPI_I2SPR;

} SPI_RegDef_t;

#define SPI2_I2S2 						(SPI_RegDef_t *)(SPI2_I2S2_PBASEADDR)
#define SPI3_I2S3 						(SPI_RegDef_t *)(SPI3_I2S3_PBASEADDR)

/*
 * RCC Register Definitions
 */

typedef struct {
	volatile uint32_t RCC_CR;
	volatile uint32_t RCC_PLLCFGR;
	volatile uint32_t RCC_CFGR;
	volatile uint32_t RCC_AHB1RSTR;
	volatile uint32_t RCC_AHB2RSTR;
	volatile uint32_t RCC_AHB3RSTR;
	volatile uint32_t RSVD1;
	volatile uint32_t RCC_APB1RSTR;
	volatile uint32_t RCC_APB2RSTR;
	volatile uint32_t RSVD2;
	volatile uint32_t RSVD3;
	volatile uint32_t RCC_AHB1ENR;
	volatile uint32_t RCC_AHB2ENR;
	volatile uint32_t RCC_AHB3ENR;
	volatile uint32_t RSVD4;
	volatile uint32_t RCC_APB1ENR;
	volatile uint32_t RCC_APB2ENR;
	volatile uint32_t RSVD5;
	volatile uint32_t RSVD6;
	volatile uint32_t RCC_AHB1LPENR;
	volatile uint32_t RCC_AHB2LPENR;
	volatile uint32_t RCC_AHB3LPENR;
	volatile uint32_t RSVD7;
	volatile uint32_t RCC_APB1LPENR;
	volatile uint32_t RCC_APB2LPENR;
	volatile uint32_t RSVD8;
	volatile uint32_t RSVD9;
	volatile uint32_t RCC_BDCR;
	volatile uint32_t RCC_CSR;
	volatile uint32_t RSVD10;
	volatile uint32_t RSVD11;
	volatile uint32_t RCC_SSCGR;
	volatile uint32_t RCC_PLLI2SCFGR;
	volatile uint32_t RCC_PLLSAICFGR;
	volatile uint32_t RCC_DCKCFGR;
	volatile uint32_t RCC_CKGATENR;
	volatile uint32_t RCC_DCKCFGR2;
} RCC_RegDef_t;

#define RCC (RCC_RegDef_t *)(RCC_BASEADDR)

/*
 * Clock enable and disable macros
 */

#define GPIOA_PCLK_EN() (RCC->RCC_AHB1ENR |= (1<<0))
#define GPIOB_PCLK_EN() (RCC->RCC_AHB1ENR |= (1<<1))
#define GPIOC_PCLK_EN() (RCC->RCC_AHB1ENR |= (1<<2))
#define GPIOD_PCLK_EN() (RCC->RCC_AHB1ENR |= (1<<3))
#define GPIOE_PCLK_EN() (RCC->RCC_AHB1ENR |= (1<<4))
#define GPIOF_PCLK_EN() (RCC->RCC_AHB1ENR |= (1<<5))
#define GPIOG_PCLK_EN() (RCC->RCC_AHB1ENR |= (1<<6))
#define GPIOH_PCLK_EN() (RCC->RCC_AHB1ENR |= (1<<7))

#define GPIOA_PCLK_DI() (RCC->RCC_AHB1ENR &= ~(1<<0))
#define GPIOB_PCLK_DI() (RCC->RCC_AHB1ENR &= ~(1<<1))
#define GPIOC_PCLK_DI() (RCC->RCC_AHB1ENR &= ~(1<<2))
#define GPIOD_PCLK_DI() (RCC->RCC_AHB1ENR &= ~(1<<3))
#define GPIOE_PCLK_DI() (RCC->RCC_AHB1ENR &= ~(1<<4))
#define GPIOF_PCLK_DI() (RCC->RCC_AHB1ENR &= ~(1<<5))
#define GPIOG_PCLK_DI() (RCC->RCC_AHB1ENR &= ~(1<<6))
#define GPIOH_PCLK_DI() (RCC->RCC_AHB1ENR &= ~(1<<7))

#define I2C1_PCLK_EN() (RCC->RCC_APB1ENR |= (1<<21))
#define I2C2_PCLK_EN() (RCC->RCC_APB1ENR |= (1<<22))
#define I2C3_PCLK_EN() (RCC->RCC_APB1ENR |= (1<<23))

#define I2C1_PCLK_DI() (RCC->RCC_APB1ENR &= ~(1<<21))
#define I2C2_PCLK_DI() (RCC->RCC_APB1ENR &= ~(1<<22))
#define I2C3_PCLK_DI() (RCC->RCC_APB1ENR &= ~(1<<23))

#define SPI1_PCLK_EN() (RCC->RCC_APB2ENR |= (1<<12))
#define SPI2_PCLK_EN() (RCC->RCC_APB1ENR |= (1<<14))
#define SPI3_PCLK_EN() (RCC->RCC_APB1ENR |= (1<<15))
#define SPI4_PCLK_EN() (RCC->RCC_APB2ENR |= (1<<13))

#define SPI1_PCLK_DI() (RCC->RCC_APB2ENR &= ~(1<<12))
#define SPI2_PCLK_DI() (RCC->RCC_APB1ENR &= ~(1<<14))
#define SPI3_PCLK_DI() (RCC->RCC_APB1ENR &= ~(1<<15))
#define SPI4_PCLK_DI() (RCC->RCC_APB2ENR &= ~(1<<13))


#endif /* INC_STM32F446XX_H_ */
