/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                       */
/*  \   \        Copyright (c) 2003-2009 Xilinx, Inc.                */
/*  /   /          All Right Reserved.                                 */
/* /---/   /\                                                         */
/* \   \  /  \                                                      */
/*  \___\/\___\                                                    */
/***********************************************************************/

/* This file is designed for use with ISim build 0x7708f090 */

#define XSI_HIDE_SYMBOL_SPEC true
#include "xsi.h"
#include <memory.h>
#ifdef __GNUC__
#include <stdlib.h>
#else
#include <malloc.h>
#define alloca _alloca
#endif
static const char *ng0 = "C:/Users/Giacomo/Google Drive/FPGA/VGA_Car_universal/Display7.vhd";



static void work_a_0500896507_3212880686_p_0(char *t0)
{
    unsigned char t1;
    char *t2;
    unsigned char t3;
    char *t4;
    char *t5;
    unsigned char t6;
    unsigned char t7;
    char *t8;
    int t9;
    unsigned int t10;
    unsigned int t11;
    unsigned int t12;
    unsigned char t13;
    unsigned char t14;
    char *t15;
    char *t16;
    int t17;
    unsigned char t18;
    char *t19;
    char *t20;
    char *t21;
    char *t22;
    char *t23;
    char *t24;
    unsigned int t25;
    unsigned int t26;
    unsigned int t27;
    int t28;
    unsigned int t29;
    unsigned int t30;
    unsigned int t31;
    unsigned char t32;
    unsigned char t33;
    int t34;
    unsigned int t35;
    unsigned int t36;
    unsigned int t37;
    unsigned char t38;
    unsigned char t39;
    char *t40;
    char *t41;
    char *t42;

LAB0:    xsi_set_current_line(39, ng0);
    t2 = (t0 + 1472U);
    t3 = xsi_signal_has_event(t2);
    if (t3 == 1)
        goto LAB5;

LAB6:    t1 = (unsigned char)0;

LAB7:    if (t1 != 0)
        goto LAB2;

LAB4:
LAB3:    t2 = (t0 + 3152);
    *((int *)t2) = 1;

LAB1:    return;
LAB2:    xsi_set_current_line(40, ng0);
    t4 = (t0 + 1032U);
    t8 = *((char **)t4);
    t9 = (0 - 3);
    t10 = (t9 * -1);
    t11 = (1U * t10);
    t12 = (0 + t11);
    t4 = (t8 + t12);
    t13 = *((unsigned char *)t4);
    t14 = (t13 == (unsigned char)3);
    if (t14 != 0)
        goto LAB8;

LAB10:    xsi_set_current_line(61, ng0);
    t2 = (t0 + 5440);
    t5 = (t0 + 3296);
    t8 = (t5 + 56U);
    t15 = *((char **)t8);
    t16 = (t15 + 56U);
    t19 = *((char **)t16);
    memcpy(t19, t2, 8U);
    xsi_driver_first_trans_fast_port(t5);
    xsi_set_current_line(62, ng0);
    t2 = (t0 + 5448);
    t5 = (t0 + 3232);
    t8 = (t5 + 56U);
    t15 = *((char **)t8);
    t16 = (t15 + 56U);
    t19 = *((char **)t16);
    memcpy(t19, t2, 4U);
    xsi_driver_first_trans_fast_port(t5);

LAB9:    xsi_set_current_line(64, ng0);
    t2 = (t0 + 1032U);
    t4 = *((char **)t2);
    t9 = (0 - 3);
    t10 = (t9 * -1);
    t11 = (1U * t10);
    t12 = (0 + t11);
    t2 = (t4 + t12);
    t7 = *((unsigned char *)t2);
    t13 = (t7 == (unsigned char)2);
    if (t13 == 1)
        goto LAB30;

LAB31:    t6 = (unsigned char)0;

LAB32:    if (t6 == 1)
        goto LAB27;

LAB28:    t3 = (unsigned char)0;

LAB29:    if (t3 == 1)
        goto LAB24;

LAB25:    t1 = (unsigned char)0;

LAB26:    if (t1 != 0)
        goto LAB21;

LAB23:
LAB22:    goto LAB3;

LAB5:    t4 = (t0 + 1512U);
    t5 = *((char **)t4);
    t6 = *((unsigned char *)t5);
    t7 = (t6 == (unsigned char)3);
    t1 = t7;
    goto LAB7;

LAB8:    xsi_set_current_line(41, ng0);
    t15 = (t0 + 1672U);
    t16 = *((char **)t15);
    t17 = *((int *)t16);
    t18 = (t17 < 10000);
    if (t18 != 0)
        goto LAB11;

LAB13:    t2 = (t0 + 1672U);
    t4 = *((char **)t2);
    t9 = *((int *)t4);
    t3 = (t9 > 10000);
    if (t3 == 1)
        goto LAB16;

LAB17:    t1 = (unsigned char)0;

LAB18:    if (t1 != 0)
        goto LAB14;

LAB15:    t2 = (t0 + 1672U);
    t4 = *((char **)t2);
    t9 = *((int *)t4);
    t1 = (t9 > 2147483600);
    if (t1 != 0)
        goto LAB19;

LAB20:
LAB12:    goto LAB9;

LAB11:    xsi_set_current_line(42, ng0);
    t15 = (t0 + 5416);
    t20 = (t0 + 3232);
    t21 = (t20 + 56U);
    t22 = *((char **)t21);
    t23 = (t22 + 56U);
    t24 = *((char **)t23);
    memcpy(t24, t15, 4U);
    xsi_driver_first_trans_fast_port(t20);
    xsi_set_current_line(43, ng0);
    t2 = (t0 + 5420);
    t5 = (t0 + 3296);
    t8 = (t5 + 56U);
    t15 = *((char **)t8);
    t16 = (t15 + 56U);
    t19 = *((char **)t16);
    memcpy(t19, t2, 8U);
    xsi_driver_first_trans_fast_port(t5);
    xsi_set_current_line(44, ng0);
    t2 = (t0 + 1672U);
    t4 = *((char **)t2);
    t9 = *((int *)t4);
    t17 = (t9 + 1);
    t2 = (t0 + 3360);
    t5 = (t2 + 56U);
    t8 = *((char **)t5);
    t15 = (t8 + 56U);
    t16 = *((char **)t15);
    *((int *)t16) = t17;
    xsi_driver_first_trans_fast(t2);
    goto LAB12;

LAB14:    xsi_set_current_line(46, ng0);
    t2 = (t0 + 5428);
    t15 = (t0 + 3232);
    t16 = (t15 + 56U);
    t19 = *((char **)t16);
    t20 = (t19 + 56U);
    t21 = *((char **)t20);
    memcpy(t21, t2, 4U);
    xsi_driver_first_trans_fast_port(t15);
    xsi_set_current_line(47, ng0);
    t2 = (t0 + 5432);
    t5 = (t0 + 3296);
    t8 = (t5 + 56U);
    t15 = *((char **)t8);
    t16 = (t15 + 56U);
    t19 = *((char **)t16);
    memcpy(t19, t2, 8U);
    xsi_driver_first_trans_fast_port(t5);
    xsi_set_current_line(48, ng0);
    t2 = (t0 + 1672U);
    t4 = *((char **)t2);
    t9 = *((int *)t4);
    t17 = (t9 + 1);
    t2 = (t0 + 3360);
    t5 = (t2 + 56U);
    t8 = *((char **)t5);
    t15 = (t8 + 56U);
    t16 = *((char **)t15);
    *((int *)t16) = t17;
    xsi_driver_first_trans_fast(t2);
    goto LAB12;

LAB16:    t2 = (t0 + 1672U);
    t5 = *((char **)t2);
    t17 = *((int *)t5);
    t6 = (t17 < 20000);
    t1 = t6;
    goto LAB18;

LAB19:    xsi_set_current_line(50, ng0);
    t2 = (t0 + 3360);
    t5 = (t2 + 56U);
    t8 = *((char **)t5);
    t15 = (t8 + 56U);
    t16 = *((char **)t15);
    *((int *)t16) = 0;
    xsi_driver_first_trans_fast(t2);
    goto LAB12;

LAB21:    xsi_set_current_line(65, ng0);
    t21 = (t0 + 5452);
    t23 = (t0 + 3296);
    t24 = (t23 + 56U);
    t40 = *((char **)t24);
    t41 = (t40 + 56U);
    t42 = *((char **)t41);
    memcpy(t42, t21, 8U);
    xsi_driver_first_trans_fast_port(t23);
    xsi_set_current_line(66, ng0);
    t2 = (t0 + 5460);
    t5 = (t0 + 3232);
    t8 = (t5 + 56U);
    t15 = *((char **)t8);
    t16 = (t15 + 56U);
    t19 = *((char **)t16);
    memcpy(t19, t2, 4U);
    xsi_driver_first_trans_fast_port(t5);
    xsi_set_current_line(67, ng0);
    t2 = (t0 + 3360);
    t4 = (t2 + 56U);
    t5 = *((char **)t4);
    t8 = (t5 + 56U);
    t15 = *((char **)t8);
    *((int *)t15) = 0;
    xsi_driver_first_trans_fast(t2);
    goto LAB22;

LAB24:    t19 = (t0 + 1032U);
    t20 = *((char **)t19);
    t34 = (3 - 3);
    t35 = (t34 * -1);
    t36 = (1U * t35);
    t37 = (0 + t36);
    t19 = (t20 + t37);
    t38 = *((unsigned char *)t19);
    t39 = (t38 == (unsigned char)2);
    t1 = t39;
    goto LAB26;

LAB27:    t15 = (t0 + 1032U);
    t16 = *((char **)t15);
    t28 = (2 - 3);
    t29 = (t28 * -1);
    t30 = (1U * t29);
    t31 = (0 + t30);
    t15 = (t16 + t31);
    t32 = *((unsigned char *)t15);
    t33 = (t32 == (unsigned char)2);
    t3 = t33;
    goto LAB29;

LAB30:    t5 = (t0 + 1032U);
    t8 = *((char **)t5);
    t17 = (1 - 3);
    t25 = (t17 * -1);
    t26 = (1U * t25);
    t27 = (0 + t26);
    t5 = (t8 + t27);
    t14 = *((unsigned char *)t5);
    t18 = (t14 == (unsigned char)2);
    t6 = t18;
    goto LAB32;

}


extern void work_a_0500896507_3212880686_init()
{
	static char *pe[] = {(void *)work_a_0500896507_3212880686_p_0};
	xsi_register_didat("work_a_0500896507_3212880686", "isim/VGA_isim_beh.exe.sim/work/a_0500896507_3212880686.didat");
	xsi_register_executes(pe);
}
