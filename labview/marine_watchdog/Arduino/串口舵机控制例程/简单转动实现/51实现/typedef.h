/******************************************************
 * FileName:      uart.c
 * Company:       乐幻索尔
 * Date:          2016/07/08  14:30
 * Description:    Lobot舵机控制板二次开发示例，基于stc89c52rc开发，
 *                 本文件包含了数据类型的定义
 *****************************************************/

#ifndef TYPEDEF_H_
#define TYPEDEF_H_

typedef unsigned char uint8_t;
typedef signed char int8_t;
typedef unsigned int uint16_t;
typedef signed int int16_t;
typedef unsigned long int uint32_t;
typedef signed long int int32_t;

typedef enum {
	false = 0, true = !false
}bool;


#endif
