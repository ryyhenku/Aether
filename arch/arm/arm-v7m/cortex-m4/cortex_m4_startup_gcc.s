.syntax unified
.cpu cortex-m4
.thumb

.global isr_vector
.global Reset_Handler

.section .isr_vector,"a",%progbits
isr_vector:
    .word __main_stack_top
    .word  Reset_Handler                /*复位*/
    .word  NMI_Handler                 /* NMI 处理函数 */
    .word  HardFault_Handler           /* 硬件错误处理函数 */
    .word  MemManage_Handler           /* 内存管理错误处理函数 */
    .word  BusFault_Handler            /* 总线错误处理函数 */
    .word  UsageFault_Handler          /* 使用错误处理函数 */
    .word  0                           /* 保留 */
    .word  0                           /* 保留 */
    .word  0                           /* 保留 */
    .word  0                           /* 保留 */
    .word  vPortSVCHandler                 /* SVCall 处理函数 */
    .word  DebugMon_Handler            /* 调试监控处理函数 */
    .word  0                           /* 保留 */
    .word  xPortPendSVHandler              /* PendSV 处理函数 */
    .word  xPortSysTickHandler             /* SysTick 处理函数 */

    /* STM32F407外部中断 (IRQ0 - IRQ81) */
    .word  WWDG_IRQHandler                 /* 0x040 窗口看门狗中断 */
    .word  PVD_IRQHandler                  /* 0x044 PVD通过EXTI检测中断 */
    .word  TAMP_STAMP_IRQHandler           /* 0x048 Tamper和时间戳中断 */
    .word  RTC_WKUP_IRQHandler             /* 0x04C RTC唤醒中断 */
    .word  FLASH_IRQHandler                /* 0x050 Flash全局中断 */
    .word  RCC_IRQHandler                  /* 0x054 RCC全局中断 */
    .word  EXTI0_IRQHandler                /* 0x058 EXTI Line0中断 */
    .word  EXTI1_IRQHandler                /* 0x05C EXTI Line1中断 */
    .word  EXTI2_IRQHandler                /* 0x060 EXTI Line2中断 */
    .word  EXTI3_IRQHandler                /* 0x064 EXTI Line3中断 */
    .word  EXTI4_IRQHandler                /* 0x068 EXTI Line4中断 */
    .word  DMA1_Stream0_IRQHandler         /* 0x06C DMA1 Stream0全局中断 */
    .word  DMA1_Stream1_IRQHandler         /* 0x070 DMA1 Stream1全局中断 */
    .word  DMA1_Stream2_IRQHandler         /* 0x074 DMA1 Stream2全局中断 */
    .word  DMA1_Stream3_IRQHandler         /* 0x078 DMA1 Stream3全局中断 */
    .word  DMA1_Stream4_IRQHandler         /* 0x07C DMA1 Stream4全局中断 */
    .word  DMA1_Stream5_IRQHandler         /* 0x080 DMA1 Stream5全局中断 */
    .word  DMA1_Stream6_IRQHandler         /* 0x084 DMA1 Stream6全局中断 */
    .word  ADC_IRQHandler                  /* 0x088 ADC1/2/3全局中断 */
    .word  CAN1_TX_IRQHandler              /* 0x08C CAN1 TX中断 */
    .word  CAN1_RX0_IRQHandler             /* 0x090 CAN1 RX0中断 */
    .word  CAN1_RX1_IRQHandler             /* 0x094 CAN1 RX1中断 */
    .word  CAN1_SCE_IRQHandler             /* 0x098 CAN1 SCE中断 */
    .word  EXTI9_5_IRQHandler              /* 0x09C EXTI Line[9:5]中断 */
    .word  TIM1_BRK_TIM9_IRQHandler        /* 0x0A0 TIM1 Break和TIM9全局中断 */
    .word  TIM1_UP_TIM10_IRQHandler        /* 0x0A4 TIM1 Update和TIM10全局中断 */
    .word  TIM1_TRG_COM_TIM11_IRQHandler   /* 0x0A8 TIM1 Trigger和TIM11全局中断 */
    .word  TIM1_CC_IRQHandler              /* 0x0AC TIM1捕获比较中断 */
    .word  TIM2_IRQHandler                 /* 0x0B0 TIM2全局中断 */
    .word  TIM3_IRQHandler                 /* 0x0B4 TIM3全局中断 */
    .word  TIM4_IRQHandler                 /* 0x0B8 TIM4全局中断 */
    .word  I2C1_EV_IRQHandler              /* 0x0BC I2C1事件中断 */
    .word  I2C1_ER_IRQHandler              /* 0x0C0 I2C1错误中断 */
    .word  I2C2_EV_IRQHandler              /* 0x0C4 I2C2事件中断 */
    .word  I2C2_ER_IRQHandler              /* 0x0C8 I2C2错误中断 */
    .word  SPI1_IRQHandler                 /* 0x0CC SPI1全局中断 */
    .word  SPI2_IRQHandler                 /* 0x0D0 SPI2全局中断 */
    .word  USART1_IRQHandler               /* 0x0D4 USART1全局中断 */
    .word  USART2_IRQHandler               /* 0x0D8 USART2全局中断 */
    .word  USART3_IRQHandler               /* 0x0DC USART3全局中断 */
    .word  EXTI15_10_IRQHandler            /* 0x0E0 EXTI Line[15:10]中断 */
    .word  RTC_Alarm_IRQHandler            /* 0x0E4 RTC闹钟通过EXTI中断 */
    .word  OTG_FS_WKUP_IRQHandler          /* 0x0E8 USB OTG FS唤醒中断 */
    .word  TIM8_BRK_TIM12_IRQHandler       /* 0x0EC TIM8 Break和TIM12全局中断 */
    .word  TIM8_UP_TIM13_IRQHandler        /* 0x0F0 TIM8 Update和TIM13全局中断 */
    .word  TIM8_TRG_COM_TIM14_IRQHandler   /* 0x0F4 TIM8 Trigger和TIM14全局中断 */
    .word  TIM8_CC_IRQHandler              /* 0x0F8 TIM8捕获比较中断 */
    .word  DMA1_Stream7_IRQHandler         /* 0x0FC DMA1 Stream7全局中断 */
    .word  FMC_IRQHandler                  /* 0x100 FMC全局中断 */
    .word  SDIO_IRQHandler                 /* 0x104 SDIO全局中断 */
    .word  TIM5_IRQHandler                 /* 0x108 TIM5全局中断 */
    .word  SPI3_IRQHandler                 /* 0x10C SPI3全局中断 */
    .word  UART4_IRQHandler                /* 0x110 UART4全局中断 */
    .word  UART5_IRQHandler                /* 0x114 UART5全局中断 */
    .word  TIM6_DAC_IRQHandler             /* 0x118 TIM6全局和DAC1/2中断 */
    .word  TIM7_IRQHandler                 /* 0x11C TIM7全局中断 */
    .word  DMA2_Stream0_IRQHandler         /* 0x120 DMA2 Stream0全局中断 */
    .word  DMA2_Stream1_IRQHandler         /* 0x124 DMA2 Stream1全局中断 */
    .word  DMA2_Stream2_IRQHandler         /* 0x128 DMA2 Stream2全局中断 */
    .word  DMA2_Stream3_IRQHandler         /* 0x12C DMA2 Stream3全局中断 */
    .word  DMA2_Stream4_IRQHandler         /* 0x130 DMA2 Stream4全局中断 */
    .word  ETH_IRQHandler                  /* 0x134 Ethernet全局中断 */
    .word  ETH_WKUP_IRQHandler             /* 0x138 Ethernet唤醒中断 */
    .word  CAN2_TX_IRQHandler              /* 0x13C CAN2 TX中断 */
    .word  CAN2_RX0_IRQHandler             /* 0x140 CAN2 RX0中断 */
    .word  CAN2_RX1_IRQHandler             /* 0x144 CAN2 RX1中断 */
    .word  CAN2_SCE_IRQHandler             /* 0x148 CAN2 SCE中断 */
    .word  OTG_FS_IRQHandler               /* 0x14C USB OTG FS全局中断 */
    .word  DMA2_Stream5_IRQHandler         /* 0x150 DMA2 Stream5全局中断 */
    .word  DMA2_Stream6_IRQHandler         /* 0x154 DMA2 Stream6全局中断 */
    .word  DMA2_Stream7_IRQHandler         /* 0x158 DMA2 Stream7全局中断 */
    .word  USART6_IRQHandler               /* 0x15C USART6全局中断 */
    .word  I2C3_EV_IRQHandler              /* 0x160 I2C3事件中断 */
    .word  I2C3_ER_IRQHandler              /* 0x164 I2C3错误中断 */
    .word  OTG_HS_EP1_OUT_IRQHandler       /* 0x168 USB OTG HS End Point1 Out中断 */
    .word  OTG_HS_EP1_IN_IRQHandler        /* 0x16C USB OTG HS End Point1 In中断 */
    .word  OTG_HS_WKUP_IRQHandler          /* 0x170 USB OTG HS唤醒中断 */
    .word  OTG_HS_IRQHandler               /* 0x174 USB OTG HS全局中断 */
    .word  DCMI_IRQHandler                 /* 0x178 DCMI全局中断 */
    .word  CRYP_IRQHandler                 /* 0x17C CRYPTO全局中断 */
    .word  HASH_RNG_IRQHandler             /* 0x180 Hash和Rng全局中断 */
    .word  FPU_IRQHandler                  /* 0x184 FPU全局中断 */

/* Reset_Handler */
.section .text.Reset_Handler
.type Reset_Handler, %function
Reset_Handler:
  /* 初始化栈指针 */
  ldr   sp, =__main_stack_top

  /* 启动FPU */
  ldr.w r0, =0xE000ED88          
  ldr   r1, [r0]                 
  orr   r1, r1, #(0xF << 20)    
  str   r1, [r0]                
  dsb                           
  isb                            

  /* 复制数据段从Flash到RAM */
  ldr   r0, =_sdata
  ldr   r1, =_edata
  ldr   r2, =_sidata
  movs  r3, #0
  b     LoopCopyDataInit

CopyDataInit:
  ldr   r4, [r2, r3]
  str   r4, [r0, r3]
  adds  r3, r3, #4

LoopCopyDataInit:
  adds  r4, r0, r3
  cmp   r4, r1
  bcc   CopyDataInit

  /* 清零BSS段 */
  ldr   r2, =_sbss
  ldr   r4, =_ebss
  movs  r3, #0
  b     LoopFillZerobss

FillZerobss:
  str   r3, [r2]
  adds  r2, r2, #4

LoopFillZerobss:
  cmp   r2, r4
  bcc   FillZerobss

  /* 配置系统时钟 */
  bl    SystemInit

  /* 跳转到main函数 */
  bl    main

  /* 如果main函数返回，进入无限循环 */
LoopForever:
  b     LoopForever

.size Reset_Handler, .-Reset_Handler

/* 默认中断处理函数 */
.section  .text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
  b  Infinite_Loop
.size  Default_Handler, .-Default_Handler

/* 宏定义：简化弱定义代码 */
.macro def_default_handler handler_name
    .weak  \handler_name
    .thumb_set \handler_name, Default_Handler
.endm

/* ========== Cortex-M4处理器异常 ========== */
def_default_handler NMI_Handler
def_default_handler HardFault_Handler
def_default_handler MemManage_Handler
def_default_handler BusFault_Handler
def_default_handler UsageFault_Handler
def_default_handler vPortSVCHandler
def_default_handler DebugMon_Handler
def_default_handler xPortPendSVHandler
def_default_handler xPortSysTickHandler

/* ========== STM32F407外部中断 (IRQ0 - IRQ81) ========== */

/* 中断0-9 */
def_default_handler WWDG_IRQHandler
def_default_handler PVD_IRQHandler
def_default_handler TAMP_STAMP_IRQHandler
def_default_handler RTC_WKUP_IRQHandler
def_default_handler FLASH_IRQHandler
def_default_handler RCC_IRQHandler
def_default_handler EXTI0_IRQHandler
def_default_handler EXTI1_IRQHandler
def_default_handler EXTI2_IRQHandler
def_default_handler EXTI3_IRQHandler

/* 中断10-19 */
def_default_handler EXTI4_IRQHandler
def_default_handler DMA1_Stream0_IRQHandler
def_default_handler DMA1_Stream1_IRQHandler
def_default_handler DMA1_Stream2_IRQHandler
def_default_handler DMA1_Stream3_IRQHandler
def_default_handler DMA1_Stream4_IRQHandler
def_default_handler DMA1_Stream5_IRQHandler
def_default_handler DMA1_Stream6_IRQHandler
def_default_handler ADC_IRQHandler
def_default_handler CAN1_TX_IRQHandler

/* 中断20-29 */
def_default_handler CAN1_RX0_IRQHandler
def_default_handler CAN1_RX1_IRQHandler
def_default_handler CAN1_SCE_IRQHandler
def_default_handler EXTI9_5_IRQHandler
def_default_handler TIM1_BRK_TIM9_IRQHandler
def_default_handler TIM1_UP_TIM10_IRQHandler
def_default_handler TIM1_TRG_COM_TIM11_IRQHandler
def_default_handler TIM1_CC_IRQHandler
def_default_handler TIM2_IRQHandler
def_default_handler TIM3_IRQHandler

/* 中断30-39 */
def_default_handler TIM4_IRQHandler
def_default_handler I2C1_EV_IRQHandler
def_default_handler I2C1_ER_IRQHandler
def_default_handler I2C2_EV_IRQHandler
def_default_handler I2C2_ER_IRQHandler
def_default_handler SPI1_IRQHandler
def_default_handler SPI2_IRQHandler
def_default_handler USART1_IRQHandler
def_default_handler USART2_IRQHandler
def_default_handler USART3_IRQHandler

/* 中断40-49 */
def_default_handler EXTI15_10_IRQHandler
def_default_handler RTC_Alarm_IRQHandler
def_default_handler OTG_FS_WKUP_IRQHandler
def_default_handler TIM8_BRK_TIM12_IRQHandler
def_default_handler TIM8_UP_TIM13_IRQHandler
def_default_handler TIM8_TRG_COM_TIM14_IRQHandler
def_default_handler TIM8_CC_IRQHandler
def_default_handler DMA1_Stream7_IRQHandler
def_default_handler FMC_IRQHandler
def_default_handler SDIO_IRQHandler

/* 中断50-59 */
def_default_handler TIM5_IRQHandler
def_default_handler SPI3_IRQHandler
def_default_handler UART4_IRQHandler
def_default_handler UART5_IRQHandler
def_default_handler TIM6_DAC_IRQHandler
def_default_handler TIM7_IRQHandler
def_default_handler DMA2_Stream0_IRQHandler
def_default_handler DMA2_Stream1_IRQHandler
def_default_handler DMA2_Stream2_IRQHandler
def_default_handler DMA2_Stream3_IRQHandler

/* 中断60-69 */
def_default_handler DMA2_Stream4_IRQHandler
def_default_handler ETH_IRQHandler
def_default_handler ETH_WKUP_IRQHandler
def_default_handler CAN2_TX_IRQHandler
def_default_handler CAN2_RX0_IRQHandler
def_default_handler CAN2_RX1_IRQHandler
def_default_handler CAN2_SCE_IRQHandler
def_default_handler OTG_FS_IRQHandler
def_default_handler DMA2_Stream5_IRQHandler
def_default_handler DMA2_Stream6_IRQHandler

/* 中断70-79 */
def_default_handler DMA2_Stream7_IRQHandler
def_default_handler USART6_IRQHandler
def_default_handler I2C3_EV_IRQHandler
def_default_handler I2C3_ER_IRQHandler
def_default_handler OTG_HS_EP1_OUT_IRQHandler
def_default_handler OTG_HS_EP1_IN_IRQHandler
def_default_handler OTG_HS_WKUP_IRQHandler
def_default_handler OTG_HS_IRQHandler
def_default_handler DCMI_IRQHandler
def_default_handler CRYP_IRQHandler

/* 中断80-81 */
def_default_handler HASH_RNG_IRQHandler
def_default_handler FPU_IRQHandler

