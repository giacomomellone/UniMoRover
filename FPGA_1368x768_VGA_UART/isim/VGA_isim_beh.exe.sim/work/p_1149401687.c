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



void work_p_1149401687_sub_1121350022_2668930228(char *t0, char *t1, char *t2, unsigned int t3, unsigned int t4, char *t5, unsigned int t6, unsigned int t7, char *t8, unsigned int t9, unsigned int t10, char *t11, unsigned int t12, unsigned int t13, char *t14, unsigned int t15, unsigned int t16, char *t17, unsigned int t18, unsigned int t19, char *t20)
{
    unsigned char t23;
    unsigned char t24;
    char *t25;
    char *t26;
    int t27;
    char *t28;
    int t29;
    unsigned char t30;
    char *t31;
    int t32;
    char *t33;
    int t34;
    char *t35;
    int t36;
    int t37;
    unsigned char t38;
    unsigned char t39;
    char *t40;
    int t41;
    char *t42;
    int t43;
    unsigned char t44;
    char *t45;
    int t46;
    char *t47;
    int t48;
    char *t49;
    int t50;
    int t51;
    unsigned char t52;
    unsigned int t53;
    char *t54;
    char *t55;
    char *t56;

LAB0:    t25 = (t2 + 40U);
    t26 = *((char **)t25);
    t25 = (t26 + t4);
    t27 = *((int *)t25);
    t26 = (t8 + 40U);
    t28 = *((char **)t26);
    t26 = (t28 + t10);
    t29 = *((int *)t26);
    t30 = (t27 > t29);
    if (t30 == 1)
        goto LAB8;

LAB9:    t24 = (unsigned char)0;

LAB10:    if (t24 == 1)
        goto LAB5;

LAB6:    t23 = (unsigned char)0;

LAB7:    if (t23 != 0)
        goto LAB2;

LAB4:    t53 = (0 + t18);
    t25 = (t20 + 56U);
    t26 = *((char **)t25);
    t28 = (t26 + 56U);
    t31 = *((char **)t28);
    *((unsigned char *)t31) = (unsigned char)2;
    xsi_driver_first_trans_delta(t20, t53, 1, 0LL);

LAB3:
LAB1:    return;
LAB2:    t53 = (0 + t18);
    t49 = (t20 + 56U);
    t54 = *((char **)t49);
    t55 = (t54 + 56U);
    t56 = *((char **)t55);
    *((unsigned char *)t56) = (unsigned char)3;
    xsi_driver_first_trans_delta(t20, t53, 1, 0LL);
    goto LAB3;

LAB5:    t35 = (t5 + 40U);
    t40 = *((char **)t35);
    t35 = (t40 + t7);
    t41 = *((int *)t35);
    t40 = (t11 + 40U);
    t42 = *((char **)t40);
    t40 = (t42 + t13);
    t43 = *((int *)t40);
    t44 = (t41 > t43);
    if (t44 == 1)
        goto LAB11;

LAB12:    t39 = (unsigned char)0;

LAB13:    t23 = t39;
    goto LAB7;

LAB8:    t28 = (t2 + 40U);
    t31 = *((char **)t28);
    t28 = (t31 + t4);
    t32 = *((int *)t28);
    t31 = (t8 + 40U);
    t33 = *((char **)t31);
    t31 = (t33 + t10);
    t34 = *((int *)t31);
    t33 = (t14 + 40U);
    t35 = *((char **)t33);
    t33 = (t35 + t16);
    t36 = *((int *)t33);
    t37 = (t34 + t36);
    t38 = (t32 < t37);
    t24 = t38;
    goto LAB10;

LAB11:    t42 = (t5 + 40U);
    t45 = *((char **)t42);
    t42 = (t45 + t7);
    t46 = *((int *)t42);
    t45 = (t11 + 40U);
    t47 = *((char **)t45);
    t45 = (t47 + t13);
    t48 = *((int *)t45);
    t47 = (t14 + 40U);
    t49 = *((char **)t47);
    t47 = (t49 + t16);
    t50 = *((int *)t47);
    t51 = (t48 + t50);
    t52 = (t46 < t51);
    t39 = t52;
    goto LAB13;

}


extern void work_p_1149401687_init()
{
	static char *se[] = {(void *)work_p_1149401687_sub_1121350022_2668930228};
	xsi_register_didat("work_p_1149401687", "isim/VGA_isim_beh.exe.sim/work/p_1149401687.didat");
	xsi_register_subprogram_executes(se);
}
