/* ���� */

#include    <stdio.h>
#include    <stdlib.h>

#define     ERROR  -1
#define     SOLVED 0

#define     SIZE   9
#define     SIZE2  (SIZE * SIZE)

typedef     struct{
  int         fixed;
  int         flag[SIZE];
}           TABLE;

#include    "../del_dupe.c"
#include    "../chk_error.c"
#include    "../print.c"

/* ����ǡ�����ơ��֥���Ѵ� */
void        question2table(int*q, TABLE*t)
{
  int         i, j;

  for(i = 0; i < 9 * 9; i++){
    t[i].fixed = q[i];
    if(q[i]){
      for(j = 0; j < SIZE; j++)
        t[i].flag[j] = 0;
      t[i].flag[q[i] - 1] = 1;
    }else
      for(j = 0; j < SIZE; j++)
        t[i].flag[j] = 1;
  }
}

/* �����˷��ꤷ���ޥ���̵���������å�����ͭ���fix���� */
int         chk_fixed(TABLE*t)
{
  int         i, j, k, n;
  int         flag = 0;

  for(i = 0; i < 9 * 9; i++)
    if(!t[i].fixed){
      n = 0;
      for(j = 0; j < 9; j++)
        if(t[i].flag[j]){
          n++;
          k = j + 1;
        }

      if(1 == n){
//        printf("(%d %d)", i, k);
        t[i].fixed = k;
        flag = 1;
      }
    }

  return flag;
}

/* ��λȽ��(���ꤷ�Ƥ��ʤ��ޥ��ο����֤�, -1:error) */
int         chk_finished(TABLE*t)
{
  int         i, n = 0;

  for(i = 0; i < 9 * 9; i++)
    if(!t[i].fixed)
      n++;

  if(chk_error(t) < 0)
    return -1;

  return n;
}

/* �ơ��֥�򥳥ԡ����� */
void        cp_table(TABLE*src, TABLE*dest)
{
  int         i;

  for(i = 0; i < 9 * 9; i++)
    dest[i] = src[i];
}

/* �ơ��֥����Ӥ���(fixed�Τ�) */
int         cmp_table(TABLE*src, TABLE*dest)
{
  int         i;

  for(i = 0; i < 9 * 9; i++)
    if(dest[i].fixed != src[i].fixed)
      return -1;
  return 0;
}

/* �ºݤ˲�
 * mode < 0  : �����鸡��
 * otherwise : �夫�鸡��
 */
int         solve(TABLE*t, int mode)
{
  TABLE       backup[9 * 9];
  int         j, k, m, n = 0;

  del_dupe(t);

  /* �ơ��֥��Хå����åפ��� */
  cp_table(t, backup);

  while(1){

    /* ��λȽ�� */
    k = chk_finished(t);
    /* ���顼(���ƤΥޥ���fix������������ǤϤʤ�) */
    if(k < 0)
      return ERROR;
    if(0 == k)
      return SOLVED;

    /* �ޤ����ꤷ�Ƥ��ʤ��ǽ�Υޥ��򥵡��� */
    for(m = 0; m < 9 * 9; m++)
      if(0 == t[m].fixed)
        break;

    if(mode < 0){
      /* �ĤäƤ������Τ������Ǥ⾮�������򥵡��� */
      for(n = 0; n < 9; n++)
        if(t[m].flag[n])
          break;
    }else
      /* �ĤäƤ������Τ������Ǥ��礭�����򥵡��� */
      for(n = 8; 0 <= n; n--)
        if(t[m].flag[n])
          break;

    if(9 <= n)
      return ERROR;

  /* ���ο��˷��ꤹ�� */
    t[m].fixed = n + 1;
    for(j = n + 1; j < 9; j++)
      t[m].flag[j] = 0;

    del_dupe(t);

    k = solve(t, mode);
    if(SOLVED == k) /* �����é���夤�� */
      return SOLVED;
    else if(k < 0){ /* ���顼(���ƤΥޥ���fix������������ǤϤʤ�) */
      backup[m].flag[n] = 0;
      del_dupe(backup);
      cp_table(backup, t);
    }
  }
}

int         main(void)
{
  int         question[9 * 9]
    = {0,0,0,0,0,0,7,0,6,
3,0,0,0,5,6,0,0,0,
0,0,0,0,1,2,9,4,0,
0,0,9,0,0,0,0,0,0,
4,0,0,0,0,1,0,8,0,
0,8,0,2,0,0,5,0,0,
0,4,8,0,0,0,0,1,0,
2,9,3,0,0,7,0,0,0,
0,0,0,0,0,3,0,0,9
};

  int         exsample[9 * 9]
    = {0,5,0,7,0,1,0,4,0,
       7,0,3,0,0,0,1,0,2,
       0,8,0,4,0,6,0,9,0,
       9,0,4,0,6,0,8,0,3,
       0,0,0,8,0,7,0,0,0,
       1,0,8,0,5,0,6,0,9,
       0,1,0,6,0,3,0,8,0,
       5,0,6,0,0,0,7,0,1,
       0,3,0,5,0,9,0,2,0};

  int         easy1[9 * 9]
    = {0,2,8,5,0,4,1,7,0,
       6,4,0,0,2,0,0,5,3,
       1,0,0,0,9,0,0,0,8,
       8,0,0,0,1,0,0,0,5,
       0,1,3,7,0,2,6,4,0,
       4,0,0,0,6,0,0,0,2,
       2,0,0,0,5,0,0,0,7,
       7,9,0,0,4,0,0,8,1,
       0,5,1,8,0,6,2,9,0};

  int         medium50[9 * 9]
    = {0,4,0,0,0,0,0,0,0,
       0,3,9,0,0,0,0,2,7,
       0,0,5,9,0,0,6,8,0,
       0,0,0,5,0,1,9,0,0,
       0,0,0,0,0,0,0,0,0,
       0,0,3,4,0,2,0,0,0,
       0,6,7,0,0,3,1,0,0,
       1,2,0,0,0,0,4,5,0,
       0,0,0,0,0,0,0,7,0};

  int         hard99[9 * 9]
    = {8,0,0,0,0,5,0,0,0,
       0,1,2,3,0,0,6,0,0,
       0,4,5,6,0,0,0,2,0,
       0,7,8,0,0,0,0,0,1,
       0,0,0,0,9,0,0,0,0,
       9,0,0,0,0,0,8,7,0,
       0,2,0,0,0,6,5,4,0,
       0,0,4,0,0,3,2,1,0,
       0,0,0,1,0,0,0,0,9};

  int tmp0[9 * 9]
    = {8,0,0,0,9,0,0,6,7,
5,0,0,0,0,3,0,0,0,
0,0,3,1,0,0,8,0,0,
0,9,0,5,0,0,4,0,0,
7,0,0,6,0,2,0,0,8,
0,0,0,0,8,0,0,1,0,
0,0,4,0,0,8,7,0,0,
0,0,0,7,0,0,0,0,3,
3,8,0,0,6,0,0,0,4};

  int tmp1[9 * 9]
    = {7,0,0,0,0,3,4,0,6,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,9,8,0,2,
0,0,4,5,0,0,6,0,9,
1,0,0,3,0,2,0,0,7,
9,0,7,0,0,6,3,0,0,
5,0,1,4,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
6,0,8,2,0,0,0,0,3};

  int tmp2[9 * 9]
    = {
0,3,6,0,0,0,4,1,0,
1,0,0,0,3,0,0,0,5,
7,0,0,2,0,4,0,0,6,
0,0,4,0,9,0,3,0,0,
0,2,0,8,0,3,0,9,0,
0,0,7,0,6,0,1,0,0,
9,0,0,4,0,5,0,0,1,
6,0,0,0,7,0,0,0,4,
0,7,5,0,0,0,9,2,0};

  TABLE       t0[9 * 9];
  TABLE       t1[9 * 9];
  int         i, j;

//  question2table(exsample, t0);
//  question2table(easy1, t0);
//  question2table(medium50, t0);
//  question2table(hard99, t0);
//  question2table(tmp0, t0);
  question2table(question, t0);

  /* �����ɽ�� */
  printf("Question:\n");
  print_table(t0);

  /* solve */
  del_dupe(t0);
  if(SOLVED == chk_finished(t0))
    printf("Easy/Medium\n");
  else
    printf("Hard\n");

  cp_table(t0, t1);

  i = solve(t0, 1);
  if(i < 0)
    fprintf(stderr, "ERROR.\n");

  j = solve(t1, -1);
  if(j < 0)
    fprintf(stderr, "ERROR.\n");

  /* ������ɽ�� */
  printf("\nAnswer:\n");
  print_table(t0);

  /* ������ʣ��¸�ߤ����硢�⤦��Ĥ����ɽ�� */
  if(cmp_table(t0, t1) < 0){
    printf("\n");
    print_table(t1);
  }

  return EXIT_SUCCESS;
}
