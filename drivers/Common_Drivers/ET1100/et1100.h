#ifndef __ET1100_H__
#define __ET1100_H__
#include <stdio.h>



int et1100_init();

void et1100_read_isr(void *pData, uint16_t Address, uint16_t Len);
void et1100_read(void *pData, uint16_t Address, uint16_t Len);

void et1100_write_isr(void *pData, uint16_t Address, uint16_t Len);
void et1100_write(void *pData, uint16_t Address, uint16_t Len);

/*  SSC FUNCTION */
/**< \brief Returns the first 16bit of the AL Event register(0x220)*/
#define HW_GetALEventRegister()                   et1100_get_alevent_reg()
#define HW_GetALEventRegister_Isr()               et1100_get_alevent_reg()

/**< \brief Generic ESC (register and DPRAM) read access.*/
#define HW_EscRead(pData, Address, Len)           et1100_read(pData, Address, Len)
#define HW_EscReadIsr(pData, Address, Len)        et1100_read_isr(pData, Address, Len)
/**< \brief Generic ESC (register and DPRAM) write access.*/
#define HW_EscWrite(pData, Address, Len)          et1100_write(pData, Address, Len)
#define HW_EscWriteIsr(pData, Address, Len)       et1100_write_isr(pData, Address, Len)


#if 0
/**< \brief 16Bit specific ESC (register and DPRAM) read access.*/
#define HW_EscReadWord(WordValue, Address)        et1100_read((uint16_t*)(&WordValue), Address,2)
#define HW_EscReadWordIsr(WordValue, Address)     et1100_read((uint16_t*)(&WordValue), Address,2)
/**< \brief 16Bit specific ESC (register and DPRAM) write access.*/
#define HW_EscWriteWord(WordValue, Address)       et1100_write((uint16_t*)(&WordValue), Address,2)
#define HW_EscWriteWordIsr(WordValue, Address)    et1100_write((uint16_t*)(&WordValue), Address,2)
#endif /* ESC_16BIT_ACCESS */

# if 1
/**< \brief 32Bit specific ESC (register and DPRAM) read access.*/
#define HW_EscReadDWord(DWordValue, Address)      et1100_read((void*)(&DWordValue), Address, 4)
#define HW_EscReadDWordIsr(DWordValue, Address)   et1100_read_isr((void*)(&DWordValue), Address, 4)
/**< \brief 32Bit specific ESC (register and DPRAM) write access.*/
#define HW_EscWriteDWord(DWordValue, Address)     et1100_write((void*)(&DWordValue), Address,4)
#define HW_EscWriteDWordIsr(DWordValue, Address)  et1100_write_isr((void*)(&DWordValue), Address,4)
#endif /* ESC_32BIT_ACCESS */

/**< \brief Macro to copy data from the application mailbox memory(not the ESC memory).*/
#define HW_EscReadMbxMem(pData, Address, Len)     et1100_read(pData, Address, Len)
/**< \brief Macro to copy data from the application mailbox memory (not the ESC memory).*/
#define HW_EscWriteMbxMem(pData, Address, Len)    et1100_write(pData, Address, Len)



#endif /* __ET1100_H__ */