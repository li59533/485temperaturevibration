/**
 **************************************************************************************************
 * @file        sort.c
 * @author
 * @version
 * @date        5/28/2016
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "stdint.h"
#include "sort.h"

/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    sort_Modules 
 * @{  
 */

/**
 * @defgroup      sort_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      sort_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      sort_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      sort_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      sort_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      sort_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      sort_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      sort_Functions 
 * @brief         
 * @{  
 */
 
void Bubble_sort(float *arr, int len)
{

    float tmp = 0.0;
    uint8_t  swap = 0;//加判断条件  减少比较次数
    for (int i = 0; i < len -1; i++)
    {
        for (int j = 0; j < len - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;//交换
                swap = 1;
            }
        }
        if (!swap)
        {
            return;
        }
    }
}


/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

