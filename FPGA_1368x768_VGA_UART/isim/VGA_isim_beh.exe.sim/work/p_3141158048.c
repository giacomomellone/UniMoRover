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



void work_p_3141158048_sub_3943171265_4213757531(char *t0, char *t1, char *t2, unsigned int t3, unsigned int t4, char *t5, unsigned int t6, unsigned int t7, char *t8, unsigned int t9, unsigned int t10, char *t11, unsigned int t12, unsigned int t13, char *t14, unsigned int t15, unsigned int t16, char *t17, unsigned int t18, unsigned int t19, char *t20, unsigned int t21, unsigned int t22, char *t23)
{
    unsigned char t26;
    unsigned char t27;
    unsigned char t28;
    char *t29;
    char *t30;
    int t31;
    char *t32;
    int t33;
    unsigned char t34;
    char *t35;
    int t36;
    char *t37;
    int t38;
    char *t39;
    int t40;
    int t41;
    unsigned char t42;
    unsigned char t43;
    char *t44;
    int t45;
    char *t46;
    int t47;
    unsigned char t48;
    char *t49;
    int t50;
    char *t51;
    int t52;
    char *t53;
    int t54;
    int t55;
    unsigned char t56;
    unsigned char t57;
    unsigned char t58;
    char *t59;
    int t60;
    char *t61;
    int t62;
    unsigned char t63;
    char *t64;
    int t65;
    char *t66;
    int t67;
    char *t68;
    int t69;
    int t70;
    unsigned char t71;
    unsigned char t72;
    char *t73;
    int t74;
    char *t75;
    int t76;
    unsigned char t77;
    char *t78;
    int t79;
    char *t80;
    int t81;
    char *t82;
    int t83;
    int t84;
    unsigned char t85;
    unsigned int t86;
    char *t87;
    char *t88;
    char *t89;

LAB0:    t29 = (t2 + 40U);
    t30 = *((char **)t29);
    t29 = (t30 + t4);
    t31 = *((int *)t29);
    t30 = (t8 + 40U);
    t32 = *((char **)t30);
    t30 = (t32 + t10);
    t33 = *((int *)t30);
    t34 = (t31 > t33);
    if (t34 == 1)
        goto LAB11;

LAB12:    t28 = (unsigned char)0;

LAB13:    if (t28 == 1)
        goto LAB8;

LAB9:    t27 = (unsigned char)0;

LAB10:    if (t27 == 1)
        goto LAB5;

LAB6:    t53 = (t5 + 40U);
    t59 = *((char **)t53);
    t53 = (t59 + t7);
    t60 = *((int *)t53);
    t59 = (t11 + 40U);
    t61 = *((char **)t59);
    t59 = (t61 + t13);
    t62 = *((int *)t59);
    t63 = (t60 > t62);
    if (t63 == 1)
        goto LAB20;

LAB21:    t58 = (unsigned char)0;

LAB22:    if (t58 == 1)
        goto LAB17;

LAB18:    t57 = (unsigned char)0;

LAB19:    t26 = t57;

LAB7:    if (t26 != 0)
        goto LAB2;

LAB4:    t86 = (0 + t21);
    t29 = (t23 + 56U);
    t30 = *((char **)t29);
    t32 = (t30 + 56U);
    t35 = *((char **)t32);
    *((unsigned char *)t35) = (unsigned char)2;
    xsi_driver_first_trans_delta(t23, t86, 1, 0LL);

LAB3:
LAB1:    return;
LAB2:    t86 = (0 + t21);
    t82 = (t23 + 56U);
    t87 = *((char **)t82);
    t88 = (t87 + 56U);
    t89 = *((char **)t88);
    *((unsigned char *)t89) = (unsigned char)3;
    xsi_driver_first_trans_delta(t23, t86, 1, 0LL);
    goto LAB3;

LAB5:    t26 = (unsigned char)1;
    goto LAB7;

LAB8:    t39 = (t5 + 40U);
    t44 = *((char **)t39);
    t39 = (t44 + t7);
    t45 = *((int *)t39);
    t44 = (t11 + 40U);
    t46 = *((char **)t44);
    t44 = (t46 + t13);
    t47 = *((int *)t44);
    t48 = (t45 == t47);
    if (t48 == 1)
        goto LAB14;

LAB15:    t46 = (t5 + 40U);
    t49 = *((char **)t46);
    t46 = (t49 + t7);
    t50 = *((int *)t46);
    t49 = (t11 + 40U);
    t51 = *((char **)t49);
    t49 = (t51 + t13);
    t52 = *((int *)t49);
    t51 = (t17 + 40U);
    t53 = *((char **)t51);
    t51 = (t53 + t19);
    t54 = *((int *)t51);
    t55 = (t52 + t54);
    t56 = (t50 == t55);
    t43 = t56;

LAB16:    t27 = t43;
    goto LAB10;

LAB11:    t32 = (t2 + 40U);
    t35 = *((char **)t32);
    t32 = (t35 + t4);
    t36 = *((int *)t32);
    t35 = (t8 + 40U);
    t37 = *((char **)t35);
    t35 = (t37 + t10);
    t38 = *((int *)t35);
    t37 = (t14 + 40U);
    t39 = *((char **)t37);
    t37 = (t39 + t16);
    t40 = *((int *)t37);
    t41 = (t38 + t40);
    t42 = (t36 < t41);
    t28 = t42;
    goto LAB13;

LAB14:    t43 = (unsigned char)1;
    goto LAB16;

LAB17:    t68 = (t2 + 40U);
    t73 = *((char **)t68);
    t68 = (t73 + t4);
    t74 = *((int *)t68);
    t73 = (t8 + 40U);
    t75 = *((char **)t73);
    t73 = (t75 + t10);
    t76 = *((int *)t73);
    t77 = (t74 == t76);
    if (t77 == 1)
        goto LAB23;

LAB24:    t75 = (t2 + 40U);
    t78 = *((char **)t75);
    t75 = (t78 + t4);
    t79 = *((int *)t75);
    t78 = (t8 + 40U);
    t80 = *((char **)t78);
    t78 = (t80 + t10);
    t81 = *((int *)t78);
    t80 = (t14 + 40U);
    t82 = *((char **)t80);
    t80 = (t82 + t16);
    t83 = *((int *)t80);
    t84 = (t81 + t83);
    t85 = (t79 == t84);
    t72 = t85;

LAB25:    t57 = t72;
    goto LAB19;

LAB20:    t61 = (t5 + 40U);
    t64 = *((char **)t61);
    t61 = (t64 + t7);
    t65 = *((int *)t61);
    t64 = (t11 + 40U);
    t66 = *((char **)t64);
    t64 = (t66 + t13);
    t67 = *((int *)t64);
    t66 = (t17 + 40U);
    t68 = *((char **)t66);
    t66 = (t68 + t19);
    t69 = *((int *)t66);
    t70 = (t67 + t69);
    t71 = (t65 < t70);
    t58 = t71;
    goto LAB22;

LAB23:    t72 = (unsigned char)1;
    goto LAB25;

}


extern void work_p_3141158048_init()
{
	static char *se[] = {(void *)work_p_3141158048_sub_3943171265_4213757531};
	xsi_register_didat("work_p_3141158048", "isim/VGA_isim_beh.exe.sim/work/p_3141158048.didat");
	xsi_register_subprogram_executes(se);
}
