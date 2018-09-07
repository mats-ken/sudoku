/* �ơ��֥�ξ��֤�ɽ�� */
void        print_table(TABLE*t)
{
  int         i;

  for(i = 0; i < 9 * 9; i++){
    if(t[i].fixed)
      printf("%d", t[i].fixed);
    else
      printf(" ");

    if(0 == (i + 1) % 9)
      printf("\n");
    else if(0 == (i + 1) % 3)
      printf("|");
    else
      printf(" ");

    if(0 == (i + 1) % 27 && 80 != i)
      printf("-----+-----+-----\n");
  }
}

/* �ơ��֥�ξ��֤�ɽ��(Excel��) */
void        print_table_tab(TABLE*t, FILE*fp)
{
  int         i;

  for(i = 0; i < 9 * 9; i++){
    if(t[i].fixed)
      fprintf(fp, "%d", t[i].fixed);
    else
      fprintf(fp, " ");

    if(0 == (i + 1) % 9)
      fprintf(fp, "\n");
    else
      fprintf(fp, "\t");
  }
}

/* �ơ��֥�ξ��֤�ɽ��(�����) */
void        print_table_0(TABLE*t, FILE*fp)
{
  int         i;

  for(i = 0; i < 9 * 9; i++){
    if(t[i].fixed)
      fprintf(fp, "%d", t[i].fixed);
    else
      fprintf(fp, "0");

    if(0 == (i + 1) % 9)
      fprintf(fp, "\n");
  }
}

/* �ơ��֥�ξ��֤�ܤ���ɽ�� */
void        print_table_detail(TABLE*t)
{
  int         i, j;

  for(i = 0; i < 9 * 9; i++){
    for(j = 0; j < 9; j++){
      if(t[i].flag[j])
        printf("%d", j + 1);
      else if(t[i].fixed)
        printf(" ");
      else
        printf("*");
    }

    if(0 == (i + 1) % 9)
      printf("\n");
    else if(0 == (i + 1) % 3)
      printf(" # ");
    else
      printf("|");

    if(0 == (i + 1) % 27 && 80 != i){
      for(j = 0; j < 9 * 9 + 8 + 4; j++)
        putchar('#');
      printf("\n");
    }
  }
}
